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

#include "driver/gpio.h"


#define BOOTDELAY_MS      5000
#define DELAY_MS          100
#define GPIO_RED          26
#define GPIO_BLUE         12
#define GPIO_GREEN        14
#define GPIO_YELLOW       27 


// void blinkLED(void *pvParameters)
// {   
//     vTaskDelay(pdMS_TO_TICKS(BOOTDELAY_MS)); // Delay for 5 seconds
//     while (1)
//     {
//         LED_Toggle(); // Toggle the LED state
//         vTaskDelay(pdMS_TO_TICKS(50)); // Delay
//     }
// }

// void trafficLight(void *pvParameters)
// {   
//     PIN_Set(GPIO_GREEN); // Set GPIO 26 output to HIGH
//     vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 5 seconds
//     PIN_Clear(GPIO_GREEN); // Clear GPIO 26 output

//     PIN_Set(GPIO_YELLOW); // Set GPIO 27 output to HIGH
//     vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 5 seconds
//     PIN_Clear(GPIO_YELLOW); // Clear GPIO 27 output

//     PIN_Set(GPIO_RED); // Set GPIO 26 output to HIGH
//     vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 5 seconds
//     PIN_Clear(GPIO_RED); // Clear GPIO 26 output

//     PIN_Set(GPIO_BLUE); // Set GPIO 12 output to HIGH
//     vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 5 seconds
//     PIN_Clear(GPIO_BLUE); // Clear GPIO 12 output

//     PIN_Set(GPIO_GREEN);
//     vTaskDelay(pdMS_TO_TICKS(125)); // Delay for 5 seconds
//     PIN_Clear(GPIO_GREEN); // Clear GPIO 14 output

//     PIN_Set(GPIO_YELLOW); // Set GPIO 27 output to HIGH
//     vTaskDelay(pdMS_TO_TICKS(125)); // Delay for 5 seconds
//     PIN_Clear(GPIO_YELLOW); // Clear GPIO 27 output

//     PIN_Set(GPIO_RED); // Set GPIO 26 output to HIGH
//     vTaskDelay(pdMS_TO_TICKS(125)); // Delay for 5 seconds
//     PIN_Clear(GPIO_RED); // Clear GPIO 26 output

//     PIN_Set(GPIO_BLUE); // Set GPIO 12 output to HIGH
//     vTaskDelay(pdMS_TO_TICKS(125)); // Delay for 5 seconds
//     PIN_Clear(GPIO_BLUE); // Clear GPIO 12 output

//     PIN_Set(GPIO_GREEN);
//     vTaskDelay(pdMS_TO_TICKS(125)); // Delay for 5 seconds
//     PIN_Clear(GPIO_GREEN); // Clear GPIO 14 output

//     PIN_Set(GPIO_YELLOW); // Set GPIO 27 output to HIGH
//     vTaskDelay(pdMS_TO_TICKS(125)); // Delay for 5 seconds
//     PIN_Clear(GPIO_YELLOW); // Clear GPIO 27 output

//     PIN_Set(GPIO_RED); // Set GPIO 26 output to HIGH
//     vTaskDelay(pdMS_TO_TICKS(125)); // Delay for 5 seconds
//     PIN_Clear(GPIO_RED); // Clear GPIO 26 output

//     PIN_Set(GPIO_BLUE); // Set GPIO 12 output to HIGH
//     vTaskDelay(pdMS_TO_TICKS(125)); // Delay for 5 seconds
//     PIN_Clear(GPIO_BLUE); // Clear GPIO 12 output

//     while (1)
//     {
//         PIN_Set(GPIO_GREEN); // Set GPIO 14 output to HIGH (Green light ON)
//         vTaskDelay(pdMS_TO_TICKS(5000)); // Delay for 5 seconds
//         PIN_Clear(GPIO_GREEN); // Clear GPIO 14 output (Green light OFF)
//         PIN_Set(GPIO_YELLOW); // Set GPIO 27 output to HIGH (Yellow light ON)
//         vTaskDelay(pdMS_TO_TICKS(2000)); // Delay for 2 seconds
//         PIN_Clear(GPIO_YELLOW); // Clear GPIO 27 output (Yellow light OFF)
//         PIN_Set(GPIO_RED); // Set GPIO 26 output to HIGH (Red light ON)
//         vTaskDelay(pdMS_TO_TICKS(5000)); // Delay for 5 seconds
//         PIN_Clear(GPIO_RED); // Clear GPIO 26 output (Red light OFF)
//         PIN_Set(GPIO_BLUE); // Set GPIO 12 output to HIGH (Blue light ON)
//         vTaskDelay(pdMS_TO_TICKS(2000)); // Delay for 2 seconds
//         PIN_Clear(GPIO_BLUE); // Clear GPIO 12 output (Blue light OFF)
//     }
// }

// void app_main(void)
// {
//     LED_Init(ON); // Initialize the LED to ON state
//     printf("LED is %s\n", LED_GetState() ? "ON" : "OFF");

//     gpio_dump_io_configuration(stdout, (1ULL << 22));

//     PIN_Reset(GPIO_RED);
//     PIN_InitGPIO_OutputPin(GPIO_RED); // Initialize GPIO 26 as output
//     PIN_Reset(GPIO_BLUE);
//     PIN_InitGPIO_OutputPin(GPIO_BLUE); // Initialize GPIO 12 as output
//     PIN_Reset(GPIO_GREEN);
//     PIN_InitGPIO_OutputPin(GPIO_GREEN); // Initialize GPIO 14 as output
//     PIN_Reset(GPIO_YELLOW);
//     PIN_InitGPIO_OutputPin(GPIO_YELLOW); // Initialize GPIO 27 as output

//     xTaskCreate(blinkLED, "BlinkLED", 2048, NULL, 5, NULL);
//     xTaskCreate(trafficLight, "TrafficLight", 2048, NULL, 5, NULL);
//     while (1)
//     {
// 		printf("Hello!!!!!\n\n\n");
// 		vTaskDelay(pdMS_TO_TICKS(5000));
//     }
    

// }

void app_main(void) {

    SPIProtocol_Init(SPI3, 79,999, 0);

    const uint8_t dataToSend[] = {0xAA, 0xBB, 0xCC, 0xDD}; 
	
	//gpio_set_direction(5, GPIO_MODE_OUTPUT);
	gpio_dump_io_configuration(stdout, (1ULL << 5));
	gpio_dump_io_configuration(stdout, (1ULL << 18));
	gpio_dump_io_configuration(stdout, (1ULL << 23));
	gpio_dump_io_configuration(stdout, (1ULL << 19));
	
    while(1){
		
        // gpio_set_level(5, 0);
        // PIN_Clear(5);
        // SPI_HAL_TriggerOperation(SPI3); // Trigger the SPI operation
        // SPIProtocol_SendData(SPI3, dataToSend, 1);

        PIN_Clear(5); // Set GPIO 5 output to LOW
        SPIProtocol_SendData(SPI3, dataToSend, sizeof(dataToSend));
        PIN_Set(5); // Set GPIO 5 output to HIGH
        
        // gpio_set_level(5, 1);
        // vTaskDelay(pdMS_TO_TICKS(10)); // Delay for 10 miliseconds
        //PIN_Set(5);
    }
	
	
	
    // while (1) {  
    //     SPIProtocol_SendData(SPI3, dataToSend, sizeof(dataToSend));

    //     printf("Data sent over SPI\n");

    //     vTaskDelay(pdMS_TO_TICKS(2000)); 
    // }
}