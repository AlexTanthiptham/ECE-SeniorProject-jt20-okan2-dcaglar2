/*
 * lidar.h
 *
 *  Created on: Feb 26, 2023
 *      Author: okano
 */


#ifndef LIDAR_H
#define LIDAR_H

#include "main.h"
#define LIDAR_WRITE_ADD  0xC4
#define LIDAR_READ_ADD 0xC5
#define LIDAR_ADD (uint8_t)(0x62 << 1)
#define MAX_LIDAR_TIMEOUT 10
/* Default I2C Address of LIDAR-Lite. */
#define LIDARLite_WriteAdr  0xc4    /// 8-bit slave write address
#define LIDARLite_ReadAdr   0xc5    /// 8-bit slave read address

/* Commands */
#define SET_CommandReg       0x00   /// Register to write to initiate ranging
#define AcqMode              0x04   /// Value to set in control register to initiate ranging

/* Read Registers */
#define GET_DistanceHBReg    0x0f   /// High byte of distance reading data
#define GET_DistanceLBReg    0x10   /// Low byte of distance reading data
#define GET_Distance2BReg    0x8f   /// Register to get both High and Low bytes of distance reading data in 1 call
#define GET_VelocityReg      0x09   /// Velocity measutement data
typedef struct {
    I2C_HandleTypeDef *port;
} LIDAR;

int lidarInit(LIDAR *lidar, I2C_HandleTypeDef *port);
int configLidar(LIDAR *lidar, int configversion);
int getStatus(LIDAR *lidar);
int getDistance(LIDAR *lidar);


#define LIDAR_COMMAND_CONTROL_REG         0x00
#define LIDAR_SYSTEM_STATUS_REG           0x01
#define LIDAR_MAX_ACQUISITION_COUNT_REG   0x02
#define LIDAR_CORRELATION_RECORD_LEN_REG  0x03
#define LIDAR_ACQUISITION_MODE_CTRL_REG   0x04
#define LIDAR_MEASURED_THRESH_OFFSET_REG  0x05
#define LIDAR_MEASURED_DELAY_REF_REG      0x06
#define LIDAR_MEASURED_DELAY_REF_MSB_REG  0x07
#define LIDAR_REF_CORREL_MEASURED_PEAK_REG 0x08
#define LIDAR_VELOCITY_MEASURED_OUTPUT_REG 0x09
#define LIDAR_MEASURED_DELAY_SIGNAL_RET_REG 0x0A
#define LIDAR_MEASURED_DELAY_SIGNAL_RET_MSB_REG 0x0B
#define LIDAR_SIGNAL_CORREL_MEASURED_PEAK_REG 0x0C
#define LIDAR_CORREL_RECORD_NOISE_FLOOR_REG 0x0D
#define LIDAR_RECEIVED_SIGNAL_STRENGTH_REG 0x0E
#define LIDAR_CALCULATED_DISTANCE_REG     0x0F
#define LIDAR_CALCULATED_DISTANCE_MSB_REG 0x10
#define LIDAR_DC_THRESHOLD_COMMAND_REG    0x11
#define LIDAR_DELAY_TO_REDUCE_BURST_FREQ_REG 0x12
#define LIDAR_DISTANCE_CALIBRATION_REG    0x13
#define LIDAR_PREVIOUS_MEASURED_DIST_REG  0x14
#define LIDAR_PREVIOUS_MEASURED_DIST_MSB_REG 0x15
#define LIDAR_COMMAND_REG 0x40
#define LIDAR_HW_VERSION_REG 0x41
#define LIDAR_PREAMP_DC_CTRL_REG 0x42
#define LIDAR_TX_POWER_CTRL_REG 0x43
#define LIDAR_PROCESSING_RANGE_GATE_LOW_REG 0x44
#define LIDAR_PROCESSING_RANGE_GATE_HIGH_REG 0x45
#define LIDAR_RANGE_MEASUREMENT_PWM_OUTPUT_REG 0x46
#define LIDAR_ACQUISITION_STATUS_REG 0x47
#define LIDAR_MEASURED_PREAMP_DC_OFFSET_REG 0x49
#define LIDAR_OUTPUT_PORT_REG 0x4a
#define LIDAR_RANGE_PROCESSING_CRITERIA_REG 0x4b
#define LIDAR_SECOND_LARGEST_PEAK_REG 0x4c
#define LIDAR_SOFTWARE_VERSION_REG 0x4f
#define LIDAR_CORRELATION_RECORD_SIZE_SELECT_REG 0x51
#define LIDAR_CORRELATION_DATA_ACCESS_PORT_LOW_REG 0x52
#define LIDAR_ACQUISITION_SETTINGS_REG 0x53
#define LIDAR_MEASURED_DELAY_OF_REF_SIGNAL_REG 0x57
#define LIDAR_MEASURED_DELAY_OF_SIGNAL_REG 0x58
#define LIDAR_CORRELATION_PEAK_VALUE_OF_REF_SIGNAL_REG 0x59
#define LIDAR_CORRELATION_NOISE_FLOOR_OF_SIGNAL_REG 0x5a
#define LIDAR_RECEIVED_SIGNAL_STRENGTH_REG 0x5b
#define LIDAR_RESET_CORRELATOR_REG 0x5c
#define LIDAR_CORRELATION_DATA_ACCESS_PORT_SIGN_BIT_REG 0x5d
#define LIDAR_CLOCK_SYNCHRONIZER_CTRL_REG 0x5e
#define LIDAR_MEASURED_TRANSMIT_POWER_REG 0x5f
#define LIDAR_MEASURED_FINE_DELAY_REG 0x60
#define LIDAR_COARSE_DELAY_REG 0x61
#define LIDAR_COARSE_DELAY_HIGH_REG 0x62
#define LIDAR_POSITIVE_CORRELATION_SAMPLE_REG 0x63
#endif /* LIDAR_H */
