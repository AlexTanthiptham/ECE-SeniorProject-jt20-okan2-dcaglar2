/*
 * motorDriver.c
 *
 *  Created on: Feb 23, 2023
 *      Author: okano
 */

#include "main.h"
#include "motorDriver.h"
MotorDriver * MotorDriverInit(){
	MotorDriver temp;
	return &temp;
}
void goForward(MotorDriver* motorDriver) {
    // code to make the motor driver move forward

	HAL_GPIO_WritePin(MotorAIn1_GPIO_Port, MotorAIn1_Pin, 1);
	HAL_GPIO_WritePin(MotorAIn2_GPIO_Port, MotorAIn2_Pin, 0);
	HAL_GPIO_WritePin(MotorBIn1_GPIO_Port, MotorBIn1_Pin, 1);
	HAL_GPIO_WritePin(MotorBIn2_GPIO_Port, MotorBIn2_Pin, 0);

}

void fastStop(MotorDriver * motorDriver){
	HAL_GPIO_WritePin(MotorAIn1_GPIO_Port, MotorAIn1_Pin, 0);
	HAL_GPIO_WritePin(MotorAIn2_GPIO_Port, MotorAIn2_Pin, 0);
	HAL_GPIO_WritePin(MotorBIn1_GPIO_Port, MotorBIn1_Pin, 0);
	HAL_GPIO_WritePin(MotorBIn2_GPIO_Port, MotorBIn2_Pin, 0);
}
void goLeft(MotorDriver* motorDriver) {
    // code to make the motor driver turn left
}

void goRight(MotorDriver* motorDriver) {
    // code to make the motor driver turn right
}

void goBackwards(MotorDriver* motorDriver) {
    // code to make the motor driver move backwards
	HAL_GPIO_WritePin(MotorAIn1_GPIO_Port, MotorAIn1_Pin, 0);
	HAL_GPIO_WritePin(MotorAIn2_GPIO_Port, MotorAIn2_Pin, 1);
	HAL_GPIO_WritePin(MotorBIn1_GPIO_Port, MotorBIn1_Pin, 0);
	HAL_GPIO_WritePin(MotorBIn2_GPIO_Port, MotorBIn2_Pin, 1);
}




