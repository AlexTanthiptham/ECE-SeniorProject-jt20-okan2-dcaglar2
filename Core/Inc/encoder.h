/*
 * encoder.h
 *
 *  Created on: Apr 21, 2023
 *      Author: okano
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_
#include "stm32f4xx_hal.h"
#include "pid.h"
typedef struct{
	int lastCounterValue;
	float distance;
	int counterValue;
	float lastMeasurement;
	int sampleRate;
	int sampleCount;
	int sampleSum;
	double *realSpeed;
	double * desiredSpeed;
	double * motorSpeed;
	PID_TypeDef *speedController;
	TIM_HandleTypeDef * INT_Timer;
	TIM_HandleTypeDef * encoderInputTimer;
//	VirtualTimer * vt;
} Encoder;
void initEncoder(Encoder * enc, TIM_HandleTypeDef * intTIM,
		TIM_HandleTypeDef * InputTIM,PID_Params pidParams);
int getCounter(Encoder * enc);
float getVelocity(Encoder * enc);
float getDistance(Encoder * enc);
void Encoder_IT_Handler(Encoder * enc);

#define COUNTER_TO_ANGLE 360.0/478.0
#define INT_PERIOD  1/1000.0
#define INT_FREQ 1000.0
#define PI 3.14
#define DEG_TO_RAD  PI/ 180
#define WHEEL_RADIUS_INCH  3 //inch
#define WHEEL_RADIUS_CM WHEEL_RADIUS_INCH * 2.54 //cm
#endif /* INC_ENCODER_H_ */
