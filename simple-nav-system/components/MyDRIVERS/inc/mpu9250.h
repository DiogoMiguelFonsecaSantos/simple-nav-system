/*
 * mpu9250.h
 *
 *  Created on: 26/04/2025
 *      Author: Diogo
 */

 #ifndef COMPONENTS_MYDRIVERS_INC_MPU9250_H_
 #define COMPONENTS_MYDRIVERS_INC_MPU9250_H_
 
 #include <stdint.h>
 #include "spi_driver.h"
 #include <stdbool.h>
 
 // MPU9250 Register Definitions
 #define MPU9250_WHO_AM_I      0x75
 #define MPU9250_PWR_MGMT_1    0x6B
 #define MPU9250_GYRO_CONFIG   0x1B
 #define MPU9250_ACCEL_CONFIG  0x1C
 #define MPU9250_ACCEL_CONFIG2 0x1D
 #define MPU9250_INT_PIN_CFG   0x37
 #define MPU9250_INT_ENABLE    0x38
 #define MPU9250_ACCEL_XOUT_H  0x3B
 #define MPU9250_GYRO_XOUT_H   0x43
 #define MPU9250_EXT_SENS_DATA_00 0x49
 
 // Magnetometer (AK8963) registers
 #define AK8963_WHO_AM_I       0x00
 #define AK8963_CNTL1          0x0A
 #define AK8963_CNTL2          0x0B
 #define AK8963_HXL            0x03
 
 // Configuration values
 #define MPU9250_WHOAMI_ID     0x71
 #define AK8963_WHOAMI_ID      0x48
 
 // SPI Configuration for MPU9250
 #define MPU9250_SPI_MODE      0
 #define MPU9250_SPI_CLOCK     (1000000) // 1MHz default
 #define MPU9250_SPI_CS_SETUP  1
 #define MPU9250_SPI_CS_HOLD   1
 #define MPU9250_SPI_QUEUE_SIZE 5
 

 #endif /* COMPONENTS_MYDRIVERS_INC_MPU9250_H_ */