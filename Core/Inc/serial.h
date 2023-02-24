/*
 * serial.h
 *
 *  Created on: Feb 24, 2023
 *      Author: okano
 */

typedef struct{
	UART_HandleTypeDef * port;
} UARTClient;
UARTClient UARTClientInit(UART_HandleTypeDef*  port);
void UARTPrintf(UARTClient * client, char *formattedString,...);
void UARTPrintln(UARTClient * client,  char *formattedString,...);
