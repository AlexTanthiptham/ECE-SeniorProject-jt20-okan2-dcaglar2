/*
 * virtualTimer.c
 *
 *  Created on: Apr 19, 2023
 *      Author: okano
 */

#include "virtualTimer.h"

void initVirtualTimer(VirtualTimer *vt, int timerPeriod, float dutyCycle,
		GPIO_TypeDef *outputChannelPort, uint16_t outputChannelPin,
		TIM_HandleTypeDef *htim) {
	vt->timerCount = 0;
	vt->timerPeriod = timerPeriod; //driverSpeed
	vt->dutyCycle = dutyCycle;
	vt->timerStepDownCount = (int) (vt->dutyCycle * vt->timerPeriod);
	vt->outputChannelPort = outputChannelPort;
	vt->outputChannelPin = outputChannelPin;
	vt->htim = htim;


}
void VirtualPWM_IT_Handler(VirtualTimer *vt) {
	__disable_irq();
	if (vt->updateFlag) {
		vt->timerStepDownCount = (int) (vt->dutyCycle * vt->timerPeriod);
		vt->updateFlag = 0;
		__enable_irq();
		return;
	}
	if (vt->timerCount <= vt->timerStepDownCount) {
		HAL_GPIO_WritePin(vt->outputChannelPort, vt->outputChannelPin,
				GPIO_PIN_SET);
	}
	if (vt->timerCount > vt->timerStepDownCount) {
		HAL_GPIO_WritePin(vt->outputChannelPort, vt->outputChannelPin,
				GPIO_PIN_RESET);
	}
	if (vt->timerCount == vt->timerPeriod) {
		vt->timerCount = 0;
		__enable_irq();
		return;
	}
	vt->timerCount++;
	__enable_irq();
}
void setDutyCycle(VirtualTimer *vt, float amount) {
	vt->dutyCycle = amount;
	__disable_irq();
	vt->updateFlag = 1;
	__enable_irq();
}
void gradualSetDutyCycle(VirtualTimer *vt, float amount, int stepSize){
	float currentDutyCycle = vt->dutyCycle;
	float step;
	float adjustedStepSize = stepSize/100.0;
	//increase
	if(currentDutyCycle < amount){
		for(step = currentDutyCycle; step < amount; step+=adjustedStepSize){
			setDutyCycle(vt, step);
		}
	}else if(currentDutyCycle > amount){ //decrease
		for(step = currentDutyCycle; step  > amount; step-=adjustedStepSize){
			setDutyCycle(vt, step);
		}
	}else{
		return;
	}



}
void start_IT(VirtualTimer * vt){
	HAL_TIM_Base_Start_IT(vt->htim);
}

