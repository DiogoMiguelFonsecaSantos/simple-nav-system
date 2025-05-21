#include "mpu9250.h"
#include "spi_protocol.h"
#include "esp_log.h"
#include <math.h> 

static const char *TAG = "MPU9250";
static float mag_adjust[3]; // Sensitivity adjustment values for X, Y, Z axes

esp_err_t MPU9250WriteRegister(uint8_t reg, uint8_t value) {
    uint8_t tx_data[2] = { reg & 0x7F, value }; // MSB = 0 for write
    uint8_t rx_data[2] = { 0 };

    // Transmit data over SPI
    return SPI_PROTOCOLTransmit(tx_data, rx_data, sizeof(tx_data));
}

esp_err_t MPU9250ReadRegister(uint8_t reg, uint8_t *value) {
    uint8_t tx_data[2] = { reg | 0x80, 0x00 }; // MSB = 1 for read
    uint8_t rx_data[2] = { 0 };

    // Transmit data over SPI
    esp_err_t ret = SPI_PROTOCOLTransmit(tx_data, rx_data, sizeof(tx_data));
    if (ret == ESP_OK) {
        *value = rx_data[1]; // The second byte contains the register value
    }
    return ret;
}

esp_err_t MPU9250Init(void) {
    ESP_LOGI(TAG, "Initializing MPU-9250...");

    // Enable I2C master mode
    esp_err_t ret = MPU9250WriteRegister(MPU9250_USER_CTRL_REG, 0x20);
    if (ret != ESP_OK) return ret;

    // Set I2C master clock speed
    ret = MPU9250WriteRegister(MPU9250_I2C_MST_CTRL_REG, 0x0D);
    if (ret != ESP_OK) return ret;

    // Enable bypass mode to access magnetometer
    ret = MPU9250WriteRegister(MPU9250_INT_PIN_CFG_REG, 0x02);
    if (ret != ESP_OK) return ret;

    // Initialize AK8963 magnetometer
    ret = AK8963Init();
    if (ret != ESP_OK) return ret;

    return ESP_OK;
}

esp_err_t AK8963Init(void) {
    
    ESP_LOGI(TAG, "Initializing AK8963 Magnetometer...");

    // Set AK8963 to power-down mode
    esp_err_t ret = MPU9250WriteRegister(AK8963_CNTL_REG, 0x00);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set AK8963 to power-down mode");
        return ret;
    }

    vTaskDelay(10 / portTICK_PERIOD_MS); // Wait for 10ms

    // Set AK8963 to fuse ROM access mode
    ret = MPU9250WriteRegister(AK8963_CNTL_REG, 0x0F);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set AK8963 to fuse ROM access mode");
        return ret;
    }

    // Read sensitivity adjustment values
    uint8_t asa[3];
    ret = MPU9250ReadRegister(AK8963_ASAX_REG, &asa[0]);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read AK8963_ASAX_REG");
        return ret;
    }
    ret = MPU9250ReadRegister(AK8963_ASAY_REG, &asa[1]);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read AK8963_ASAY_REG");
        return ret;
    }
    ret = MPU9250ReadRegister(AK8963_ASAZ_REG, &asa[2]);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read AK8963_ASAZ_REG");
        return ret;
    }

    // Calculate sensitivity adjustment values
    mag_adjust[0] = (asa[0] - 128) / 256.0f + 1.0f;
    mag_adjust[1] = (asa[1] - 128) / 256.0f + 1.0f;
    mag_adjust[2] = (asa[2] - 128) / 256.0f + 1.0f;

    ESP_LOGI(TAG, "Magnetometer sensitivity adjustment values: X=%.2f, Y=%.2f, Z=%.2f",
             mag_adjust[0], mag_adjust[1], mag_adjust[2]);

    // Set AK8963 to continuous measurement mode 1 (8 Hz output rate)
    ret = MPU9250WriteRegister(AK8963_CNTL_REG, 0x12);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set AK8963 to continuous measurement mode");
        return ret;
    }

    vTaskDelay(10 / portTICK_PERIOD_MS); // Wait for 10ms

    ESP_LOGI(TAG, "AK8963 Magnetometer initialized successfully.");
    return ESP_OK;
}

esp_err_t MPU9250ReadAccelerometerRaw(int16_t *x, int16_t *y, int16_t *z) {
    uint8_t data[6]; // Buffer to store raw data from the accelerometer registers
     
    // Read the 6 accelerometer registers starting from ACCEL_XOUT_H
    esp_err_t ret = MPU9250ReadRegister(MPU9250_ACCEL_XOUT_H_REG, &data[0]); // ACCEL_XOUT_H
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(MPU9250_ACCEL_XOUT_L_REG, &data[1]); // ACCEL_XOUT_L
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(MPU9250_ACCEL_YOUT_H_REG, &data[2]); // ACCEL_YOUT_H
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(MPU9250_ACCEL_YOUT_L_REG, &data[3]); // ACCEL_YOUT_L
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(MPU9250_ACCEL_ZOUT_H_REG, &data[4]); // ACCEL_ZOUT_H
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(MPU9250_ACCEL_ZOUT_L_REG, &data[5]); // ACCEL_ZOUT_L
    if (ret != ESP_OK) return ret;

    // Combine high and low bytes for each axis
    *x = ((int16_t)data[0] << 8) | data[1];
    *y = ((int16_t)data[2] << 8) | data[3];
    *z = ((int16_t)data[4] << 8) | data[5];

    return ESP_OK;
}

esp_err_t MPU9250ReadGyroscopeRaw(int16_t *x, int16_t *y, int16_t *z) {
    uint8_t data[6]; // Buffer to store raw data from the gyroscope registers
    esp_err_t ret;

    // Read the 6 gyroscope registers starting from GYRO_XOUT_H
    ret = MPU9250ReadRegister(MPU9250_GYRO_XOUT_H_REG, &data[0]); // GYRO_XOUT_H
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(MPU9250_GYRO_XOUT_L_REG, &data[1]); // GYRO_XOUT_L
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(MPU9250_GYRO_YOUT_H_REG, &data[2]); // GYRO_YOUT_H
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(MPU9250_GYRO_YOUT_L_REG, &data[3]); // GYRO_YOUT_L
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(MPU9250_GYRO_ZOUT_H_REG, &data[4]); // GYRO_ZOUT_H
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(MPU9250_GYRO_ZOUT_L_REG, &data[5]); // GYRO_ZOUT_L
    if (ret != ESP_OK) return ret;

    // Combine high and low bytes for each axis
    *x = ((int16_t)data[0] << 8) | data[1];
    *y = ((int16_t)data[2] << 8) | data[3];
    *z = ((int16_t)data[4] << 8) | data[5];

    return ESP_OK;
}

esp_err_t MPU9250ReadMagnetometerRaw(int16_t *x, int16_t *y, int16_t *z) {
    uint8_t data[7]; // Buffer to store raw data from the magnetometer registers
    esp_err_t ret;

    // Read the 7 magnetometer registers starting from HXL
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
    ret = MPU9250ReadRegister(AK8963_ST2_REG, &data[6]); // Status 2 register
    if (ret != ESP_OK) return ret;

    // Combine high and low bytes for each axis
    *x = ((int16_t)data[1] << 8) | data[0];
    *y = ((int16_t)data[3] << 8) | data[2];
    *z = ((int16_t)data[5] << 8) | data[4];

    // Check for overflow
    if (data[6] & 0x08) {
        ESP_LOGE(TAG, "Magnetometer overflow detected.");
        return ESP_FAIL;
    }

    //ESP_LOGI(TAG, "Raw magnetometer data: X=%d, Y=%d, Z=%d", *x, *y, *z);

    return ESP_OK;
}

esp_err_t MPU9250ReadMagnetometer(mpu9250_data_t *data) {
    int16_t raw_x, raw_y, raw_z;
    esp_err_t ret = MPU9250ReadMagnetometerRaw(&raw_x, &raw_y, &raw_z);
    if (ret != ESP_OK) return ret;

    // Apply sensitivity adjustment and scale factor
    data->mag_x = raw_x * MAGNETOMETER_SCALE * mag_adjust[0];
    data->mag_y = raw_y * MAGNETOMETER_SCALE * mag_adjust[1];
    data->mag_z = raw_z * MAGNETOMETER_SCALE * mag_adjust[2];

    //ESP_LOGI(TAG, "Scaled magnetometer data: X=%.2f, Y=%.2f, Z=%.2f",
             //data->mag_x, data->mag_y, data->mag_z);

    return ESP_OK;
}

esp_err_t MPU9250ReadTemperature(float *temp) {
    uint8_t data[2]; // Buffer to store raw data from the temperature registers

    // Read the 2 temperature registers starting from TEMP_OUT_H
    esp_err_t ret = MPU9250ReadRegister(MPU9250_TEMP_OUT_H_REG, &data[0]); // TEMP_OUT_H
    if (ret != ESP_OK) return ret;
    ret = MPU9250ReadRegister(MPU9250_TEMP_OUT_L_REG, &data[1]); // TEMP_OUT_L
    if (ret != ESP_OK) return ret;

    // Combine high and low bytes for temperature
    int16_t raw_temp = ((int16_t)data[0] << 8) | data[1];

    // Convert to Celsius
    *temp = ((float)raw_temp / TEMP_SENSITIVITY) + TEMP_OFFSET;

    return ESP_OK;
}

esp_err_t MPU9250ReadAllData(mpu9250_data_t *data) {
    int16_t accel_x, accel_y, accel_z;
    int16_t gyro_x, gyro_y, gyro_z;

    // Read accelerometer data
    esp_err_t retVal = MPU9250ReadAccelerometerRaw(&accel_x, &accel_y, &accel_z);
    if (retVal != ESP_OK) return retVal;

    // Read gyroscope data
    retVal = MPU9250ReadGyroscopeRaw(&gyro_x, &gyro_y, &gyro_z);
    if (retVal != ESP_OK) return retVal;

    // Read magnetometer data
    retVal = MPU9250ReadMagnetometer(data);
    if (retVal != ESP_OK) return retVal;

    // Read temperature data
    retVal = MPU9250ReadTemperature(&data->temperature);
    if (retVal != ESP_OK) return retVal;

    // Scale and assign accelerometer data
    data->accel_x = accel_x / ACCEL_SCALE;
    data->accel_y = accel_y / ACCEL_SCALE;
    data->accel_z = accel_z / ACCEL_SCALE;

    // Scale and assign gyroscope data
    data->gyro_x = gyro_x / GYRO_SCALE;
    data->gyro_y = gyro_y / GYRO_SCALE;
    data->gyro_z = gyro_z / GYRO_SCALE;

    // Calculate pitch and roll using accelerometer data (atan2 = tangent of y/x)
    float accel_pitch = atan2(data->accel_x, sqrt(data->accel_y * data->accel_y + data->accel_z * data->accel_z)) * 180.0 / M_PI;
    float accel_roll = atan2(data->accel_y, sqrt(data->accel_x * data->accel_x + data->accel_z * data->accel_z)) * 180.0 / M_PI;

    // Integrate gyroscope data to estimate pitch and roll
    data->pitch += data->gyro_x * data->sample_time; // Integrate gyroscope data for pitch
    data->roll += data->gyro_y * data->sample_time; // Integrate gyroscope data for roll

    // Apply complementary filter
    const float alpha = 0.98; // Adjust this value to tune the filter
    data->pitch = alpha * data->pitch + (1 - alpha) * accel_pitch; // Complementary filter for pitch 
    data->roll = alpha * data->roll + (1 - alpha) * accel_roll; // Complementary filter for roll 

    data->accel_x = data->accel_x * 9.80665; // Convert to m/s^2
    data->accel_y = data->accel_y * 9.80665; // Convert to m/s^2
    data->accel_z = data->accel_z * 9.80665; // Convert to m/s^2

    return ESP_OK;
}

// https://www.hibit.dev/posts/67/complementary-filter-and-relative-orientation-with-mpu9250
