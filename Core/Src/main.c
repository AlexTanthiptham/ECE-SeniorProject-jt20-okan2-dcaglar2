/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "motorDriver.h"
#include "virtualTimer.h"
#include "serial.h"
#include "test.h"
#include "encoder.h"
#include "math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define baseDutyCycle  0.5
#define TESTING 1
#define ACTUAL_ROBOT 0
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
VirtualTimer MotorATimer;
VirtualTimer MotorBTimer;
Encoder EncoderA;
Encoder EncoderB;
MotorDriver MD;
RPIClient pi;
int encoderValue;
int direction;
double EncoderA_Kp =0.01; //0.01; // 0.01 0.25
double EncoderA_Ki =1.5;//1.5
double EncoderA_Kd = 0.1; //0.1
int timeoutCounter = 0;
int ret = 0;
#define TIMEOUT_COUNTER_LIMIT (int)(1000.0 / UART_TIMEOUT)
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM5_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
//  HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
	  PIDPON_TypeDef POn = _PID_P_ON_E;
	  PIDCD_TypeDef ControllerDirection = _PID_CD_DIRECT;
	PID_TypeDef EncoderA_PID;
	double EncoderA_Out =0;
	double EncoderA_In =0;
	double EncoderA_SS=0;
	PID_Params EncoderA_PID_Params = {
    .uPID = &EncoderA_PID,
	  .Kp = EncoderA_Kp,
	  .Ki = EncoderA_Ki,
	  .Kd = EncoderA_Kd,
	  .POn = POn,
	  .ControllerDirection = ControllerDirection,
	  .Input = &EncoderA_In,
	  .Output = &EncoderA_Out,
	  .Setpoint = &EncoderA_SS
  };
	double EncoderB_Out =0;
	double EncoderB_In =0;
	double EncoderB_SS=0;
	PID_TypeDef EncoderB_PID;
	PID_Params EncoderB_PID_Params = {
    .uPID = &EncoderB_PID,
	  .Kp = EncoderA_Kp,
	  .Ki = EncoderA_Ki,
	  .Kd = EncoderA_Kd,
	  .POn = POn,
	  .ControllerDirection = ControllerDirection,
	  .Input = &EncoderB_In,
	  .Output = &EncoderB_Out,
	  .Setpoint = &EncoderB_SS
  };
	initEncoder(&EncoderA, &htim5, &htim2,EncoderA_PID_Params);
	initEncoder(&EncoderB, &htim5, &htim1, EncoderB_PID_Params);
	initVirtualTimer(&MotorATimer, driverSpeed, baseDutyCycle,
	MotorAPWM_GPIO_Port, MotorAPWM_Pin, &htim3);
	initVirtualTimer(&MotorBTimer, driverSpeed, baseDutyCycle,
	MotorBPWMOutput_GPIO_Port, MotorBPWMOutput_Pin, &htim4);
	__disable_irq();
	HAL_TIM_Encoder_Start_IT(EncoderA.encoderInputTimer, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start_IT(EncoderB.encoderInputTimer,TIM_CHANNEL_ALL);
	HAL_TIM_Base_Start_IT(EncoderB.INT_Timer);
	start_IT(&MotorATimer);
	start_IT(&MotorBTimer);
	__enable_irq();

	setOverallSpeed(&MD, 0);
	double xdist = 0;
	double ydist = 0;
	double xout = 0;
	double yout = 0;
	double steadyStateY = 90;
	double steadyStateX = 0;
	double V_l, V_r;
	PID_TypeDef xctrl;
	PID_TypeDef yctrl;
	MD.encA =&EncoderA;
	MD.encB =&EncoderB;
	MotorDriverInit(&MD, &xdist, &ydist, &xout, &yout, &steadyStateX,
			&steadyStateY, &xctrl, &yctrl, &MotorATimer, &MotorBTimer);

	fastStop(&MD);
	char buffer[RPI_BUFFER_SIZE];
	RPIPacket packet;
	UARTClient piUART;
	piUART.port = &huart1;
	RPIClientInit(&pi, buffer, &packet, &piUART);
	int PIDUpdateRet = 0;
//    TIM1->CCR1 = (int) (driverSpeed / dutyCycle);
//	TIM2->CCR1 = (int) (driverSpeed / dutyCycle);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//	while(1){};
	if (ACTUAL_ROBOT && TESTING) {
		HAL_Delay(10000);
	}
//	fastStop(&MD);
//	takeOff(&MD);
	if (TESTING) {
//		Echo_TEST(&pi);
//		TEST_BASIC_FOLLOW(&MD, &pi);
//		PRINT_TEST(&pi);
		//		Echo_TEST(&pi);
		//		Parser_TEST(&pi);
//		DATA_TEST(&pi);
//		setOverallSpeed(&MD, 75);
//		Acceleration_TEST(&MD);
//		setOverallSpeed(&MD,50);
		*MD.encA->desiredSpeed =50;
		*MD.encB->desiredSpeed =50;
		goForward(&MD);
//		while(1){};
		while(1){
//			*MD.enc->desiredSpeed =100;
			setOverallSpeed(&MD, 50);
//			gradualSetIndividualSpeedRPM(MD.vtA, *MD.encA->motorSpeed);
//			gradualSetIndividualSpeedRPM(MD.vtB, *MD.encB->motorSpeed);

		}


	}

	double x = 0;
	double y = 0;

	Velocity v;
	int FIRST_MEAS = 0;

	while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//		encoderValue =  __HAL_TIM_GET_COUNTER(&htim2) >>1;
		// MAIN CODE
//		__disable_irq();
		ret = recieveData(&pi);
//		__enable_irq();
		switch (ret) {
		case HAL_ERROR:
			fastStop(&MD);
			continue;
			break;
		case HAL_TIMEOUT:
			if(!FIRST_MEAS){
				continue;
			}
			UARTPrintf(pi.uart, "ACK: MCU: Are you alive? \n\r");
//			if(FIRST_MEAS){
//				*MD.encA->desiredSpeed -= *MD.encA->desiredSpeed ==0? 0: 10;
//				*MD.encB->desiredSpeed -=*MD.encB->desiredSpeed ==0? 0: 10;
//				gradualSetIndividualSpeedRPM(MD.vtA, *MD.encA->motorSpeed);
//				gradualSetIndividualSpeedRPM(MD.vtB, *MD.encB->motorSpeed);
//			}
			if(timeoutCounter > TIMEOUT_COUNTER_LIMIT){
				fastStop(&MD);
//				timeoutCounter=0;
			}
			timeoutCounter++;
			HAL_Delay(100*timeoutCounter);
			continue;
			break;
		case HAL_OK:
			FIRST_MEAS = 1;
			break;
		}
		goForward(&MD);
//		__disable_irq();
		timeoutCounter=0;
//		xdist = pi.mostRecentPacket->xdistance;
		xdist =0;
		ydist = pi.mostRecentPacket->ydistance;
		if(ydist <70 || ydist>110){
			__enable_irq();
			UARTPrintf(pi.uart, "ACK: PID too close \n\r");

			continue;
		}
		PIDUpdateRet = motorDriverUpdate(&MD);
		if(!PIDUpdateRet){
			__enable_irq();
			UARTPrintf(pi.uart, "ACK: PID error \n\r");
			continue;
		}
//		V_l = *MD.ycontOut / (1 + *MD.xcontOut);
//		V_r =  *MD.xcontOut * V_l;
		__disable_irq();
		x = 0;//*MD.xcontOut;
		y = *MD.ycontOut *-1;
		v = calculateMotorVelocities(x, y);

//		if(y>0){
//			goBackwards(&MD);
//		}else{
//			goForward(&MD);
//		}
		*MD.encA->desiredSpeed =v.V_left; //< 0? -v.V_left : v.V_left ;
		*MD.encB->desiredSpeed =v.V_right; //<0? -v.V_right: v.V_right;

		gradualSetIndividualSpeedRPM(MD.vtA, *MD.encA->motorSpeed);
		gradualSetIndividualSpeedRPM(MD.vtB, *MD.encB->motorSpeed);
		__enable_irq();
		UARTPrintf(pi.uart, "DATA:%d (%d,%d,%d,%d) \n\r",
				PIDUpdateRet,
				(int) (*MD.xcontOut),
				(int) (*MD.ycontOut),
				(int)(*MD.encA->realSpeed),
				(int)(*MD.encB->realSpeed)
				);
//		direction =__HAL_TIM_IS_TIM_COUNTING_DOWN(EncoderA.encoderInputTimer);
		//...
//		HAL_Delay(25); //every 0.05 seconds 1 frame

	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 10;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 10;
  if (HAL_TIM_Encoder_Init(&htim1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 10;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 10;
  if (HAL_TIM_Encoder_Init(&htim2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 16-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = driverSpeed -1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 16-1;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = driverSpeed -1;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 16-1;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = SAMPLE_PERIOD-1;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, MotorBPWMOutput_Pin|MotorAPWM_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, MotorAIn1_Pin|MotorAIn2_Pin|MotorBIn1_Pin|MotorBIn2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : MotorBPWMOutput_Pin MotorAPWM_Pin */
  GPIO_InitStruct.Pin = MotorBPWMOutput_Pin|MotorAPWM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : BOOT1_Pin */
  GPIO_InitStruct.Pin = BOOT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : MotorAIn1_Pin MotorAIn2_Pin MotorBIn1_Pin MotorBIn2_Pin */
  GPIO_InitStruct.Pin = MotorAIn1_Pin|MotorAIn2_Pin|MotorBIn1_Pin|MotorBIn2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
//void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
//	Encoder_IT_Handler(&EncoderA);
//}
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//    if(GPIO_Pin == EncoderA_Pin) // If The INT Source Is EXTI Line9 (A9 Pin)
//    {
//    	int val = HAL_GPIO_ReadPin(EncoderB_GPIO_Port,EncoderB_Pin);
//    	if(val == GPIO_PIN_SET){
//    		encoderValue++;
//    	}else{
//    		encoderValue--;
//    	}
//    }
//}
// Callback: timer has rolled over
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	// Check which version of the timer triggered this callback and toggle LED
	if (htim == MotorATimer.htim) {
//		HAL_GPIO_TogglePin(MotorBPWMOutput_GPIO_Port,  MotorBPWMOutput_Pin);
//		HAL_GPIO_WritePin(MotorBPWMOutput_GPIO_Port, MotorBPWMOutput_Pin, GPIO_PIN_SET);
		VirtualPWM_IT_Handler(&MotorATimer);

	}
	if (htim == MotorBTimer.htim) {
//	HAL_GPIO_TogglePin(MotorAPWM_GPIO_Port,  MotorAPWM_Pin);
//		HAL_GPIO_WritePin(MotorAPWM_GPIO_Port,MotorAPWM_Pin, GPIO_PIN_SET);
		VirtualPWM_IT_Handler(&MotorBTimer);
	}

	if (htim == EncoderA.INT_Timer) {
		Encoder_IT_Handler(&EncoderA);
	}
	if(htim==EncoderB.INT_Timer){
		Encoder_IT_Handler(&EncoderB);
	}

}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
