/*
 * pinconfig.c
 *
 *  Created on: 04/04/2025
 *      Author: Diogo
 */

#include "pinconfig.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "hal/aes_hal.h"


void PINCFG_Function(PIN_ValueType pinId, PINCFG_FunctionType func) {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << pinId),
        .mode = func,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&io_conf);
}

void PINCFG_ResistorMode(PIN_ValueType pinId, PINCFG_ResistorModeType mode) {
    gpio_set_pull_mode(pinId, mode);
}

void PINCFG_OpenDrainMode(PIN_ValueType pinId, PINCFG_OpenDrainModeType func) {
    gpio_set_direction(pinId, func ? GPIO_MODE_OUTPUT_OD : GPIO_MODE_OUTPUT);
}


