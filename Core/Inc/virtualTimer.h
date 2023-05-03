/*
 * virtualTimer.h
 *
 *  Created on: Apr 19, 2023
 *      Author: okano
 */

#ifndef INC_VIRTUALTIMER_H_
#define INC_VIRTUALTIMER_H_

#include "stm32f4xx_hal.h"
typedef struct {
	volatile int timerCount;
	int timerPeriod; //driverSpeed
	float dutyCycle;
	int updateFlag;
	int timerStepDownCount;
	uint16_t outputChannelPin;
	GPIO_TypeDef * outputChannelPort;
	TIM_HandleTypeDef * htim;
} VirtualTimer;
void initVirtualTimer(VirtualTimer *vt, int timerPeriod, float dutyCycle, GPIO_TypeDef *outputChannelPort,
		uint16_t outputChannelPin,TIM_HandleTypeDef * htim);
void VirtualPWM_IT_Handler(VirtualTimer * vt);
void setDutyCycle(VirtualTimer * vt, float amount);
void gradualSetDutyCycle(VirtualTimer *vt, float amount, int stepSize);
void start_IT(VirtualTimer * vt);
#endif /* INC_VIRTUALTIMER_H_ */
