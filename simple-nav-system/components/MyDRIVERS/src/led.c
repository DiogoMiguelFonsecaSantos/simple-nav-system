/*
 * led.c
 *
 *  Created on: 05/04/2025
 *      Author: Diogo
 */

#include "led.h"
#include "pin.h"
#include "pinconfig.h"

// Define the GPIO pin for the LED
#define LED_PIN 22 // GPIO22 on the ESP32
// The LED is Active-Low

void LED_Init(LEDState state){

    PIN_Reset(LED_PIN); // Reset GPIO 12
    PIN_InitGPIO_OutputPin(LED_PIN); // Initialize GPIO 12 as output
    
    // Set the initial state of the LED
    if (state == ON) {
        PIN_Clear(LED_PIN);
    } else {
		PIN_Set(LED_PIN);
    }
}

bool LED_GetState(void) {
    // Read the current state of the LED pin
    return !PIN_Value(LED_PIN);
}

void LED_On(void) {
    // Turn the LED ON
    PIN_Clear(LED_PIN);
}

void LED_Off(void) {
    // Turn the LED OFF
    PIN_Set(LED_PIN);
}

void LED_Toggle(void) {
    // Toggle the state of the LED
    if (LED_GetState()) {
        LED_Off();
        
    } else {
        LED_On();
    }
}