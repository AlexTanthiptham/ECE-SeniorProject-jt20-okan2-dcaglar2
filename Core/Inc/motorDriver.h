/*
 * motorDriver.h
 *
 *  Created on: Feb 23, 2023
 *      Author: okano
 */

#ifndef SRC_MOTORDRIVE_MOTORDRIVER_H_
#define SRC_MOTORDRIVE_MOTORDRIVER_H_
#include "pid.h"
#define CONTROLLER_SAMPLE_RATE 500
#define CONTROLLER_OUTPUT_LIMIT 100
#define TARGET_DISTANCE 100
#define Kp 1
#define Kd 1
#define Ki 1
typedef struct {
	double *xdistance;
	double *ydistance;
	double *xcontOut;
	double *ycontOut;
	PID_TypeDef *X_Controller;
	PID_TypeDef *Y_Controller;

	// other attributes of the motor driver could be added here
} MotorDriver;
void MotorDriverInit(MotorDriver *driver, int *xdist, int *ydist, int *xout,
		float *yout, PID_TypeDef *xctrl, PID_TypeDef *yctrl);
void initPIDController(PID_TypeDef *cont, int *inputVar, int *outputVar,
		int steadyState);
void goForward(MotorDriver *motorDriver);
void goLeft(MotorDriver *motorDriver);
void goRight(MotorDriver *motorDriver);
void goBackwards(MotorDriver *motorDriver);
void motorDriverUpdate(MotorDriver * motorDriver);

#endif /* SRC_MOTORDRIVE_MOTORDRIVER_H_ */
