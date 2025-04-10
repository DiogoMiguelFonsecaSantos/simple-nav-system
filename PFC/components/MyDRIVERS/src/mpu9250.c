#include "mpu9250.h"
#include "spi_protocol.h"
#include "esp_log.h"

esp_err_t MPU9250Init(void) {
    return SPI_PROTOCOLInit();
}

esp_err_t MPU9250InitMagnetometer(void) {
    // Set magnetometer to continuous measurement mode 1 (0x12)
    return MPU9250WriteRegister(AK8963_CNTL_REG, MPU9250_MAG_MODE_CONTINUOUS1);
}

esp_err_t MPU9250ReadRegister(uint8_t reg, uint8_t *data) {
    uint8_t tx_data[2] = { reg | MPU9250_REG_READ, 0x00 };
    uint8_t rx_data[2] = { 0 };

    esp_err_t ret = SPI_PROTOCOLTransmit(tx_data, rx_data, 2);
    if (ret == ESP_OK) {
        *data = rx_data[1]; // Second byte contains the register value
    }
    return ret;
}

esp_err_t MPU9250WriteRegister(uint8_t reg, uint8_t data) {
    uint8_t tx_data[2] = { reg | MPU9250_REG_WRITE, data };
    return SPI_PROTOCOLTransmit(tx_data, NULL, 2);
}

esp_err_t MPU9250SetAccelerometerRange(uint8_t range) {
    return MPU9250WriteRegister(0x1C, range); // ACCEL_CONFIG register
}

esp_err_t MPU9250SetGyroscopeRange(uint8_t range) {
    return MPU9250WriteRegister(0x1B, range); // GYRO_CONFIG register
}

esp_err_t MPU9250ReadAccelerometerRaw(int16_t *x, int16_t *y, int16_t *z) {
    uint8_t data[6] = { 0 };
    esp_err_t ret;

    ret = MPU9250ReadRegister(MPU9250_ACCEL_XOUT_H_REG, &data[0]);
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(MPU9250_ACCEL_XOUT_L_REG, &data[1]);
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(MPU9250_ACCEL_YOUT_H_REG, &data[2]);
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(MPU9250_ACCEL_YOUT_L_REG, &data[3]);
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(MPU9250_ACCEL_ZOUT_H_REG, &data[4]);
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(MPU9250_ACCEL_ZOUT_L_REG, &data[5]);
    if (ret != ESP_OK) return ret;

    *x = ((int16_t)data[0] << 8) | data[1];
    *y = ((int16_t)data[2] << 8) | data[3];
    *z = ((int16_t)data[4] << 8) | data[5];

    return ESP_OK;
}

esp_err_t MPU9250ReadGyroscopeRaw(int16_t *x, int16_t *y, int16_t *z) {
    uint8_t data[6] = { 0 };
    esp_err_t ret;

    ret = MPU9250ReadRegister(MPU9250_GYRO_XOUT_H_REG, &data[0]);
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(MPU9250_GYRO_XOUT_L_REG, &data[1]);
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(MPU9250_GYRO_YOUT_H_REG, &data[2]);
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(MPU9250_GYRO_YOUT_L_REG, &data[3]);
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(MPU9250_GYRO_ZOUT_H_REG, &data[4]);
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(MPU9250_GYRO_ZOUT_L_REG, &data[5]);
    if (ret != ESP_OK) return ret;

    *x = ((int16_t)data[0] << 8) | data[1];
    *y = ((int16_t)data[2] << 8) | data[3];
    *z = ((int16_t)data[4] << 8) | data[5];

    return ESP_OK;
}

esp_err_t MPU9250ReadMagnetometerRaw(int16_t *x, int16_t *y, int16_t *z) {
    uint8_t status;
    uint8_t data[6] = { 0 };
    esp_err_t ret;

    // Check if data is ready
    ret = MPU9250ReadRegister(AK8963_ST1_REG, &status);
    if (ret != ESP_OK || !(status & 0x01)) {
        return ESP_FAIL; // Data not ready
    }

    ret = MPU9250ReadRegister(AK8963_HXL_REG, &data[0]);
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(AK8963_HXH_REG, &data[1]);
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(AK8963_HYL_REG, &data[2]);
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(AK8963_HYH_REG, &data[3]);
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(AK8963_HZL_REG, &data[4]);
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(AK8963_HZH_REG, &data[5]);
    if (ret != ESP_OK) return ret;

    *x = ((int16_t)data[1] << 8) | data[0];
    *y = ((int16_t)data[3] << 8) | data[2];
    *z = ((int16_t)data[5] << 8) | data[4];

    return ESP_OK;
}