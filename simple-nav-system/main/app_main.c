#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"

#define DELAY_MS          6000
#define GPIO_LED          22

void app_main(void)
{
    // Initialize the LED
    LED_Init(ON); // Initialize LED in OFF state
    vTaskDelay(pdMS_TO_TICKS(5000)); // Delay for 5 seconds

    while (1)
    {
        // Set GPIO 22 high
        LED_Toggle(); // Toggle the LED state
        printf("LED is %s\n\n", LED_GetState() ? "ON" : "OFF");
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
    }   
}
