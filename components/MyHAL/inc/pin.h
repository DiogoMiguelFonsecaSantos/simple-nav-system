/*
 * pin.h
 *
 *  Created on: 04/04/2025
 *      Author: Diogo
 */

#ifndef COMPONENTS_MYHAL_INC_PIN_H_
#define COMPONENTS_MYHAL_INC_PIN_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    INPUT = 0,
    OUTPUT = 1
} PIN_Direction;

/**
 * @brief Sets the direction of a specified pin.
 * 
 * This function configures the direction of a given pin as either input or output.
 * 
 * @param pin The pin number to configure.
 * @param direction The desired direction for the pin. 
 *                  Use `PIN_Direction::INPUT` for input or `PIN_Direction::OUTPUT` for output.
 */
void PIN_SetDirection(uint8_t pin, PIN_Direction direction);

/**
 * @brief Sets the output level of a specified pin.
 * 
 * This function configures the logical level (high or low) of a given pin.
 * 
 * @param pin The pin number to configure.
 * @param level The desired output level:
 *              - `true` for high level.
 *              - `false` for low level.
 */
void PIN_SetLevel(uint8_t pin, uint32_t level);

void PIN_Clear(uint8_t pin);

void PIN_Set(uint8_t pin);

/**
 * @brief Retrieves the current logic level of the specified pin.
 * 
 * This function checks the state of the given pin and returns its 
 * current logic level as a boolean value.
 * 
 * @param pin The pin number to query.
 *            This should be a valid pin identifier.
 * 
 * @return true if the pin is at a high logic level, false if it is at a low logic level.
 */
int PIN_GetLevel(uint8_t pin);

void PIN_ToggleLevel(uint8_t pin);

#endif /* COMPONENTS_MYHAL_INC_PIN_H_ */
