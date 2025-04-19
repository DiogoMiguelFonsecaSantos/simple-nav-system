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

#define BOOTDELAY_MS      5000
#define DELAY_MS          100
#define GPIO_LED          26
#define GPIO_BLUE         12
#define LED               22

void app_main(void)
{
    PIN_Reset(GPIO_BLUE); // Reset GPIO 12
    PIN_InitGPIO_OutputPin(GPIO_BLUE); // Initialize GPIO 12 as output

    gpio_dump_io_configuration(stdout, (1ULL << 12));
    PIN_Set(GPIO_BLUE);

    PIN_Reset(LED); // Reset GPIO 12
    PIN_InitGPIO_OutputPin(LED); // Initialize GPIO 12 as output
    PIN_Set(LED); // Set GPIO 12 output

    gpio_dump_io_configuration(stdout, (1ULL << LED));

    vTaskDelay(pdMS_TO_TICKS(BOOTDELAY_MS)); // Delay for 5 seconds

    while (1)
    {

        PIN_Clear(GPIO_BLUE); // Clear GPIO 12 output
        PIN_Clear(LED); // Clear GPIO 12 output
        printf("LED is OFF\n"); 
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS)); // Delay
        
        PIN_Set(GPIO_BLUE); // Set GPIO 12 output
        PIN_Set(LED);
        printf("LED is ON\n");
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS)); // Delay
        bool status = PIN_Value(GPIO_BLUE); // Read GPIO 12 value
        if (status) {
            printf("GPIO 12 is HIGH\n");
        } else {
            printf("GPIO 12 is LOW\n");
        }

    }
    
}
