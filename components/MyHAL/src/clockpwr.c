/*
 * clockpwr.c
 *
 *  Created on: 04/04/2025
 *      Author: Diogo
 */

#include "clockpwr.h"

// Mutex for thread-safe access
static SemaphoreHandle_t clockpwr_mutex = NULL;

// Initialize the mutex
static void CLOCKPWR_InitMutex(void) {
    if (clockpwr_mutex == NULL) {
        clockpwr_mutex = xSemaphoreCreateMutex();
    }
}

// Enable a peripheral clock
esp_err_t CLOCKPWR_ClockEnable(periph_module_t module) {
    CLOCKPWR_InitMutex();
    xSemaphoreTake(clockpwr_mutex, portMAX_DELAY);

    // Enable the peripheral module clock
    periph_module_enable(module);

    xSemaphoreGive(clockpwr_mutex);
    return ESP_OK;
}

// Disable a peripheral clock
esp_err_t CLOCKPWR_ClockDisable(periph_module_t module) {
    CLOCKPWR_InitMutex();
    xSemaphoreTake(clockpwr_mutex, portMAX_DELAY);

    // Disable the peripheral module clock
    periph_module_disable(module);

    xSemaphoreGive(clockpwr_mutex);
    return ESP_OK;
}


uint32_t CLOCKPWR_GetAPBClock(void) {

    uint32_t freq = esp_clk_apb_freq();

    return freq;
}