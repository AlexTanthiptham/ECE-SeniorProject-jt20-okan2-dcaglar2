/*
 * test.c
 *
 *  Created on: Apr 20, 2023
 *      Author: okano
 */


#include "motorDriver.h"
#include  "serial.h"
void TEST_BASIC_FOLLOW(MotorDriver * MD, RPIClient * RPI){
	int THRESH = 10;
	int oldY =0;
	int yDiff =0;
	while(1){
		recieveData(RPI);
		yDiff = RPI->mostRecentPacket->ydistance - oldY;
		yDiff = yDiff < 0 ? -yDiff : yDiff;
		if(yDiff > THRESH ){
			goForward(MD);
			gradualSetSpeed(MD, 75,5);
		}else{
			gradualSetSpeed(MD, 0,5);
			fastStop(MD);

		}
		oldY = RPI->mostRecentPacket->ydistance;
	}
}
void Acceleration_TEST(MotorDriver * MD){
	int i;
	goForward(MD);
	for (i = 0; i < 100; i += 10) {
		*MD->encA->desiredSpeed =i;
		*MD->encB->desiredSpeed =i;
		gradualSetIndividualSpeedRPM(MD->vtA, *MD->encA->motorSpeed);
		gradualSetIndividualSpeedRPM(MD->vtB, *MD->encB->motorSpeed);
		HAL_Delay(500);
	}
	for (i = 100; i > 0; i -= 10) {
		*MD->encA->desiredSpeed =i;
		*MD->encB->desiredSpeed =i;
		gradualSetIndividualSpeedRPM(MD->vtA, *MD->encA->motorSpeed);
		gradualSetIndividualSpeedRPM(MD->vtB, *MD->encB->motorSpeed);
	}
	fastStop(MD);
}

void Echo_TEST(RPIClient * pi){
	while(1){
		UARTScanln(pi->uart, pi->buffer, 256);
		UARTPrintf(pi->uart, "Received: %s \n\r",pi->buffer);
//		HAL_Delay(1000);
	}
}
void PRINT_TEST(RPIClient * pi){
	while(1){
		UARTPrintf(pi->uart, "Poggers Taylor plays amongus\n\r");
		HAL_Delay(1000);
	}
}
void Parser_TEST(RPIClient * pi){
	char buf[] = "3|5";
	RPIPacket p;
	RPIParse(&p,buf);
	UARTPrintf(pi,"(x:%d,y:%d)",p.xdistance,p.ydistance);
}
void DATA_TEST(RPIClient * pi){
	int bufferSize = 128;
	while(1){
		recieveData(pi);
		UARTPrintf(pi->uart, "Received: (%d,%d) \n\r",pi->mostRecentPacket->xdistance,pi->mostRecentPacket->ydistance);
	}
}
