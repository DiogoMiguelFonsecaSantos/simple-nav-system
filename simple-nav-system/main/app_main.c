#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define DELAY_MS          100
#define GPIO_OUT_W1TS_REG 0x3FF44008
#define GPIO_OUT_W1TC_REG 0x3FF4400C
#define GPIO_EN_REG       0x3FF44020
#define GPIO_LED          22

void app_main(void)
{

    volatile uint32_t* gpio_out_w1ts_reg = (volatile uint32_t*) GPIO_OUT_W1TS_REG;
    volatile uint32_t* gpio_out_w1tc_reg = (volatile uint32_t*) GPIO_OUT_W1TC_REG;
    volatile uint32_t* gpio_en_reg       = (volatile uint32_t*) GPIO_EN_REG;

    *gpio_en_reg = (1 << GPIO_LED);

    while(1)
    {

        *gpio_out_w1ts_reg = (1 << GPIO_LED);
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
        *gpio_out_w1tc_reg = (1 << GPIO_LED);
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
    }


}
