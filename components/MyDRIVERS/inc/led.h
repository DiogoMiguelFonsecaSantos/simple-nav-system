/*
 * LED.H
 *
 *  Created on: 05/04/2025
 *      Author: Diogo
 */

#ifndef COMPONENTS_MYDRIVERS_INC_LED_H_
#define COMPONENTS_MYDRIVERS_INC_LED_H_

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Initializes the LED with the specified initial state.
 * 
 * @param state Initial state of the LED (true for ON, false for OFF).
 */
void LED_Init(bool state);

/**
 * @brief Retrieves the current state of the LED.
 * 
 * @return true if the LED is ON, false if it is OFF.
 */
bool LED_GetState(void);

/**
 * @brief Turns the LED ON.
 */
void LED_On(void);

/**
 * @brief Turns the LED OFF.
 */
void LED_Off(void);

/**
 * @brief Toggles the state of the LED.
 */
void LED_Toggle(void);

#endif /* COMPONENTS_MYDRIVERS_INC_LED_H_ */
