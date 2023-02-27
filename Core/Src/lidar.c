/*
 * lidar.c
 *
 *  Created on: Feb 26, 2023
 *      Author: okano
 */

#include "lidar.h"
#include "main.h"
int lidarInit(LIDAR *lidar, I2C_HandleTypeDef *port) {
	uint8_t cmd[1];
	lidar->port = port;
	cmd[0] = 0x04;
	return 0;
//	return HAL_I2C_Mem_Write(lidar->port, LIDAR_WRITE_ADD, 0x00, 1, cmd, 1, 0x100);
//	return 0;

}
void waitTillFree(LIDAR *lidar) {
	int timeoutCounter = 0;
	while (getStatus(lidar)) {
		if (timeoutCounter > MAX_LIDAR_TIMEOUT) {
			return 0;
		}
		timeoutCounter++;
		HAL_Delay(20);
	}
}
int configLidar(LIDAR *lidar, int configversion) {
	uint8_t cmd[1];
	HAL_StatusTypeDef ret;
	waitTillFree(lidar);
	switch (configversion) {
	case 0: // Default configuration
		cmd[0] = 0x00;
		ret = HAL_I2C_Mem_Write(lidar->port, LIDAR_WRITE_ADD, (uint16_t) 0x00,
				I2C_MEMADD_SIZE_8BIT, cmd, 2, 100);
		break;
	case 1: // Set aquisition count to 1/3 default value, faster reads, slightly noisier values
		cmd[0] = 0x00;
		ret = HAL_I2C_Mem_Write(lidar->port, LIDAR_WRITE_ADD, (uint16_t) 0x04,
				I2C_MEMADD_SIZE_8BIT, cmd, 2, 100);
		break;
	case 2: // Low noise, low sensitivity: Pulls decision criteria higher above the noise, allows fewer false detections, reduces sensitivity
		cmd[0] = 0x20;
		ret = HAL_I2C_Mem_Write(lidar->port, LIDAR_WRITE_ADD, (uint16_t) 0x1c,
				I2C_MEMADD_SIZE_8BIT, cmd, 2, 100);
		break;
	case 3: // High noise, high sensitivity: Pulls decision criteria into the noise, allows more false detections, increses sensitivity
		cmd[0] = 0x60;
		ret = HAL_I2C_Mem_Write(lidar->port, LIDAR_WRITE_ADD, (uint16_t) 0x1c,
				I2C_MEMADD_SIZE_8BIT, cmd, 2, 100);
		break;
	}
	return ret;

}
int getStatus(LIDAR *lidar) {
	uint8_t cmd[1];
	uint8_t data[1] = { 0 };
	HAL_StatusTypeDef ret;
	cmd[0] = 0x01;
	ret = HAL_I2C_Master_Transmit(lidar->port, LIDAR_ADD, cmd, 1, 100);
	if (ret != HAL_OK) {
		return -1;
	}
	ret = HAL_I2C_Master_Receive(lidar->port, LIDAR_READ_ADD, data, 1, 100);
	if (ret != HAL_OK) {
		return -1;
	}
	return data[0] & 0x01;
}

int getDistance(LIDAR *lidar) {
	int distance;
	uint8_t upper,lower;
	uint8_t cmd[1];
	uint8_t data[2] = { 10 };
	HAL_StatusTypeDef ret;
    cmd[0] = 0x04;
	ret = HAL_I2C_Mem_Write(lidar->port,LIDAR_ADD ,0x00,1,cmd,1,100);
	HAL_Delay(20);
	ret = HAL_I2C_Mem_Read(lidar->port,LIDAR_ADD, 0x00,1,data,1,100);
	HAL_Delay(20);
	cmd[0]=0x8f;
	ret = HAL_I2C_Master_Transmit(lidar->port,LIDAR_ADD,cmd,1,100);
	HAL_Delay(20);
	ret = HAL_I2C_Master_Receive(lidar->port,LIDAR_ADD,data,2,100);
	return (data[0]<<8)|(data[1]);
}

