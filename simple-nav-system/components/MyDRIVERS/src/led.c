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

    // Configure the LED pin as output
    GPIO_EnableOutput(LED_PIN);
    
    // Set the initial state of the LED
    if (state == ON) {
        GPIO_ClearOutput(LED_PIN);
    } else {
		GPIO_SetOutput(LED_PIN);
        
    }
}

bool LED_GetState(void) {
    // Read the current state of the LED pin
    return !GPIO_ReadInput(LED_PIN);
}

void LED_On(void) {
    // Turn the LED ON
    GPIO_ClearOutput(LED_PIN);
}

void LED_Off(void) {
    // Turn the LED OFF
    GPIO_SetOutput(LED_PIN);
}

void LED_Toggle(void) {
    // Toggle the state of the LED
    if (LED_GetState()) {
        LED_Off();
        
    } else {
        LED_On();
    }
}