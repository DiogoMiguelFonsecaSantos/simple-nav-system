/*
 * pinconfig.h
 *
 *  Created on: 04/04/2025
 *      Author: Diogo
 */

#ifndef COMPONENTS_MYHAL_INC_PINCONFIG_H_
#define COMPONENTS_MYHAL_INC_PINCONFIG_H_

#include "driver/gpio.h"
#include <stdint.h>
#include <stdbool.h>
#include "hal/aes_hal.h"

typedef uint32_t PIN_ValueType;
typedef gpio_mode_t PINCFG_FunctionType;
typedef gpio_pull_mode_t PINCFG_ResistorModeType;
typedef bool PINCFG_OpenDrainModeType;

/**
 * @brief Configure the function (mode) of a GPIO pin.
 *
 * @param pinId GPIO pin number.
 * @param func GPIO mode (e.g., GPIO_MODE_INPUT, GPIO_MODE_OUTPUT, etc.).
 * 
 * @note IMPORTANT: This function configures the GPIO pin's mode. It should be called before using the pin.
 *       Not only that, but this is the "full version" of the PIN_SetDirection function, one can 
 *       use this function to set the pin as input, output, or any other mode supported by the GPIO driver, while
 *       PIN_SetDirection is a simplified version that only sets the pin as input or output.
 */
void PINCFG_Function(PIN_ValueType pinId, PINCFG_FunctionType func);

/**
 * @brief Configure the resistor mode (pull-up, pull-down, or none) of a GPIO pin.
 *
 * @param pinId GPIO pin number.
 * @param mode GPIO pull mode (e.g., GPIO_PULLUP_ONLY, GPIO_PULLDOWN_ONLY, GPIO_FLOATING).
 */
void PINCFG_ResistorMode(PIN_ValueType pinId, PINCFG_ResistorModeType mode);

/**
 * @brief Configure the open-drain mode of a GPIO pin.
 *
 * @param pinId GPIO pin number.
 * @param func Enable or disable open-drain mode (true for enable, false for disable).
 */
void PINCFG_OpenDrainMode(PIN_ValueType pinId, PINCFG_OpenDrainModeType func);

#endif /* COMPONENTS_MYHAL_INC_PINCONFIG_H_ */
