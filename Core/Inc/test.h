/*
 * test.h
 *
 *  Created on: Apr 20, 2023
 *      Author: okano
 */

#ifndef INC_TEST_H_
#define INC_TEST_H_
#include "motorDriver.h"
#include "serial.h"
void TEST_BASIC_FOLLOW(MotorDriver * MD, RPIClient * RPI);
void Acceleration_TEST(MotorDriver * MD);
void Echo_TEST(RPIClient* pi);
void Parser_TEST(RPIClient * pi);
void PRINT_TEST(RPIClient * pi);
#endif /* INC_TEST_H_ */
