/*
 * serial.h
 *
 *  Created on: Apr 20, 2023
 *      Author: okano
 */

#ifndef INC_SERIAL_H_
#define INC_SERIAL_H_
#include "stm32f4xx_hal.h"
typedef struct {
	UART_HandleTypeDef *port;
} UARTClient;
typedef struct {
	int xdistance;
	int ydistance;
	int timestamp;
} RPIPacket;
typedef struct {
	char *buffer;
	RPIPacket *mostRecentPacket;
	UARTClient *uart;
} RPIClient;

//UARTClient UARTClientInit(UART_HandleTypeDef *port);

#define PACKET_SIZE 2
#define SEPERATOR '|'
#define RPI_BUFFER_SIZE 128
#define UART_TIMEOUT 2000
void UARTPrintf(UARTClient * client, char *formattedString, ...);
void UARTPrintln(UARTClient * client, char *formattedString, ...);
int UARTScanln(UARTClient * client, char *buffer, uint16_t bufferSize);
void RPIParse(RPIPacket * packet, char * RPIInputBuffer);
void RPIClientInit(RPIClient *client, char *buffer, RPIPacket *mostRecentPacket, UARTClient *uart);
int recieveData(RPIClient * pi);


#endif /* INC_SERIAL_H_ */
