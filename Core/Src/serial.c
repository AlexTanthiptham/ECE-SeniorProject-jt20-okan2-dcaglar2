/*
 * serial.c
 *
 *  Created on: Feb 24, 2023
 *      Author: okano
 */


#include <stdio.h>
#include <stdarg.h>
#include <main.h>
#include "serial.h"


void UARTPrintf(UARTClient * client,  char *formattedString,...){
    char  str[80]= "";

    /*Extract the the argument list using VA apis */
    va_list args;
    va_start(args, formattedString);
    vsprintf(str, formattedString,args);
    va_end(args);
    HAL_UART_Transmit(client->port, (uint8_t * )str, sizeof(str),HAL_MAX_DELAY);


}

void UARTPrintln(UARTClient * client, char *formattedString,...){
	UARTPrintf(client, "%s\n\r",formattedString);
}
