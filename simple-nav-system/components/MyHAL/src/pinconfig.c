/*
 * pinconfig.c
 *
 *  Created on: 04/04/2025
 *      Author: Diogo
 */

#include "pinconfig.h"
#include "gpio_matrix.h"
#include "pin.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "io_mux.h"

#define GPIO_PIN0_REG_BASE 0x3FF44088
#define GPIO_PIN0_REG_SIZE 0x00000004

void PINCONFIG_DisableInput(uint8_t pinId) { 

    __IO uint32_t *reg = IO_MUX_FindRegThroughPinId(pinId); // Find the register for the pin
    IO_MUX_FUN_IEnableCFG(reg, IPIN_DIS); // Disable input enable for the pin
}

void PINCONFIG_EnableInput(uint8_t pinId) { 

    __IO uint32_t *reg = IO_MUX_FindRegThroughPinId(pinId); // Find the register for the pin
    IO_MUX_FUN_IEnableCFG(reg, IPIN_EN); // Enable input enable for the pin
}

void PINCONFIG_OpenDrainMode(PINCFG_OpenDrainModeType mode, uint8_t pin) {
    
    volatile uint32_t *ODModeSelCfg = (volatile uint32_t *)((uintptr_t)&GPIO_MATRIX->PIN0_REG + (pin * 4));

    // Configure the open-drain mode for the specified pin
    if (mode == OPEN_DRAIN) {
        *ODModeSelCfg |= (1 << 2); // Set the open-drain mode bit
    } else {
        *ODModeSelCfg &= ~(1 << 2); // Clear the open-drain mode bit
    }

}

void PINCONFIG_Function(PIN_ValueType pinId, IO_MUX_MCU_SEL_FunctionType func) {
    
    __IO uint32_t *reg = IO_MUX_FindRegThroughPinId(pinId); // Find the register for the specified pin

    // Call the configuration function with the resolved register
    IO_MUX_MCU_SEL_FunctionCFG(reg, func);
}


void PINCONFIG_SetDriveStrength(uint8_t pinId,IO_MUX_FUN_DRV_StrengthType strength) {

    __IO uint32_t *reg = IO_MUX_FindRegThroughPinId(pinId); // Find the register for the specified pin

    IO_MUX_FUN_DRV_StrengthCFG(reg, strength); // Set the drive strength for the pin
}

void PINCONFIG_ResistorMode(PINCFG_ResistorModeType mode, uint8_t pin){
        
    __IO uint32_t *reg = IO_MUX_FindRegThroughPinId(pin);

    // Configure the resistor mode for the specified pin
    if (mode == PULL_UP) {

        IO_MUX_FUN_WPU_PinCFG(reg,INTPUP_EN); // Set the pull-up resistor mode bit
        IO_MUX_FUN_WPD_PinCFG(reg,INTPDN_DIS); // Clear the pull-down resistor mode bit
        
    } else if (mode == PULL_DOWN) {

        IO_MUX_FUN_WPU_PinCFG(reg,INTPUP_DIS); // Clear the pull-up resistor mode bit
        IO_MUX_FUN_WPD_PinCFG(reg,INTPDN_EN); // Set the pull-down resistor mode bit

    } else if(mode == NONE) {

        IO_MUX_FUN_WPU_PinCFG(reg,INTPUP_DIS); // Clear the pull-up resistor mode bit for none
        IO_MUX_FUN_WPD_PinCFG(reg,INTPDN_DIS); // Clear the pull-down resistor mode bit for none
    }
}