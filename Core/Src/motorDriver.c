/*
 * motorDriver.c
 *
 *  Created on: Feb 23, 2023
 *      Author: okano
 */

#include "main.h"
#include "motorDriver.h"
#include "pid.h"
#include "math.h"
#include  "encoder.h"
void MotorDriverInit(MotorDriver *driver, double *xdist, double *ydist,
		double *xout, double *yout, double *ssX, double *ssY,
		PID_TypeDef *xctrl, PID_TypeDef *yctrl, VirtualTimer *vtA,
		VirtualTimer *vtB) {
	driver->xdistance = xdist;
	driver->ydistance = ydist;
	driver->xcontOut = xout;
	driver->ycontOut = yout;
	driver->X_Controller = xctrl;
	driver->Y_Controller = yctrl;
	driver->vtA = vtA;
	driver->vtB = vtB;
//	driver->steadyStateX = ssX;
	PID(driver->X_Controller, driver->xdistance, driver->xcontOut, ssX, KpX, KiX, KdX, _PID_P_ON_E,
			_PID_CD_DIRECT);
	PID(driver->Y_Controller, driver->ydistance, driver->ycontOut,
			ssY, KpY, KiY, KdY, _PID_P_ON_E,
			_PID_CD_DIRECT);
	initPIDController(driver->X_Controller, driver->xdistance, driver->xcontOut,
			ssX);
	initPIDController(driver->Y_Controller, driver->ydistance, driver->ycontOut,
			ssY);
	PID_SetOutputLimits(driver->X_Controller, -30, 30);
//	PID_SetOutputLimits(driver->Y_Controller, -100.0, 100.0);
	PID_SetOutputLimits(driver->Y_Controller, -30.0, 0);
//	PID_SetOutputLimits(driver->X_Controller, 0, 100);
//	PID_SetOutputLimits(driver->Y_Controller, -370, 370);
}
void initPIDController(PID_TypeDef *cont, double *inputVar, double *outputVar,
		double *steadyState) {
//	PID(cont, inputVar, outputVar, steadyState, Kp, Ki, Kd, _PID_P_ON_E,
//			_PID_CD_DIRECT);
	PID_SetMode(cont, _PID_MODE_AUTOMATIC);
	PID_SetSampleTime(cont, CONTROLLER_SAMPLE_RATE);
//	PID_SetOutputLimits(cont, 1, CONTROLLER_OUTPUT_LIMIT);
}
int motorDriverUpdate(MotorDriver *motorDriver) {
	int retX, retY;
	retX = PID_Compute(motorDriver->X_Controller);
	retY = PID_Compute(motorDriver->Y_Controller);
	return retX && retY;
}
void goBackwards(MotorDriver *motorDriver) {
	// code to make the motor driver move forward

	HAL_GPIO_WritePin(MotorAIn1_GPIO_Port, MotorAIn1_Pin, 0);
	HAL_GPIO_WritePin(MotorAIn2_GPIO_Port, MotorAIn2_Pin, 1);
	HAL_GPIO_WritePin(MotorBIn1_GPIO_Port, MotorBIn1_Pin, 0);
	HAL_GPIO_WritePin(MotorBIn2_GPIO_Port, MotorBIn2_Pin, 1);

}

void fastStop(MotorDriver *motorDriver) {
	HAL_GPIO_WritePin(MotorAIn1_GPIO_Port, MotorAIn1_Pin, 0);
	HAL_GPIO_WritePin(MotorAIn2_GPIO_Port, MotorAIn2_Pin, 0);
	HAL_GPIO_WritePin(MotorBIn1_GPIO_Port, MotorBIn1_Pin, 0);
	HAL_GPIO_WritePin(MotorBIn2_GPIO_Port, MotorBIn2_Pin, 0);
}
void gradualSetIndividualSpeedRPM(VirtualTimer *vt, double rpm) {
	if(rpm <0){
		gradualSetDutyCycle(vt, 0, 5);
		return;
	}
	if(rpm > MAX_SPEED){
		rpm = MAX_SPEED;
	}
	double percentage = rpm /MAX_SPEED;
	gradualSetDutyCycle(vt, percentage, 5);
}
void goForward(MotorDriver *motorDriver) {
	// code to make the motor driver move backwards
	HAL_GPIO_WritePin(MotorAIn1_GPIO_Port, MotorAIn1_Pin, 1); //0
	HAL_GPIO_WritePin(MotorAIn2_GPIO_Port, MotorAIn2_Pin, 0); //1
	HAL_GPIO_WritePin(MotorBIn1_GPIO_Port, MotorBIn1_Pin, 1);//0
	HAL_GPIO_WritePin(MotorBIn2_GPIO_Port, MotorBIn2_Pin, 0); //1
}

void setOverallSpeed(MotorDriver *motorDriver, double speedInCMpS) {
	double percentage = speedInCMpS /MAX_SPEED;
	setDutyCycle(motorDriver->vtA, percentage);
	setDutyCycle(motorDriver->vtB,  percentage);

}

void gradualSetSpeed(MotorDriver *MD, int amount, int stepSize) {
	gradualSetDutyCycle(MD->vtA, amount / 100.0, stepSize);
	gradualSetDutyCycle(MD->vtB, amount / 100.0, stepSize);
}
void takeOff(MotorDriver *MD) {
	goForward(MD);
	setOverallSpeed(MD, 100);
	HAL_Delay(3000);
	gradualSetSpeed(MD, 75, 5);
}
#define MIN_ROTATION -PI/36.0
#define MAX_ROTATION PI/36.0
Velocity calculateMotorVelocities(double x, double y) {
	int l = 30;// cm
	int r= 15;//cm
//	double rotation_angle= y >0 ? atan(x/y) :0;
	double rotation_angle =0;
	double V_o = 0;
	double V_l =0;
	double V_r=0;
	Velocity v;
	if (rotation_angle > MIN_ROTATION && rotation_angle < MAX_ROTATION) {
		//ignore x
		V_o = y * CONTROLLER_SAMPLE_FREQ;
		V_l = V_o;
		V_r = V_l;
	} else {
		//if x > 0  go left aka left motor turn more
		if(x>0){
			V_r = rotation_angle * r *CONTROLLER_SAMPLE_FREQ;
			V_l = rotation_angle * (r + l) * CONTROLLER_SAMPLE_FREQ;
		}else{ //x <0 aka right motor turn more
			V_l = -rotation_angle * r *CONTROLLER_SAMPLE_FREQ;
			V_r = -rotation_angle * (r + l) * CONTROLLER_SAMPLE_FREQ;
		}

	}
	v.V_left = V_l;
	v.V_right = V_r;
	return v;
}
void Encoder_TRAIN(MotorDriver * MD){
	int i=0;
	fastStop(MD);
	setOverallSpeed(MD,0.5);
//	*MD->enc->desiredSpeed =0.5;
	goForward(MD);
	HAL_Delay(5000);
//	while (1){};
}

