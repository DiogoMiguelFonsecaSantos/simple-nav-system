#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mpu9250.h"
#include "esp_log.h"

void configureMPU9250(void) {
    // Set accelerometer to ±4g
    esp_err_t ret = MPU9250SetAccelerometerRange(MPU9250_ACCEL_RANGE_4G);
    if (ret != ESP_OK) {
        ESP_LOGE("MAIN", "Failed to set accelerometer range");
    }

    // Set gyroscope to ±500 dps
    ret = MPU9250SetGyroscopeRange(MPU9250_GYRO_RANGE_500DPS);
    if (ret != ESP_OK) {
        ESP_LOGE("MAIN", "Failed to set gyroscope range");
    }
}

void app_main(void) {
    // Initialize the MPU-9250
    esp_err_t ret = MPU9250Init();
    if (ret != ESP_OK) {
        ESP_LOGE("MAIN", "Failed to initialize MPU-9250: %d", ret);
        return;
    }

    // Configure the MPU-9250
    configureMPU9250();

    // Initialize the magnetometer
    ret = MPU9250InitMagnetometer();
    if (ret != ESP_OK) {
        ESP_LOGE("MAIN", "Failed to initialize magnetometer: %d", ret);
        return;
    }

    printf("MPU-9250 initialized and configured successfully.\n");

    // Variables to store sensor data
    int16_t accel_x, accel_y, accel_z;
    int16_t gyro_x, gyro_y, gyro_z;
    int16_t mag_x, mag_y, mag_z;

    while (1) {
        // Read accelerometer data
        ret = MPU9250ReadAccelerometerRaw(&accel_x, &accel_y, &accel_z);
        if (ret != ESP_OK) {
            printf("Failed to read accelerometer data: %d\n", ret);
            continue;
        }

        // Read gyroscope data
        ret = MPU9250ReadGyroscopeRaw(&gyro_x, &gyro_y, &gyro_z);
        if (ret != ESP_OK) {
            printf("Failed to read gyroscope data: %d\n", ret);
            continue;
        }

        // Read magnetometer data
        ret = MPU9250ReadMagnetometerRaw(&mag_x, &mag_y, &mag_z);
        if (ret != ESP_OK) {
            ESP_LOGE("MAIN", "Failed to read magnetometer data: %d", ret);
        } else {
            ESP_LOGI("MAIN", "Magnetometer data: X=%d, Y=%d, Z=%d", mag_x, mag_y, mag_z);
        }

        // Print sensor data
        printf("========================================================================\n");
        printf("Accelerometer: X=%d, Y=%d, Z=%d\n", accel_x, accel_y, accel_z);
        printf("Gyroscope: X=%d, Y=%d, Z=%d\n", gyro_x, gyro_y, gyro_z);
        printf("Magnetometer: X=%d, Y=%d, Z=%d\n", mag_x, mag_y, mag_z);
        printf("========================================================================\n");

        // Delay for a while before reading again
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}