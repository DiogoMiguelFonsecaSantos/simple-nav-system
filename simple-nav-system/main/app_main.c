#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mpu9250.h"
#include "spi_protocol.h"
#include "led.h"
#include "pin.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_err.h"
#include "esp_log.h"
#include "epaper.h"

#define LED_RED 26
#define LED_YELLOW 27
#define LED_GREEN 14
#define LED_BLUE 12

void configLEDS(void)
{
    gpio_reset_pin(LED_RED);
    gpio_reset_pin(LED_YELLOW);
    gpio_reset_pin(LED_GREEN);
    gpio_reset_pin(LED_BLUE);

    PIN_SetDirection(LED_RED, OUTPUT);
    PIN_SetDirection(LED_YELLOW, OUTPUT);
    PIN_SetDirection(LED_GREEN, OUTPUT);
    PIN_SetDirection(LED_BLUE, OUTPUT);
}

void internalBlink(void *pvParameters)
{   
	LED_Off();
    while (true) {
        LED_Toggle();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void printInfo(mpu9250_data_t *imuData) {
    printf("========================================================================\n");
    printf("Accelerometer: X=%.2f m/s2, Y=%.2f m/s2, Z=%.2f m/s2\n", imuData->accel_x, imuData->accel_y, imuData->accel_z);
    printf("Gyroscope: X=%.2f, Y=%.2f, Z=%.2f\n", imuData->gyro_x, imuData->gyro_y, imuData->gyro_z);
    printf("Magnetometer: X=%.2f, Y=%.2f, Z=%.2f\n", imuData->mag_x, imuData->mag_y, imuData->mag_z);
    printf("Temperature: %.2f degrees Celsius\n", imuData->temperature);
    printf("Pitch: %.2f degrees, Roll: %.2f degrees\n", imuData->pitch, imuData->roll);
    printf("========================================================================\n");

}

void app_main(void)
{

    LED_Init(false);
	//configLEDS();
	
    ESP_LOGI("MAIN", "Starting application...");

    if (SPI_PROTOCOLInit() != ESP_OK) {
        ESP_LOGE("MAIN", "Failed to initialize SPI");
        return;
    }

    if (MPU9250Init() != ESP_OK) {
        ESP_LOGE("MAIN", "Failed to initialize MPU-9250");
        return;
    }

    printf("MPU-9250 initialized successfully.\n");

    mpu9250_data_t imuData = {0}; // Initialize all struct fields to 0
    //Set struct sample time to 20 ms
    imuData.sample_time = 0.02f; // 20 ms

    // Initialize the e-paper display
    if (EPAPER_Init() != ESP_OK) {
        ESP_LOGE("MAIN", "Failed to initialize e-paper display");
        return;
    }

    printf("EPAPER initialized successfully.\n");

    xTaskCreate(&internalBlink, "internalBlink", 2048, NULL, 5, NULL);

    vTaskDelay(pdMS_TO_TICKS(3000));

    // Clear the e-paper display
    if (EPAPER_Clear() != ESP_OK) {
        ESP_LOGE("MAIN", "Failed to clear e-paper display");
        return;
    }

    int i = 0;
    while (1) {
        esp_err_t retVal = MPU9250ReadAllData(&imuData);
        if (retVal != ESP_OK) {
            printf("Failed to read sensor data: %d\n", retVal);
            continue;
        }
        
        if(i < 100){
            // Delay for a while before reading again
            vTaskDelay(20 / portTICK_PERIOD_MS);
            i++;
        }
        else{
            printInfo(&imuData);
            i = 0; 
        }
        
    }

}
