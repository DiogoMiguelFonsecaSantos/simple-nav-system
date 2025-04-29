#include "mpu9250.h"
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static bool MPU9250_WriteRegister(GenericSPI_Type *SPIx, uint8_t reg, uint8_t value) {
    uint8_t txData[2] = {reg & 0x7F, value}; // MSB=0 for write
    SPIProtocol_SendData(SPIx, txData, sizeof(txData));
    return true;
}

static bool MPU9250_ReadRegister(GenericSPI_Type *SPIx, uint8_t reg, uint8_t *value) {
    uint8_t txData[2] = {reg | 0x80, 0x00}; // MSB=1 for read
    uint8_t rxData[2] = {0};
    SPIProtocol_Transaction(SPIx, txData, rxData, sizeof(txData));
    *value = rxData[1];
    return true;
}

// needs rework
bool MPU9250_Init(GenericSPI_Type *SPIx) {
    // Wake up the MPU9250
    if (!MPU9250_WriteRegister(SPIx, PWR_MGMT_1, 0x00)) {
        return false;
    }

    // Set clock source to PLL with X-axis gyroscope reference 
    if (!MPU9250_WriteRegister(SPIx, PWR_MGMT_1, 0x01)) {
        return false;
    }

    // Disable sleep mode
    if (!MPU9250_WriteRegister(SPIx, PWR_MGMT_2, 0x00)) {
        return false;
    }

    return true;
}

bool MPU9250_ReadAccel(GenericSPI_Type *SPIx, int16_t *accelX, int16_t *accelY, int16_t *accelZ) {
    uint8_t accelX_H, accelX_L, accelY_H, accelY_L, accelZ_H, accelZ_L;

    if (!MPU9250_ReadRegister(SPIx, ACCEL_XOUT_H, &accelX_H) ||
        !MPU9250_ReadRegister(SPIx, ACCEL_XOUT_L, &accelX_L) ||
        !MPU9250_ReadRegister(SPIx, ACCEL_YOUT_H, &accelY_H) ||
        !MPU9250_ReadRegister(SPIx, ACCEL_YOUT_L, &accelY_L) ||
        !MPU9250_ReadRegister(SPIx, ACCEL_ZOUT_H, &accelZ_H) ||
        !MPU9250_ReadRegister(SPIx, ACCEL_ZOUT_L, &accelZ_L)) {
        return false;
    }

    *accelX = (int16_t)((accelX_H << 8) | accelX_L);
    *accelY = (int16_t)((accelY_H << 8) | accelY_L);
    *accelZ = (int16_t)((accelZ_H << 8) | accelZ_L);

    return true;
}

bool MPU9250_ReadGyro(GenericSPI_Type *SPIx, int16_t *gyroX, int16_t *gyroY, int16_t *gyroZ) {
    uint8_t gyroX_H, gyroX_L, gyroY_H, gyroY_L, gyroZ_H, gyroZ_L;

    if (!MPU9250_ReadRegister(SPIx, GYRO_XOUT_H, &gyroX_H) ||
        !MPU9250_ReadRegister(SPIx, GYRO_XOUT_L, &gyroX_L) ||
        !MPU9250_ReadRegister(SPIx, GYRO_YOUT_H, &gyroY_H) ||
        !MPU9250_ReadRegister(SPIx, GYRO_YOUT_L, &gyroY_L) ||
        !MPU9250_ReadRegister(SPIx, GYRO_ZOUT_H, &gyroZ_H) ||
        !MPU9250_ReadRegister(SPIx, GYRO_ZOUT_L, &gyroZ_L)) {
        return false;
    }

    *gyroX = (int16_t)((gyroX_H << 8) | gyroX_L);
    *gyroY = (int16_t)((gyroY_H << 8) | gyroY_L);
    *gyroZ = (int16_t)((gyroZ_H << 8) | gyroZ_L);

    return true;
}

bool MPU9250_ReadTemp(GenericSPI_Type *SPIx, int16_t *temp) {
    uint8_t temp_H, temp_L;

    if (!MPU9250_ReadRegister(SPIx, TEMP_OUT_H, &temp_H) ||
        !MPU9250_ReadRegister(SPIx, TEMP_OUT_L, &temp_L)) {
        return false;
    }

    *temp = (int16_t)((temp_H << 8) | temp_L);
    return true;
}

bool MPU9250_WhoAmI(GenericSPI_Type *SPIx, uint8_t *id) {
    return MPU9250_ReadRegister(SPIx, WHO_AM_I, id);
}