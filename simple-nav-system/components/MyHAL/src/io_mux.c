/*
 * io_mux.c
 *
 *  Created on: 13/04/2025
 *      Author: Diogo
 */

#include "io_mux.h"
#include "regs_io_mux.h"
#include <stdint.h>

void IO_MUX_PIN_CTRL_OutCLK_I2S0(IO_MUX_PIN_CTRL_ClockOut clk_out) {

    switch (clk_out) {
    case CLK_OUT1:
        IO_MUX->PIN_CTRL = (IO_MUX->PIN_CTRL & ~0xF) | 0x0; // rrrrrxx0
        break;
    case CLK_OUT2:
        IO_MUX->PIN_CTRL = (IO_MUX->PIN_CTRL & ~0xFF) | 0x00; // rrrrrx00
        break;
    case CLK_OUT3:
        IO_MUX->PIN_CTRL = (IO_MUX->PIN_CTRL & ~0xF0F) | 0x000; // rrrrr0x0
        break;
    default:
        return; // Invalid clock output selection
    }
}

void IO_MUX_PIN_CTRL_OutCLK_I2S1(IO_MUX_PIN_CTRL_ClockOut clk_out) {

    switch (clk_out) {
    case CLK_OUT1:
        IO_MUX->PIN_CTRL = (IO_MUX->PIN_CTRL & ~0xF) | 0xF; // rrrrrxxF
        break;
    case CLK_OUT2:
        IO_MUX->PIN_CTRL = (IO_MUX->PIN_CTRL & ~0xFF) | 0x0F; // rrrrrx0F
        break;
    case CLK_OUT3:
        IO_MUX->PIN_CTRL = (IO_MUX->PIN_CTRL & ~0xF0F) | 0x00F; // rrrrr0xF
        break;
    default:
        return; // Invalid clock output selection
    }
}

void IO_MUX_PIN_CTRL_OutCLK_APPL(IO_MUX_PIN_CTRL_ClockOut clk_out) {

    switch (clk_out) {
    case CLK_OUT1:
        IO_MUX->PIN_CTRL = (IO_MUX->PIN_CTRL & ~0xF) | 0x6; // rrrrrxx6
        break;
    case CLK_OUT2:
        IO_MUX->PIN_CTRL = (IO_MUX->PIN_CTRL & ~0xFF) | 0x66; // rrrrrx66
        break;
    case CLK_OUT3:
        IO_MUX->PIN_CTRL = (IO_MUX->PIN_CTRL & ~0xF0F) | 0x606; // rrrrr6x6
        break;
    default:
        return; // Invalid clock output selection
    }
}

void IO_MUX_MCU_SEL_FunctionCFG(__IO uint32_t *reg, IO_MUX_MCU_SEL_FunctionType function) {

    if (reg == NULL) {
        return; // Invalid register pointer
    }
    // Clear the function bits 12 - 14
    *reg &= ~IO_MUX_MCU_SEL_MASK;
    // Set the function bits to the desired value
    *reg |= (function << 12); // Set the function bits to the desired value

}

void IO_MUX_FUN_DRV_StrengthCFG(__IO uint32_t *reg,IO_MUX_FUN_DRV_StrengthType strength){

    if (reg == NULL) {
        return; // Invalid register pointer
    }
    // Clear the strength bits 10 - 11
    *reg &= ~IO_MUX_FUN_DRV_MASK;
    // Set the strength bits to the desired value
    *reg |= (strength << 10); 

}

void IO_MUX_FUN_IEnableCFG(__IO uint32_t *reg, IO_MUX_FUN_IEnableType iEnable){

    if (reg == NULL) {
        return; // Invalid register pointer
    }
    // Clear the IEnable bit 9
    *reg &= ~IO_MUX_FUN_IE_MASK;
    // Set the IEnable bit to the desired value
    *reg |= (iEnable << 9); 
}

void IO_MUX_FUN_WPU_PinCFG(__IO uint32_t *reg, IO_MUX_FUN_WPU_PinType wpuPin){

    if (reg == NULL) {
        return; // Invalid register pointer
    }
    // Clear the WPU bit 8
    *reg &= ~IO_MUX_FUN_WPU_MASK;
    // Set the WPU bit to the desired value
    *reg |= (wpuPin << 8); 
}

void IO_MUX_FUN_WPD_PinCFG(__IO uint32_t *reg, IO_MUX_FUN_WPD_PinType wpdPin){

    if (reg == NULL) {
        return; // Invalid register pointer
    }
    // Clear the WPD bit 7
    *reg &= ~IO_MUX_FUN_WPD_MASK;
    // Set the WPD bit to the desired value
    *reg |= (wpdPin << 7); 
}

void IO_MUX_SLP_SELModeCFG(__IO uint32_t *reg, IO_MUX_SLP_SELMode slpSelMode{

    if (reg == NULL) {
        return; // Invalid register pointer
    }
    // Clear the SLP_SEL bit 1
    *reg &= ~IO_MUX_SLP_SEL_MASK;
    // Set the SLP_SEL bit to the desired value
    *reg |= (slpSelMode << 1); 
}

void IO_MUX_MCU_DRV_StrengthCFG(__IO uint32_t *reg, IO_MUX_MCU_DRV_StrengthType sleepStrength){
    if (reg == NULL) {
        return; // Invalid register pointer
    }
    // Clear the sleep strength bits 5 - 6
    *reg &= ~IO_MUX_MCU_DRV_MASK;
    // Set the sleep strength bits to the desired value
    *reg |= (sleepStrength << 5); 
}

void IO_MUX_MCU_IEnableCFG(__IO uint32_t *reg, IO_MUX_MCU_IEnableType sleepIEnable){

    if (reg == NULL) {
        return; // Invalid register pointer
    }
    // Clear the sleep IEnable bit 4
    *reg &= ~IO_MUX_MCU_IE_MASK;
    // Set the sleep IEnable bit to the desired value
    *reg |= (sleepIEnable << 4);
}

void IO_MUX_MCU_WPU_PinCFG(__IO uint32_t *reg, IO_MUX_MCU_WPU_PinType sleepWpuPin){

    if (reg == NULL) {
        return; // Invalid register pointer
    }
    // Clear the sleep WPU bit 3
    *reg &= ~IO_MUX_MCU_WPU_MASK;
    // Set the sleep WPU bit to the desired value
    *reg |= (sleepWpuPin << 3); 
}

void IO_MUX_MCU_WPD_PinCFG(__IO uint32_t *reg, IO_MUX_MCU_WPD_PinType sleepWpdPin){

    if (reg == NULL) {
        return; // Invalid register pointer
    }
    // Clear the sleep WPD bit 2
    *reg &= ~IO_MUX_MCU_WPD_MASK;
    // Set the sleep WPD bit to the desired value
    *reg |= (sleepWpdPin << 2); 
}

void IO_MUX_MCU_OEnableCFG(__IO uint32_t *reg, IO_MUX_MCU_OEnableType sleepOEnable){

    if (reg == NULL) {
        return; // Invalid register pointer
    }
    // Clear the sleep OEnable bit 0
    *reg &= ~IO_MUX_MCU_OE_MASK;
    // Set the sleep OEnable bit to the desired value
    *reg |= (sleepOEnable << 0); 
}

void IO_MUX_RegisterCFG(__IO uint32_t *reg, IO_MUX_MCU_SEL_FunctionType function, IO_MUX_FUN_DRV_StrengthType strength, 
    IO_MUX_FUN_IEnableType iEnable, IO_MUX_FUN_WPU_PinType wpuPin, IO_MUX_FUN_WPD_PinType wpdPin, 
    IO_MUX_SLP_SELMode slpSelMode, IO_MUX_MCU_DRV_StrengthType sleepStrength, 
    IO_MUX_MCU_IEnableType sleepIEnable, IO_MUX_MCU_WPU_PinType sleepWpuPin, IO_MUX_MCU_WPD_PinType sleepWpdPin, 
    IO_MUX_MCU_OEnableType sleepOEnable){

    IO_MUX_MCU_SEL_FunctionCFG(reg, function);
    IO_MUX_FUN_DRV_StrengthCFG(reg, strength);
    IO_MUX_FUN_IEnableCFG(reg, iEnable);
    IO_MUX_FUN_WPU_PinCFG(reg, wpuPin);
    IO_MUX_FUN_WPD_PinCFG(reg, wpdPin);
    IO_MUX_SLP_SELModeCFG(reg, slpSelMode);
    IO_MUX_MCU_DRV_StrengthCFG(reg, sleepStrength);
    IO_MUX_MCU_IEnableCFG(reg, sleepIEnable);
    IO_MUX_MCU_WPU_PinCFG(reg, sleepWpuPin);
    IO_MUX_MCU_WPD_PinCFG(reg, sleepWpdPin);
    IO_MUX_MCU_OEnableCFG(reg, sleepOEnable);
}

