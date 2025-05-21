#ifndef COMPONENTS_MYDRIVERS_INC_MPU9250_H_
#define COMPONENTS_MYDRIVERS_INC_MPU9250_H_

#include <stdint.h>
#include "esp_err.h"

#define MPU9250_USER_CTRL_REG 0x6A       // User Control Register
#define MPU9250_I2C_MST_CTRL_REG 0x24   // I2C Master Control Register

// MPU-9250 Register Definitions
#define MPU9250_ACCEL_XOUT_H_REG 0x3B
#define MPU9250_ACCEL_XOUT_L_REG 0x3C
#define MPU9250_ACCEL_YOUT_H_REG 0x3D
#define MPU9250_ACCEL_YOUT_L_REG 0x3E
#define MPU9250_ACCEL_ZOUT_H_REG 0x3F
#define MPU9250_ACCEL_ZOUT_L_REG 0x40

#define MPU9250_TEMP_OUT_H_REG 0x41
#define MPU9250_TEMP_OUT_L_REG 0x42

#define MPU9250_GYRO_XOUT_H_REG 0x43
#define MPU9250_GYRO_XOUT_L_REG 0x44
#define MPU9250_GYRO_YOUT_H_REG 0x45
#define MPU9250_GYRO_YOUT_L_REG 0x46
#define MPU9250_GYRO_ZOUT_H_REG 0x47
#define MPU9250_GYRO_ZOUT_L_REG 0x48

#define AK8963_WIA_REG 0x00       // Device ID
#define AK8963_INFO_REG 0x01      // Information
#define AK8963_ST1_REG 0x02       // Status 1
#define AK8963_HXL_REG 0x03       // X-axis data low byte
#define AK8963_HXH_REG 0x04       // X-axis data high byte
#define AK8963_HYL_REG 0x05       // Y-axis data low byte
#define AK8963_HYH_REG 0x06       // Y-axis data high byte
#define AK8963_HZL_REG 0x07       // Z-axis data low byte
#define AK8963_HZH_REG 0x08       // Z-axis data high byte
#define AK8963_ST2_REG 0x09       // Status 2
#define AK8963_CNTL_REG 0x0A      // Control
#define AK8963_ASAX_REG 0x10      // X-axis sensitivity adjustment value
#define AK8963_ASAY_REG 0x11      // Y-axis sensitivity adjustment value
#define AK8963_ASAZ_REG 0x12      // Z-axis sensitivity adjustment valuefine MPU9250_I2C_MST_CTRL_REG 0x24
#define MPU9250_INT_PIN_CFG_REG 0x37

// Scale factors
#define ACCEL_SCALE 16384.0 // Assuming ±2g range (LSB/g)
#define GYRO_SCALE 131.0    // Assuming ±250°/s range (LSB/°/s)
#define TEMP_SENSITIVITY 333.87
#define TEMP_OFFSET 21.0

#define MAGNETOMETER_SCALE 0.15f // Example scale factor (µT/LSB)

// Struct to hold sensor data
typedef struct {
    float accel_x;
    float accel_y;
    float accel_z;

    float gyro_x;
    float gyro_y;
    float gyro_z;

    float mag_x;
    float mag_y;
    float mag_z;

    float temperature;

    float pitch;
    float roll;
    float yaw;

    float sample_time; // Time between samples in seconds
} mpu9250_data_t;

// Function Prototypes
esp_err_t MPU9250Init(void);
esp_err_t MPU9250ReadAllData(mpu9250_data_t *data);
esp_err_t MPU9250ReadAccelerometerRaw(int16_t *x, int16_t *y, int16_t *z);
esp_err_t MPU9250ReadGyroscopeRaw(int16_t *x, int16_t *y, int16_t *z);
esp_err_t MPU9250ReadTemperature(float *temp);
esp_err_t MPU9250WriteRegister(uint8_t reg, uint8_t value);
esp_err_t MPU9250ReadRegister(uint8_t reg, uint8_t *value);
esp_err_t AK8963Init(void);

#endif /* COMPONENTS_MYDRIVERS_INC_MPU9250_H_ */