/*
 * clockpwr.h
 *
 *  Created on: 04/04/2025
 *      Author: Diogo
 */

#ifndef COMPONENTS_MYHAL_INC_CLOCKPWR_H_
#define COMPONENTS_MYHAL_INC_CLOCKPWR_H_

#include <stdint.h>
#include "esp_err.h"
#include "esp_pm.h"
#include "soc/soc.h"
#include "esp_private/esp_clk.h"
#include "esp_private/periph_ctrl.h"
#include "soc/periph_defs.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "sdkconfig.h"

// Enable a peripheral clock
esp_err_t CLOCKPWR_ClockEnable(periph_module_t module);

// Disable a peripheral clock
esp_err_t CLOCKPWR_ClockDisable(periph_module_t module);

// Get the current APB clock frequency
uint32_t CLOCKPWR_GetAPBClock(void);

#endif /* COMPONENTS_MYHAL_INC_CLOCKPWR_H_ */
