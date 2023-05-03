/*
 * motorDriver.h
 *
 *  Created on: Feb 23, 2023
 *      Author: okano
 */

#ifndef SRC_MOTORDRIVE_MOTORDRIVER_H_
#define SRC_MOTORDRIVE_MOTORDRIVER_H_
#include "pid.h"
#include "virtualTimer.h"
#include "stm32f4xx_hal.h"
#include "encoder.h"
#define CONTROLLER_SAMPLE_RATE 100
#define CONTROLLER_SAMPLE_PERIOD CONTROLLER_SAMPLE_RATE/1000.0
#define CONTROLLER_SAMPLE_FREQ 1000.0/CONTROLLER_SAMPLE_RATE
#define CONTROLLER_OUTPUT_LIMIT 100
#define TARGET_DISTANCE 100.0
#define KpY 0.01 //0.5 good
#define KdY 0.05//0.05 //0.125
#define KiY 1.5//good:1.5 // 1.7
#define KpX 0.5//0.5 good
#define KdX 0 //0.125
#define KiX 0 // 1.7
#define PI 3.14
typedef struct{
	double V_left;
	double V_right;
} Velocity;
typedef struct {
	double *xdistance;
	double *ydistance;
	double *xcontOut;
	double *ycontOut;
	double * steadyState;
	PID_TypeDef *X_Controller;
	PID_TypeDef *Y_Controller;
	VirtualTimer * vtA;
	VirtualTimer * vtB;
	Encoder * encA;
	Encoder * encB;

	// other attributes of the motor driver could be added here
} MotorDriver;
#define MAX_SPEED_RPM 131.0 //rpm
#define MAX_SPEED 60//90//(int)((MAX_SPEED_RPM/60.0)* (2.0*PI*WHEEL_RADIUS_CM)) //cm/s
#define INV_MAX_SPEED 1.0/MAX_SPEED
void MotorDriverInit(MotorDriver *driver, double *xdist, double *ydist, double *xout,
		double *yout,double * ssX,double * ssY, PID_TypeDef *xctrl, PID_TypeDef *yctrl, VirtualTimer * vtA, VirtualTimer * vtB);
void initPIDController(PID_TypeDef *cont, double *inputVar, double *outputVar,
		double * steadyState);
void goForward(MotorDriver *motorDriver);
void goLeft(MotorDriver *motorDriver);
void goRight(MotorDriver *motorDriver);
void goBackwards(MotorDriver *motorDriver);
int motorDriverUpdate(MotorDriver * motorDriver);
void setOverallSpeed(MotorDriver * motorDriver,double speedInCMpS);
void gradualSetSpeed(MotorDriver * MD,int amount, int stepSize);
void gradualSetIndividualSpeedRPM(VirtualTimer * vt, double rpm);
Velocity calculateMotorVelocities(double x, double y);
void Encoder_TRAIN(MotorDriver * MD);
#endif /* SRC_MOTORDRIVE_MOTORDRIVER_H_ */
