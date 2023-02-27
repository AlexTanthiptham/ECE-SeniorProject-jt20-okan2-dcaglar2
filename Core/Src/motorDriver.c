/*
 * motorDriver.c
 *
 *  Created on: Feb 23, 2023
 *      Author: okano
 */

#include "main.h"
#include "motorDriver.h"
#include "pid.h"
void MotorDriverInit(MotorDriver *driver, int *xdist, int *ydist, int *xout,
		float *yout, PID_TypeDef *xctrl, PID_TypeDef *yctrl) {
	driver->xdistance = xdist;
	driver->ydistance = ydist;
	driver->xcontOut = xout;
	driver->ycontOut = yout;
	driver->X_Controller = xctrl;
	driver->Y_Controller = yctrl;
	initPIDController(driver->X_Controller, driver->xdistance, driver->xcontOut, 0);
	initPIDController(driver->Y_Controller, driver->ydistance, driver->ycontOut,
			TARGET_DISTANCE);
}
void initPIDController(PID_TypeDef *cont, int *inputVar, int *outputVar,
		int steadyState) {
	PID(cont, inputVar, outputVar, steadyState, Kp, Ki, Kd, _PID_P_ON_E,
			_PID_CD_DIRECT);
	PID_SetMode(cont, _PID_MODE_AUTOMATIC);
	PID_SetSampleTime(cont, CONTROLLER_SAMPLE_RATE);
	PID_SetOutputLimits(cont, 1, CONTROLLER_OUTPUT_LIMIT);
}
void motorDriverUpdate(MotorDriver * motorDriver){
	PID_Compute(motorDriver->X_Controller);
	PID_Compute(motorDriver->Y_Controller);
}
void goForward(MotorDriver *motorDriver) {
	// code to make the motor driver move forward

	HAL_GPIO_WritePin(MotorAIn1_GPIO_Port, MotorAIn1_Pin, 1);
	HAL_GPIO_WritePin(MotorAIn2_GPIO_Port, MotorAIn2_Pin, 0);
	HAL_GPIO_WritePin(MotorBIn1_GPIO_Port, MotorBIn1_Pin, 1);
	HAL_GPIO_WritePin(MotorBIn2_GPIO_Port, MotorBIn2_Pin, 0);

}

void fastStop(MotorDriver *motorDriver) {
	HAL_GPIO_WritePin(MotorAIn1_GPIO_Port, MotorAIn1_Pin, 0);
	HAL_GPIO_WritePin(MotorAIn2_GPIO_Port, MotorAIn2_Pin, 0);
	HAL_GPIO_WritePin(MotorBIn1_GPIO_Port, MotorBIn1_Pin, 0);
	HAL_GPIO_WritePin(MotorBIn2_GPIO_Port, MotorBIn2_Pin, 0);
}
void goLeft(MotorDriver *motorDriver) {
	// code to make the motor driver turn left
}

void goRight(MotorDriver *motorDriver) {
	// code to make the motor driver turn right
}

void goBackwards(MotorDriver *motorDriver) {
	// code to make the motor driver move backwards
	HAL_GPIO_WritePin(MotorAIn1_GPIO_Port, MotorAIn1_Pin, 0);
	HAL_GPIO_WritePin(MotorAIn2_GPIO_Port, MotorAIn2_Pin, 1);
	HAL_GPIO_WritePin(MotorBIn1_GPIO_Port, MotorBIn1_Pin, 0);
	HAL_GPIO_WritePin(MotorBIn2_GPIO_Port, MotorBIn2_Pin, 1);
}

