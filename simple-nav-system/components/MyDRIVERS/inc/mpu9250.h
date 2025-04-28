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
 
 typedef struct {
     SPI_Handle_t spi;
     float accel_scale;
     float gyro_scale;
     float mag_scale;
     bool mag_enabled;
 } MPU9250_Handle;
 
 // Initialization functions
 bool MPU9250_Init(MPU9250_Handle *handle, int mosi_pin, int miso_pin, int sclk_pin, int cs_pin);
 bool MPU9250_Verify(MPU9250_Handle *handle);
 
 // Configuration functions
 void MPU9250_ConfigAccel(MPU9250_Handle *handle, uint8_t range);
 void MPU9250_ConfigGyro(MPU9250_Handle *handle, uint8_t range);
 bool MPU9250_ConfigMag(MPU9250_Handle *handle, uint8_t mode);
 
 // Data reading functions
 void MPU9250_ReadAccel(MPU9250_Handle *handle, float accel[3]);
 void MPU9250_ReadGyro(MPU9250_Handle *handle, float gyro[3]);
 void MPU9250_ReadMag(MPU9250_Handle *handle, float mag[3]);
 void MPU9250_ReadAll(MPU9250_Handle *handle, float accel[3], float gyro[3], float mag[3]);
 
 // Low-level functions
 uint8_t MPU9250_ReadRegister(MPU9250_Handle *handle, uint8_t reg);
 void MPU9250_WriteRegister(MPU9250_Handle *handle, uint8_t reg, uint8_t value);
 uint8_t MPU9250_MagReadRegister(MPU9250_Handle *handle, uint8_t reg);
 void MPU9250_MagWriteRegister(MPU9250_Handle *handle, uint8_t reg, uint8_t value);

 #endif /* COMPONENTS_MYDRIVERS_INC_MPU9250_H_ */