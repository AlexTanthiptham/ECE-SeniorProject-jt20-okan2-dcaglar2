/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ENCODER_MAX 65535/2
#define driverSpeed 100
#define SAMPLE_PERIOD 1000
#define MotorBPWMOutput_Pin GPIO_PIN_2
#define MotorBPWMOutput_GPIO_Port GPIOA
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define MotorAIn1_Pin GPIO_PIN_6
#define MotorAIn1_GPIO_Port GPIOC
#define MotorAIn2_Pin GPIO_PIN_7
#define MotorAIn2_GPIO_Port GPIOC
#define MotorBIn1_Pin GPIO_PIN_8
#define MotorBIn1_GPIO_Port GPIOC
#define MotorBIn2_Pin GPIO_PIN_9
#define MotorBIn2_GPIO_Port GPIOC
#define MotorAPWM_Pin GPIO_PIN_10
#define MotorAPWM_GPIO_Port GPIOA
#define RPI_TX_Pin GPIO_PIN_6
#define RPI_TX_GPIO_Port GPIOB
#define RPI_RX_Pin GPIO_PIN_7
#define RPI_RX_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
