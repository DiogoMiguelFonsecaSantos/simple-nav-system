#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"

#define DELAY_MS          500
#define GPIO_LED          26

void app_main(void)
{
    
    GPIO_EnableOutput(GPIO_LED); // Enable GPIO 12 as output
    GPIO_SetOutput(GPIO_LED); // Set GPIO 12 high (LED ON)
    vTaskDelay(pdMS_TO_TICKS(DELAY_MS)); // Delay for 5 seconds

    while (1)
    {
        // Set GPIO 22 high
        if (GPIO_ReadOutput(GPIO_LED)) {
            GPIO_ClearOutput(GPIO_LED);
            
        } else {
            GPIO_SetOutput(GPIO_LED);
        }
        printf("LED is %s\n\n", GPIO_ReadOutput(GPIO_LED) ? "ON" : "OFF");
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
    }   
}
