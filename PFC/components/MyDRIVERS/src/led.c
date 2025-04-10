/*
 * led.c
 *
 *  Created on: 05/04/2025
 *      Author: Diogo
 */

#include "led.h"
#include "driver/gpio.h"
#include "pin.h"
#include "pinconfig.h"

// Define the GPIO pin for the LED
#define LED_PIN 22 // GPIO22 on the ESP32

static bool ledState = false; // Tracks the current state of the LED

void LED_Init(bool state) {
    // Configure the LED pin as an output
    gpio_reset_pin(LED_PIN);
    PIN_SetDirection(LED_PIN, OUTPUT);
	
    // Set the initial state of the LED
    if (state) {
        PIN_Set(LED_PIN);
        ledState = true;
    } else {
        PIN_Clear(LED_PIN);
        ledState = false;
    }
}

bool LED_GetState(void) {
    // Return the current state of the LED
    return PIN_GetLevel(LED_PIN);
}

void LED_On(void) {
    // Turn the LED ON
    PIN_Set(LED_PIN);
    ledState = true;
}

void LED_Off(void) {
    // Turn the LED OFF
    PIN_Clear(LED_PIN);
    ledState = false;
}

void LED_Toggle(void) {
    // Toggle the LED state
    if (ledState) {
        PIN_Clear(LED_PIN);
        ledState = false;
    } else {
        PIN_Set(LED_PIN);
        ledState = true;
    }
}