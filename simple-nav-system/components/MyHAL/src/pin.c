/*
 * pin.c
 *
 *  Created on: 04/04/2025
 *      Author: Diogo
 */

#include "pin.h"
#include "hal/aes_hal.h"
#include <sys/_stdint.h>
#include <stdio.h>
#include "gpio_matrix.h"
#include "io_mux.h"
#include "pinconfig.h"

	
#define LED_BLUE 12
#define LED_GREEN 14
#define LED_RED 26
#define LED_YELLOW 27



void PIN_Direction(PIN_ValueType pinId, PIN_DirectionEnumType dir) { //does it even accept this numPins as arg?
    // Validate pinId
    if (pinId == 20 || pinId == 24 || pinId == 28 || pinId == 29 || pinId == 30 || pinId == 31) {
        // GPIO 20, 24, 28, 29, 30, and 31 are not available for GPIO matrix
        printf("GPIO%d is not available for GPIO matrix\n", pinId);
        return;
    }
    
    // Calculate the address of the FUNCy_OUT_SEL_CFG register
    volatile uint32_t *funcOutSelCfg = (volatile uint32_t *)((uintptr_t)&GPIO_MATRIX->FUNC0_OUT_SEL_CFG + (pinId * 4));

    // Configure the pin based on the direction
    if (dir == OUTPUT) {
        GPIO_FuncOutputControlSelection(funcOutSelCfg, 0x100);
        GPIO_ForceOEnableSignalSource(funcOutSelCfg,EN_REGn);
    } else if (dir == INPUT) {
        // Add input-specific configuration here if needed
        GPIO_DisableOutput(pinId); // Disable output for the pin
    }
}

void PIN_SetPinAsOutput(PIN_ValueType pinId){

    // Validate pinId
    if (pinId == 20 || pinId == 24 || pinId == 28 || pinId == 29 || pinId == 30 || pinId == 31) {
        // GPIO 20, 24, 28, 29, 30, and 31 are not available for GPIO matrix
        printf("GPIO%d is not available for GPIO matrix\n", pinId);
        return;
    }

    // Set the pin as output
    GPIO_EnableOutput(pinId); // Enable output for the pin

}

void PIN_InitGPIO_OutputPin(PIN_ValueType pinId){

    
    PIN_Direction(pinId, OUTPUT); // Set output
    PIN_SetPinAsOutput(pinId);
    PINCONFIG_Function(pinId, F2_GPIO); // Set function to GPIO
    PINCONFIG_SetDriveStrength(pinId, MEDIUM); // Set drive strength to 2

}

void PIN_Set(PIN_ValueType pinId){

    // Set the specified GPIO pin high
    GPIO_SetOutput(pinId);
}

void PIN_Clear(PIN_ValueType pinId){
    
        // Clear the specified GPIO pin (set it low)
        GPIO_ClearOutput(pinId);
}

bool PIN_Value(PIN_ValueType pinId){

    // Read the value of the specified GPIO pin
    return GPIO_ReadOutput(pinId);
}

void PIN_Reset(PIN_ValueType pinId) {
    // Validate pinId
    if (pinId == 20 || pinId == 24 || pinId == 28 || pinId == 29 || pinId == 30 || pinId == 31) {
        // GPIO 20, 24, 28, 29, 30, and 31 are not available for GPIO matrix
        printf("GPIO%d is not available for GPIO matrix\n", pinId);
        return;
    }
    
    GPIO_ClearOutput(pinId); // Clear the output state of the pin
    GPIO_DisableOutput(pinId); // Disable output for the pin

    PINCONFIG_DisableInput(pinId);
    PINCONFIG_ResistorMode(PULL_UP, pinId); // Disable pull-up and pull-down resistors
    PINCONFIG_Function(pinId, F2_GPIO); // Set function to GPIO

    GPIO_FuncOutputControlSelection((volatile uint32_t *)((uintptr_t)&GPIO_MATRIX->FUNC0_OUT_SEL_CFG + (pinId * 4)), 0x100);
    GPIO_SelectIfInvertOutSignal((volatile uint32_t *)((uintptr_t)&GPIO_MATRIX->FUNC0_OUT_SEL_CFG + (pinId * 4)), NINV_OUT); // Set output signal to non-inverted
    GPIO_ForceOEnableSignalSource((volatile uint32_t *)((uintptr_t)&GPIO_MATRIX->FUNC0_OUT_SEL_CFG + (pinId * 4)), EN_REGn); // Set output enable signal source to EN_REGn
    GPIO_SelectIfInvertOutENSignal((volatile uint32_t *)((uintptr_t)&GPIO_MATRIX->FUNC0_OUT_SEL_CFG + (pinId * 4)), NINV_OUT); // Set output enable signal to non-inverted

    GPIO_PINn_INT_EnableCFG((volatile uint32_t *)((uintptr_t)&GPIO_MATRIX->PIN0_REG + (pinId * 4)), 0); // Disable interrupt for the pin
    GPIO_PINn_INTTypeCFG((volatile uint32_t *)((uintptr_t)&GPIO_MATRIX->PIN0_REG + (pinId * 4)), INTDIS); // Set interrupt type to disable
    GPIO_PINn_PadDriverCFG((volatile uint32_t *)((uintptr_t)&GPIO_MATRIX->PIN0_REG + (pinId * 4)), NORMAL); // Set pad driver to normal

    printf("GPIO%d has been reset to default configuration\n", pinId);
}