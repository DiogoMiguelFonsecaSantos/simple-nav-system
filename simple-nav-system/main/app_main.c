#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hal/gpio_types.h"
#include "io_mux.h"
#include "gpio_matrix.h"
#include "driver/gpio.h"
#include <string.h>
#include "pin.h"
#include "pinconfig.h"
#include "regs_gpio_matrix.h"
#include "regs_io_mux.h"
#include "esp_system.h"
#include "esp_log.h"
#include "led.h"
#include "regs_spi_peripheral.h"
#include "spi_driver.h"
#include "spi_hal.h"

#include "mpu9250.h"


#define BOOTDELAY_MS      5000
#define DELAY_MS          100
#define GPIO_RED          26
#define GPIO_BLUE         12
#define GPIO_GREEN        14
#define GPIO_YELLOW       27 


void blinkLED(void *pvParameters)
{   
    vTaskDelay(pdMS_TO_TICKS(BOOTDELAY_MS)); // Delay for 5 seconds
    while (1)
    {
        LED_Toggle(); // Toggle the LED state
        vTaskDelay(pdMS_TO_TICKS(50)); // Delay
    }
}

void trafficLight(void *pvParameters)
{   
    PIN_Set(GPIO_GREEN); // Set GPIO 26 output to HIGH
    vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 5 seconds
    PIN_Clear(GPIO_GREEN); // Clear GPIO 26 output

    PIN_Set(GPIO_YELLOW); // Set GPIO 27 output to HIGH
    vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 5 seconds
    PIN_Clear(GPIO_YELLOW); // Clear GPIO 27 output

    PIN_Set(GPIO_RED); // Set GPIO 26 output to HIGH
    vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 5 seconds
    PIN_Clear(GPIO_RED); // Clear GPIO 26 output

    PIN_Set(GPIO_BLUE); // Set GPIO 12 output to HIGH
    vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 5 seconds
    PIN_Clear(GPIO_BLUE); // Clear GPIO 12 output

    PIN_Set(GPIO_GREEN);
    vTaskDelay(pdMS_TO_TICKS(125)); // Delay for 5 seconds
    PIN_Clear(GPIO_GREEN); // Clear GPIO 14 output

    PIN_Set(GPIO_YELLOW); // Set GPIO 27 output to HIGH
    vTaskDelay(pdMS_TO_TICKS(125)); // Delay for 5 seconds
    PIN_Clear(GPIO_YELLOW); // Clear GPIO 27 output

    PIN_Set(GPIO_RED); // Set GPIO 26 output to HIGH
    vTaskDelay(pdMS_TO_TICKS(125)); // Delay for 5 seconds
    PIN_Clear(GPIO_RED); // Clear GPIO 26 output

    PIN_Set(GPIO_BLUE); // Set GPIO 12 output to HIGH
    vTaskDelay(pdMS_TO_TICKS(125)); // Delay for 5 seconds
    PIN_Clear(GPIO_BLUE); // Clear GPIO 12 output

    PIN_Set(GPIO_GREEN);
    vTaskDelay(pdMS_TO_TICKS(125)); // Delay for 5 seconds
    PIN_Clear(GPIO_GREEN); // Clear GPIO 14 output

    PIN_Set(GPIO_YELLOW); // Set GPIO 27 output to HIGH
    vTaskDelay(pdMS_TO_TICKS(125)); // Delay for 5 seconds
    PIN_Clear(GPIO_YELLOW); // Clear GPIO 27 output

    PIN_Set(GPIO_RED); // Set GPIO 26 output to HIGH
    vTaskDelay(pdMS_TO_TICKS(125)); // Delay for 5 seconds
    PIN_Clear(GPIO_RED); // Clear GPIO 26 output

    PIN_Set(GPIO_BLUE); // Set GPIO 12 output to HIGH
    vTaskDelay(pdMS_TO_TICKS(125)); // Delay for 5 seconds
    PIN_Clear(GPIO_BLUE); // Clear GPIO 12 output

    while (1)
    {
        PIN_Set(GPIO_GREEN); // Set GPIO 14 output to HIGH (Green light ON)
        vTaskDelay(pdMS_TO_TICKS(5000)); // Delay for 5 seconds
        PIN_Clear(GPIO_GREEN); // Clear GPIO 14 output (Green light OFF)
        PIN_Set(GPIO_YELLOW); // Set GPIO 27 output to HIGH (Yellow light ON)
        vTaskDelay(pdMS_TO_TICKS(2000)); // Delay for 2 seconds
        PIN_Clear(GPIO_YELLOW); // Clear GPIO 27 output (Yellow light OFF)
        PIN_Set(GPIO_RED); // Set GPIO 26 output to HIGH (Red light ON)
        vTaskDelay(pdMS_TO_TICKS(5000)); // Delay for 5 seconds
        PIN_Clear(GPIO_RED); // Clear GPIO 26 output (Red light OFF)
        PIN_Set(GPIO_BLUE); // Set GPIO 12 output to HIGH (Blue light ON)
        vTaskDelay(pdMS_TO_TICKS(2000)); // Delay for 2 seconds
        PIN_Clear(GPIO_BLUE); // Clear GPIO 12 output (Blue light OFF)
    }
}

void app_main(void)
{
    LED_Init(ON); // Initialize the LED to ON state
    printf("LED is %s\n", LED_GetState() ? "ON" : "OFF");

    gpio_dump_io_configuration(stdout, (1ULL << 22));

    PIN_Reset(GPIO_RED);
     PIN_InitGPIO_OutputPin(GPIO_RED); // Initialize GPIO 26 as output
    PIN_Reset(GPIO_BLUE);
    PIN_InitGPIO_OutputPin(GPIO_BLUE); // Initialize GPIO 12 as output
    PIN_Reset(GPIO_GREEN);
    PIN_InitGPIO_OutputPin(GPIO_GREEN); // Initialize GPIO 14 as output
    PIN_Reset(GPIO_YELLOW);
    PIN_InitGPIO_OutputPin(GPIO_YELLOW); // Initialize GPIO 27 as output

    xTaskCreate(blinkLED, "BlinkLED", 2048, NULL, 5, NULL);
    xTaskCreate(trafficLight, "TrafficLight", 2048, NULL, 5, NULL);
    while (1)
    {
    }
    

}

// void app_main() {
//     MPU9250_Handle mpu;
//     float accel[3], gyro[3], mag[3];
    
//     // Initialize MPU9250 with SPI pins (MOSI=23, MISO=19, SCLK=18, CS=5)
//     if (!MPU9250_Init(&mpu, 23, 19, 18, 5)) {
//         printf("MPU9250 initialization failed!\n");
//         return;
//     }
    
//     while (1) {
//         // Read all sensor data
//         MPU9250_ReadAll(&mpu, accel, gyro, mag);
        
//         printf("Accel: X=%.2fg, Y=%.2fg, Z=%.2fg\n", accel[0], accel[1], accel[2]);
//         printf("Gyro: X=%.2f°/s, Y=%.2f°/s, Z=%.2f°/s\n", gyro[0], gyro[1], gyro[2]);
//         if (mpu.mag_enabled) {
//             printf("Mag: X=%.2fuT, Y=%.2fuT, Z=%.2fuT\n", mag[0], mag[1], mag[2]);
//         }
        
//         vTaskDelay(100 / portTICK_PERIOD_MS);
//     }
// }