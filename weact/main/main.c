#include <stdio.h>
#include <stdbool.h>
#include "weact.h"
#include "spi_protocol.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    SPI_PROTOCOLInit();
    WEACT_Epaper_Init();

    while (true) {
        WEACT_Epaper_PaintBlack();
        vTaskDelay(pdMS_TO_TICKS(2000));

        WEACT_Epaper_PaintWhite();
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}