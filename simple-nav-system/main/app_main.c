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

#define BOOTDELAY_MS      5000
#define DELAY_MS          50
#define GPIO_LED          26
#define GPIO_BLUE         12
#define LED               22
#define RED               26 

void blinkLED(void *pvParameters)
{
    while (1)
    {
        LED_Toggle(); // Toggle the LED state
        vTaskDelay(pdMS_TO_TICKS(50)); // Delay
    }
}


void app_main(void)
{
    LED_Init(ON); // Initialize the LED to ON state
    printf("LED is %s\n", LED_GetState() ? "ON" : "OFF");

    gpio_dump_io_configuration(stdout, (1ULL << LED));

    PIN_Reset(RED);
    PIN_InitGPIO_OutputPin(RED); // Initialize GPIO 12 as output
    PIN_Set(RED); // Set GPIO 12 output to HIGH

    vTaskDelay(pdMS_TO_TICKS(BOOTDELAY_MS)); // Delay for 5 seconds
    xTaskCreate(blinkLED, "BlinkLED", 2048, NULL, 5, NULL);
    while (1)
    {

        PIN_Clear(RED); // Clear GPIO 12 output
        printf("LED is OFF\n"); 
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS)); // Delay
        PIN_Set(RED);
        printf("LED is ON\n");
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS)); // Delay
        
    }
    
}

