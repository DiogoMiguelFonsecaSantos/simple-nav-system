#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hal/gpio_types.h"
#include "io_mux.h"
#include "gpio_matrix.h"
#include "driver/gpio.h"

#define BOOTDELAY_MS      5000
#define DELAY_MS          100
#define GPIO_LED          26
#define GPIO_BLUE         12


void app_main(void)
{
    GPIO_FuncOutputControlSelection(&GPIO_MATRIX->FUNC12_OUT_SEL_CFG, 0x100);
    GPIO_ForceOEnableSignalSource(&GPIO_MATRIX->FUNC12_OUT_SEL_CFG,EN_REGn);
    GPIO_EnableOutput(GPIO_BLUE);

    IO_MUX_MCU_SEL_FunctionCFG(&IO_MUX->MTDI,F2_GPIO);
    IO_MUX_FUN_DRV_StrengthCFG(&IO_MUX->MTDI, LOWEST);

    GPIO_SetOutput(GPIO_BLUE);
    vTaskDelay(pdMS_TO_TICKS(BOOTDELAY_MS)); // Delay for 5 seconds

    while (1)
    {

        // printf("ADDR: %lx\n", (long) FUNC12_OUT_SEL_CFG_REG);
        //vTaskDelay(pdMS_TO_TICKS(BOOTDELAY_MS));

        GPIO_ClearOutput(GPIO_BLUE); // Clear GPIO 12 output
        printf("LED is OFF\n"); 
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS)); // Delay
        
        GPIO_SetOutput(GPIO_BLUE); // Set GPIO 12 output
        printf("LED is ON\n");
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS)); // Delay
    }
    
}
