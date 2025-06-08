#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "rotary_encoder.h"

void app_main(void)
{
    rotary_encoder_init();
    int32_t last_val = 0;

    while (1) {
        int32_t val = rotary_encoder_get_value();
        if (val != last_val) {
            printf("Encoder value: %" PRId32 "\n", val);
            last_val = val;
        }

        encoder_button_event_t btn = rotary_encoder_get_button();
        if (btn != BUTTON_NOT_PRESSED) {
            const char* names[] = {
                "NOT PRESSED", "CLICKED", "DOUBLE CLICKED", "HELD"
            };
            printf("Button: %s\n", names[btn]);
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
