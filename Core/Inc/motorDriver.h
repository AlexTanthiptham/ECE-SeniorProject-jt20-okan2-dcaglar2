/*
 * motorDriver.h
 *
 *  Created on: Feb 23, 2023
 *      Author: okano
 */

#ifndef SRC_MOTORDRIVE_MOTORDRIVER_H_
#define SRC_MOTORDRIVE_MOTORDRIVER_H_
typedef struct {
    int speed;
    // other attributes of the motor driver could be added here
} MotorDriver;
MotorDriver * MotorDriverInit();
void goForward(MotorDriver* motorDriver);
void goLeft(MotorDriver* motorDriver);
void goRight(MotorDriver* motorDriver);
void goBackwards(MotorDriver* motorDriver);



#endif /* SRC_MOTORDRIVE_MOTORDRIVER_H_ */
