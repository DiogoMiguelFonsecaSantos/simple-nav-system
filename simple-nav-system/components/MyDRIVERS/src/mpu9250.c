#include "mpu9250.h"
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Private helper functions
static SPIDeviceContext* create_spi_device(int mosi_pin, int miso_pin, int sclk_pin, int cs_pin) {
    SPIDeviceContext* ctx = malloc(sizeof(SPIDeviceContext));
    if (!ctx) return NULL;

    // Configure bus
    ctx->busCfg.mosi_stdPin = mosi_pin;
    ctx->busCfg.miso_stdPin = miso_pin;
    ctx->busCfg.sclk_Pin = sclk_pin;
    ctx->busCfg.maxSingleTansferSz = 4092; // With DMA

    // Configure device
    ctx->devCfg.mode = MPU9250_SPI_MODE;
    ctx->devCfg.clockFreqHz = MPU9250_SPI_CLOCK;
    ctx->devCfg.cmdBits = 8;
    ctx->devCfg.csPin = cs_pin;
    ctx->devCfg.csSetupCycles = MPU9250_SPI_CS_SETUP;
    ctx->devCfg.csHoldCycles = MPU9250_SPI_CS_HOLD;
    ctx->devCfg.csIfActiveHigh = false;
    ctx->devCfg.s2mDataInputDelayns = 25;
    ctx->devCfg.dummy_bits = 0;
    ctx->devCfg.lsbFirst = false;
    ctx->devCfg.fullDuplex = true;
    ctx->devCfg.queueSZ = MPU9250_SPI_QUEUE_SIZE;
    ctx->devCfg.usingDMA = true;
    ctx->devCfg.dmaBufSZ = 64;

    return ctx;
}

bool MPU9250_Init(MPU9250_Handle *handle, int mosi_pin, int miso_pin, int sclk_pin, int cs_pin) {
    memset(handle, 0, sizeof(MPU9250_Handle));
    
    // Initialize SPI device
    handle->spi = create_spi_device(mosi_pin, miso_pin, sclk_pin, cs_pin);
    if (!handle->spi) return false;
    
    // Reset device
    MPU9250_WriteRegister(handle, MPU9250_PWR_MGMT_1, 0x80);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    
    // Wake up device and select clock source
    MPU9250_WriteRegister(handle, MPU9250_PWR_MGMT_1, 0x01);
    
    // Default configuration
    MPU9250_ConfigAccel(handle, 0x08); // ±4g
    MPU9250_ConfigGyro(handle, 0x08);  // ±500dps
    
    // Configure low pass filter
    MPU9250_WriteRegister(handle, MPU9250_ACCEL_CONFIG2, 0x03);
    
    // Enable bypass mode for magnetometer access
    MPU9250_WriteRegister(handle, MPU9250_INT_PIN_CFG, 0x02);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    
    // Initialize magnetometer
    handle->mag_enabled = MPU9250_ConfigMag(handle, 0x16); // Continuous mode 2 (100Hz)
    
    return MPU9250_Verify(handle);
}

bool MPU9250_Verify(MPU9250_Handle *handle) {
    uint8_t whoami = MPU9250_ReadRegister(handle, MPU9250_WHO_AM_I);
    if (whoami != MPU9250_WHOAMI_ID) {
        printf("MPU9250 WHO_AM_I error: 0x%02X\n", whoami);
        return false;
    }
    
    if (handle->mag_enabled) {
        whoami = MPU9250_MagReadRegister(handle, AK8963_WHO_AM_I);
        if (whoami != AK8963_WHOAMI_ID) {
            printf("AK8963 WHO_AM_I error: 0x%02X\n", whoami);
            handle->mag_enabled = false;
        }
    }
    
    return true;
}

void MPU9250_ConfigAccel(MPU9250_Handle *handle, uint8_t range) {
    MPU9250_WriteRegister(handle, MPU9250_ACCEL_CONFIG, range);
    
    // Set scale factor (in g)
    switch(range & 0x18) {
        case 0x00: handle->accel_scale = 2.0f / 32768.0f; break; // ±2g
        case 0x08: handle->accel_scale = 4.0f / 32768.0f; break; // ±4g
        case 0x10: handle->accel_scale = 8.0f / 32768.0f; break; // ±8g
        case 0x18: handle->accel_scale = 16.0f / 32768.0f; break; // ±16g
    }
}

void MPU9250_ConfigGyro(MPU9250_Handle *handle, uint8_t range) {
    MPU9250_WriteRegister(handle, MPU9250_GYRO_CONFIG, range);
    
    // Set scale factor (in dps)
    switch(range & 0x18) {
        case 0x00: handle->gyro_scale = 250.0f / 32768.0f; break;  // ±250dps
        case 0x08: handle->gyro_scale = 500.0f / 32768.0f; break;  // ±500dps
        case 0x10: handle->gyro_scale = 1000.0f / 32768.0f; break; // ±1000dps
        case 0x18: handle->gyro_scale = 2000.0f / 32768.0f; break; // ±2000dps
    }
}

bool MPU9250_ConfigMag(MPU9250_Handle *handle, uint8_t mode) {
    // Check WHO_AM_I first
    uint8_t whoami = MPU9250_MagReadRegister(handle, AK8963_WHO_AM_I);
    if (whoami != AK8963_WHOAMI_ID) {
        return false;
    }
    
    // Set magnetometer to power down
    MPU9250_MagWriteRegister(handle, AK8963_CNTL1, 0x00);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    
    // Set magnetometer to specified mode
    MPU9250_MagWriteRegister(handle, AK8963_CNTL1, mode);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    
    // Set scale factor (in uT)
    handle->mag_scale = 0.15f; // 16-bit output
    
    return true;
}

void MPU9250_ReadAccel(MPU9250_Handle *handle, float accel[3]) {
    uint8_t buffer[6];
    TransferSPI_Type trans = {
        .flags = 0,
        .cmd = MPU9250_ACCEL_XOUT_H | 0x80,
        .rxBuf = buffer,
        .dataLen = 6
    };
    
    // Execute SPI transaction
    if (SPI_Transfer(handle->spi, &trans) != 0) {
        printf("SPI read failed\n");
        return;
    }
    
    // Convert to g's
    accel[0] = (int16_t)((buffer[0] << 8) | buffer[1]) * handle->accel_scale;
    accel[1] = (int16_t)((buffer[2] << 8) | buffer[3]) * handle->accel_scale;
    accel[2] = (int16_t)((buffer[4] << 8) | buffer[5]) * handle->accel_scale;
}

void MPU9250_ReadGyro(MPU9250_Handle *handle, float gyro[3]) {
    uint8_t buffer[6];
    TransferSPI_Type trans = {
        .flags = 0,
        .cmd = MPU9250_GYRO_XOUT_H | 0x80,
        .rxBuf = buffer,
        .dataLen = 6
    };
    
    // Execute SPI transaction
    if (SPI_Transfer(handle->spi, &trans) != 0) {
        printf("SPI read failed\n");
        return;
    }
    
    // Convert to dps
    gyro[0] = (int16_t)((buffer[0] << 8) | buffer[1]) * handle->gyro_scale;
    gyro[1] = (int16_t)((buffer[2] << 8) | buffer[3]) * handle->gyro_scale;
    gyro[2] = (int16_t)((buffer[4] << 8) | buffer[5]) * handle->gyro_scale;
}

void MPU9250_ReadMag(MPU9250_Handle *handle, float mag[3]) {
    if (!handle->mag_enabled) {
        mag[0] = mag[1] = mag[2] = 0.0f;
        return;
    }
    
    uint8_t buffer[7];
    
    // Check data ready
    uint8_t st1 = MPU9250_MagReadRegister(handle, 0x02);
    if (!(st1 & 0x01)) return;
    
    // Read 7 bytes (6 data + status)
    MPU9250_WriteRegister(handle, MPU9250_I2C_SLV0_ADDR, 0x8C); // AK8963 I2C address + read
    MPU9250_WriteRegister(handle, MPU9250_I2C_SLV0_REG, 0x03);  // Start from HXL
    MPU9250_WriteRegister(handle, MPU9250_I2C_SLV0_CTRL, 0x87); // enable with 7 bytes
    
    vTaskDelay(10 / portTICK_PERIOD_MS);
    
    // Read the data
    for (int i = 0; i < 7; i++) {
        buffer[i] = MPU9250_ReadRegister(handle, MPU9250_EXT_SENS_DATA_00 + i);
    }
    
    // Check overflow
    if (buffer[6] & 0x08) {
        printf("Magnetometer overflow!\n");
        return;
    }
    
    // Convert to uT
    mag[0] = (int16_t)((buffer[1] << 8) | buffer[0]) * handle->mag_scale;
    mag[1] = (int16_t)((buffer[3] << 8) | buffer[2]) * handle->mag_scale;
    mag[2] = (int16_t)((buffer[5] << 8) | buffer[4]) * handle->mag_scale;
}

uint8_t MPU9250_ReadRegister(MPU9250_Handle *handle, uint8_t reg) {
    uint8_t value = 0;
    TransferSPI_Type trans = {
        .flags = 0,
        .cmd = reg | 0x80, // Set read bit
        .rxBuf = &value,
        .dataLen = 1
    };
    
    if (SPI_Transfer(handle->spi, &trans) != 0) {
        printf("SPI read failed\n");
    }
    
    return value;
}

void MPU9250_WriteRegister(MPU9250_Handle *handle, uint8_t reg, uint8_t value) {
    TransferSPI_Type trans = {
        .flags = 0,
        .cmd = reg & 0x7F, // Clear read bit
        .txBuf = &value,
        .dataLen = 1
    };
    
    if (SPI_Transfer(handle->spi, &trans) != 0) {
        printf("SPI write failed\n");
    }
}

uint8_t MPU9250_MagReadRegister(MPU9250_Handle *handle, uint8_t reg) {
    MPU9250_WriteRegister(handle, MPU9250_I2C_SLV0_ADDR, 0x8C); // AK8963 I2C address + read
    MPU9250_WriteRegister(handle, MPU9250_I2C_SLV0_REG, reg);
    MPU9250_WriteRegister(handle, MPU9250_I2C_SLV0_CTRL, 0x81); // enable with 1 byte
    
    vTaskDelay(10 / portTICK_PERIOD_MS);
    return MPU9250_ReadRegister(handle, MPU9250_EXT_SENS_DATA_00);
}

void MPU9250_MagWriteRegister(MPU9250_Handle *handle, uint8_t reg, uint8_t data) {
    MPU9250_WriteRegister(handle, MPU9250_I2C_SLV0_DO, data);
    MPU9250_WriteRegister(handle, MPU9250_I2C_SLV0_ADDR, 0x0C); // AK8963 I2C address + write
    MPU9250_WriteRegister(handle, MPU9250_I2C_SLV0_REG, reg);
    MPU9250_WriteRegister(handle, MPU9250_I2C_SLV0_CTRL, 0x81); // enable with 1 byte
    
    vTaskDelay(10 / portTICK_PERIOD_MS);
}