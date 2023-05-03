/*
 * serial.c
 *
 *  Created on: Feb 24, 2023
 *      Author: okano
 */
#include "serial.h"
#include <stdio.h>
#include <stdarg.h>


void UARTPrintf(UARTClient *client, char *formattedString, ...) {
	char str[32] = "";
	/*Extract the the argument list using VA apis */
	va_list args;
	va_start(args, formattedString);
	vsprintf(str, formattedString, args);
	va_end(args);
	HAL_UART_Transmit(client->port, (uint8_t*) str, sizeof(str), HAL_MAX_DELAY);

}

void UARTPrintln(UARTClient *client, char *formattedString, ...) {
	UARTPrintf(client, "%s\n\r", formattedString);
}

int UARTScanln(UARTClient *client, char *buffer, uint16_t bufferSize) {
	uint8_t ch;
	uint16_t count = 0;
	HAL_StatusTypeDef ret;
	// Clear the buffer
	memset(buffer, 0, bufferSize);

	while (1) {
		// Wait until a character is received
		ret = HAL_UART_Receive(client->port, &ch, 1,UART_TIMEOUT);
		if(ret !=HAL_OK){
			return ret;
		}

		// If a newline character is received, exit the loop
		if (ch == '\n') {
			break;
		}

		// If the buffer is full, exit the loop
		if (count >= (bufferSize - 1)) {
			break;
		}

		// Update the buffer with the received character
		buffer[count] = ch;
		count++;
	}
	return HAL_OK;
}
void RPIParse(RPIPacket *packet, char *RPIInputBuffer) {
	int bufferSize = strlen(RPIInputBuffer);
	int i;
	int charIdx = 0;
	int packetItemIdx = 0;
	char currentString[bufferSize];
	char SeperatedBuffer[PACKET_SIZE][bufferSize];
	for (i = 0; i < bufferSize; i++) {
		if (RPIInputBuffer[i] == SEPERATOR) {
			strncpy(SeperatedBuffer[packetItemIdx], currentString, charIdx);
			charIdx = 0;
			packetItemIdx++;
			continue;
		}
		currentString[charIdx] = RPIInputBuffer[i];
		charIdx++;
	}
	strncpy(SeperatedBuffer[packetItemIdx], currentString, charIdx);
	packet->xdistance = atoi(SeperatedBuffer[0]);
	packet->ydistance = atoi(SeperatedBuffer[1]);
}
void RPIClientInit(RPIClient *client, char *buffer, RPIPacket *mostRecentPacket,
		UARTClient *uart) {
	client->buffer = buffer;
	client->mostRecentPacket = mostRecentPacket;
	client->uart = uart;
}
int recieveData(RPIClient *pi) {
	int ret;
	ret = UARTScanln(pi->uart, pi->buffer, RPI_BUFFER_SIZE);
	if(ret!=HAL_OK){return ret;}
	RPIParse(pi->mostRecentPacket, pi->buffer);
	pi->mostRecentPacket->timestamp = HAL_GetTick();
	return HAL_OK;
}
