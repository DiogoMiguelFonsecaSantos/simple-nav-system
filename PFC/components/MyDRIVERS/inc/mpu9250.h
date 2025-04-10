#ifndef MPU9250_H
#define MPU9250_H

#include "esp_err.h"

// MPU9250 Register Addresses
#define MPU9250_ACCEL_XOUT_H_REG  0x3B
#define MPU9250_ACCEL_XOUT_L_REG  0x3C
#define MPU9250_ACCEL_YOUT_H_REG  0x3D
#define MPU9250_ACCEL_YOUT_L_REG  0x3E
#define MPU9250_ACCEL_ZOUT_H_REG  0x3F
#define MPU9250_ACCEL_ZOUT_L_REG  0x40

#define MPU9250_GYRO_XOUT_H_REG   0x43
#define MPU9250_GYRO_XOUT_L_REG   0x44
#define MPU9250_GYRO_YOUT_H_REG   0x45
#define MPU9250_GYRO_YOUT_L_REG   0x46
#define MPU9250_GYRO_ZOUT_H_REG   0x47
#define MPU9250_GYRO_ZOUT_L_REG   0x48

#define AK8963_ST1_REG            0x02
#define AK8963_HXL_REG            0x03
#define AK8963_HXH_REG            0x04
#define AK8963_HYL_REG            0x05
#define AK8963_HYH_REG            0x06
#define AK8963_HZL_REG            0x07
#define AK8963_HZH_REG            0x08
#define AK8963_CNTL_REG           0x0A

// Accelerometer Full-Scale Range
#define MPU9250_ACCEL_RANGE_2G  0x00
#define MPU9250_ACCEL_RANGE_4G  0x08
#define MPU9250_ACCEL_RANGE_8G  0x10
#define MPU9250_ACCEL_RANGE_16G 0x18

// Gyroscope Full-Scale Range
#define MPU9250_GYRO_RANGE_250DPS  0x00
#define MPU9250_GYRO_RANGE_500DPS  0x08
#define MPU9250_GYRO_RANGE_1000DPS 0x10
#define MPU9250_GYRO_RANGE_2000DPS 0x18

// Magnetometer Modes
#define MPU9250_MAG_MODE_CONTINUOUS1 0x12

// SPI Read/Write Masks
#define MPU9250_REG_READ          0x80
#define MPU9250_REG_WRITE         0x00

// Function Prototypes
esp_err_t MPU9250Init(void);
esp_err_t MPU9250InitMagnetometer(void);
esp_err_t MPU9250ReadRegister(uint8_t reg, uint8_t *data);
esp_err_t MPU9250WriteRegister(uint8_t reg, uint8_t data);
esp_err_t MPU9250ReadAccelerometerRaw(int16_t *x, int16_t *y, int16_t *z);
esp_err_t MPU9250ReadGyroscopeRaw(int16_t *x, int16_t *y, int16_t *z);
esp_err_t MPU9250ReadMagnetometerRaw(int16_t *x, int16_t *y, int16_t *z);
esp_err_t MPU9250SetAccelerometerRange(uint8_t range);
esp_err_t MPU9250SetGyroscopeRange(uint8_t range);

#endif // MPU9250_H