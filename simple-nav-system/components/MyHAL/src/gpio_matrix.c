/*
 * gpio_matrix.c
 *
 *  Created on: 13/04/2025
 *      Author: Diogo
 */

 #include "gpio_matrix.h"
 #include <stdint.h>
 #include <stdbool.h>

 void GPIO_OverwriteEnable(uint8_t gpio) {
    if (gpio < 32) {
        // Enable GPIO 0-31 overwrite
        GPIO_MATRIX->ENABLE = (1 << gpio);
    } else if (gpio < 40) {
        // Enable GPIO 32-39 overwrite
        GPIO_MATRIX->ENABLE1 = (1 << (gpio - 32));
    }
}

void GPIO_EnableOutput(uint8_t gpio) {
    if (gpio < 32) {
        // Enable GPIO 0-31 output
        GPIO_MATRIX->ENABLE_W1TS = (1 << gpio);
    } else if (gpio < 40) {
        // Enable GPIO 32-39 output
        GPIO_MATRIX->ENABLE1_W1TS = (1 << (gpio - 32));
    }
}

void GPIO_DisableOutput(uint8_t gpio) {
    if (gpio < 32) {
        // Disable GPIO 0-31 output
        GPIO_MATRIX->ENABLE_W1TC = (1 << gpio);
    } else if (gpio < 40) {
        // Disable GPIO 32-39 output
        GPIO_MATRIX->ENABLE1_W1TC = (1 << (gpio - 32));
    }
}

void GPIO_OverwriteOutput(uint8_t gpio) {
    if (gpio < 32) {
        // Overwrite GPIO 0-31 output
        GPIO_MATRIX->OUT = (1 << gpio);
    } else if (gpio < 40) {
        // Overwrite GPIO 32-39 output
        GPIO_MATRIX->OUT1 = (1 << (gpio - 32));
    }
}

void GPIO_SetOutput(uint8_t gpio) {
    if (gpio < 32) {
        // Set GPIO 0-31 output high
        GPIO_MATRIX->OUT_W1TS = (1 << gpio);
    } else if (gpio < 40) {
        // Set GPIO 32-39 output high
        GPIO_MATRIX->OUT1_W1TS = (1 << (gpio - 32));
    }
}

void GPIO_ClearOutput(uint8_t gpio) {
    if (gpio < 32) {
        // Clear GPIO 0-31 output
        GPIO_MATRIX->OUT_W1TC = (1 << gpio);
    } else if (gpio < 40) {
        // Clear GPIO 32-39 output
        GPIO_MATRIX->OUT1_W1TC = (1 << (gpio - 32));
    }
}

bool GPIO_ReadOutput(uint8_t gpio) {
    if (gpio < 32) {
        // Read output state for GPIO 0-31
        return (GPIO_MATRIX->OUT & (1 << gpio)) != 0;
    } else if (gpio < 40) {
        // Read output state for GPIO 32-39
        return (GPIO_MATRIX->OUT1 & (1 << (gpio - 32))) != 0;
    }
    return false; // Invalid GPIO
}

bool GPIO_ReadInput(uint8_t gpio) {
    if (gpio < 32) {
        // Read GPIO 0-31 input
        return (GPIO_MATRIX->IN & (1 << gpio)) != 0;
    } else if (gpio < 40) {
        // Read GPIO 32-39 input
        return (GPIO_MATRIX->IN1 & (1 << (gpio - 32))) != 0;
    }
    return false; // Invalid GPIO
}


uint8_t GPIO_GetBootConfig(void) {
    // Read the boot configuration from the STRAP register
    return (GPIO_MATRIX->STRAP & 0xFF); // Mask to get the relevant bits
}

uint32_t GPIO_GetStatus(void) {
    // Read the status of GPIO 0-31
    return GPIO_MATRIX->STATUS;
}

uint32_t GPIO_GetStatus1(void){
    // Read the status of GPIO 32-39
    return GPIO_MATRIX->STATUS1;
}

void GPIO_OverwriteInterruptStatus(uint32_t status){
    // Overwrite the interrupt status for GPIO 0-31
    GPIO_MATRIX->STATUS = status;
}

void GPIO_CLRStatInterruptFlag(uint8_t pin){
    // Clear the interrupt flag for a specific GPIO pin
    if (pin < 32) {
        GPIO_MATRIX->STATUS_W1TC = (1 << pin);
    } else if (pin < 40) {
        GPIO_MATRIX->STATUS1_W1TC = (1 << (pin - 32));
    }
}

void GPIO_SetStatInterruptFlag(uint8_t pin){
    // Set the interrupt flag for a specific GPIO pin
    if (pin < 32) {
        GPIO_MATRIX->STATUS_W1TS = (1 << pin);
    } else if (pin < 40) {
        GPIO_MATRIX->STATUS1_W1TS = (1 << (pin - 32));
    }
}

uint32_t GPIO_GetAPPCPUInterruptStatus(void) {
    // Read the ACPU interrupt status for GPIO 0-31
    return GPIO_MATRIX->ACPU_INT;
}

uint32_t GPIO_GetAPPCPU_NMI_InterruptStatus(void){
    // Read the ACPU NMI interrupt status for GPIO 0-31
    return GPIO_MATRIX->ACPU_NMI_INT;
}

uint32_t GPIO_GetPROPCUInterruptStatus(void){
    // Read the PCPU interrupt status for GPIO 0-31
    return GPIO_MATRIX->PCPU_INT;
}
uint32_t GPIO_GetPROPCU_NMI_InterruptStatus(void){
    // Read the PCPU NMI interrupt status for GPIO 0-31
    return GPIO_MATRIX->PCPU_NMI_INT;
}

uint8_t GPIO_GetAPPCPU_INT_InterruptStatus(void){
    // Read the ACPU interrupt status for GPIO 32-39
    return GPIO_MATRIX->ACPU_INT1;
}
uint8_t GPIO_GetAPPCPU_NMIINT_InterruptStatus(void){
    // Read the ACPU NMI interrupt status for GPIO 32-39
    return GPIO_MATRIX->ACPU_NMI_INT1;
}

uint8_t GPIO_GetPROPCPU_INT_InterruptStatus(void){
    // Read the PCPU interrupt status for GPIO 32-39
    return GPIO_MATRIX->PCPU_INT1;
}

uint8_t GPIO_GetPROPCPU_NMIINT_InterruptStatus(void){
    // Read the PCPU NMI interrupt status for GPIO 32-39
    return GPIO_MATRIX->PCPU_NMI_INT1;
}

void GPIO_PINn_INT_EnableCFG(__IO uint32_t *reg, uint8_t bits) {

    // Clear the previous configuration
    *reg &= ~( 0x0F << 13);
    // Enable interrupt bits for the specified GPIO pin
    *reg |= (bits << 13); 
}
void GPIO_PINWAKEUP_EnableCFG(__IO uint32_t *reg, WakeUPCPUTypeDef valToWakeUp){

    // Clear the previous configuration
    *reg &= ~( 1 << 10);
    // Enable wakeup for the specified GPIO pin
    *reg |= (valToWakeUp << 10);
}
void GPIO_PINn_INTTypeCFG(__IO uint32_t *reg,PINIntTypeDef valIntType){

    // Clear the previous configuration
    *reg &= ~( 0x07 << 7);
    // Set the interrupt type for the specified GPIO pin
    *reg |= (valIntType << 7); 
}
void GPIO_PINn_PadDriverCFG(__IO uint32_t *reg, PINPadDriverTypeDef value){

    // Clear the previous configuration
    *reg &= ~(1 << 2);
    // Set the pad driver type for the specified GPIO pin
    *reg |= (value << 2); 
}

void GPIO_PINnCustomConfigure(__IO uint32_t *reg, uint8_t bits, WakeUPCPUTypeDef value,
     PINIntTypeDef valIntType,PINPadDriverTypeDef valuePadDriver){

    // Custom configuration for the specified GPIO pin
    GPIO_PINn_INT_EnableCFG(reg, bits); // Enable interrupt bits
    GPIO_PINWAKEUP_EnableCFG(reg, value); // Enable wakeup
    GPIO_PINn_INTTypeCFG(reg, valIntType); // Set interrupt type
    GPIO_PINn_PadDriverCFG(reg, valuePadDriver); // Set pad driver type
    }


void GPIO_SelectIfSignalBypass(__IO uint32_t *reg, SignalInSelectTypeDef where) {

    // Select if the signal is bypassed or not
    if (where == IO_MPLEX) {
        *reg &= ~(1 << 7); // Clear the bit 7 to select IO_MUX
    } else {
        *reg |= (1 << 7); // Set the bit 7 to select GPIO_MTX
    }
}

void GPIO_SelectIfInvertInSignal(__IO uint32_t *reg, FunctionInInvSelectTypeDef invbit) {

    // Select if the input signal is inverted or not
    if (invbit == NINV) {
        *reg &= ~(1 << 6); // Clear the bit 6 to select non-inverted
    } else {
        *reg |= (1 << 6); // Set the bit 6 to select inverted
    }
}

void GPIO_PeripheralInputSelectionControl(__IO uint32_t *reg, FunctionPeriphInputSelectTypeDef whichgpiopin) {

    // Select the peripheral input for the GPIO pin
    *reg &= ~(0x3F); // Clear the lower 6 bits
    *reg |= (whichgpiopin & 0x3F); // Set the new value
}

void GPIO_FunctionInSelect_CustomRegConfig(__IO uint32_t *reg, SignalInSelectTypeDef where, FunctionInInvSelectTypeDef invbit, 
    FunctionPeriphInputSelectTypeDef whichgpiopin){

    // Custom configuration for the function input selection
    GPIO_SelectIfSignalBypass(reg, where); // Select if the signal is bypassed
    GPIO_SelectIfInvertInSignal(reg, invbit); // Select if the input signal is inverted
    GPIO_PeripheralInputSelectionControl(reg, whichgpiopin); // Select the peripheral input
}

void GPIO_SelectIfInvertOutENSignal(__IO uint32_t *reg, FunctionOEnableInvSelectTypeDef invbit){
    // Select if the output enable signal is inverted or not
    if (invbit == NINV_OUTEN) {
        *reg &= ~(1 << 11); // Clear the bit 11 to select non-inverted
    } else {
        *reg |= (1 << 11); // Set the bit 6 to select inverted
    }

}

void GPIO_ForceOEnableSignalSource(__IO uint32_t *reg,SourceForOutputEnableTypeDef source){
    // Select the source for the output enable signal
    if (source == OEN_PERIPHERAL) {
        *reg &= ~(1 << 10); // Clear the bit 10 to select OEN_PERIPHERAL
    } else {
        *reg |= (1 << 10); // Set the bit 10 to select EN_REGn
    }
}

void GPIO_SelectIfInvertOutSignal(__IO uint32_t *reg,FunctionOutputValInvSelectTypeDef invbit){
    // Select if the output signal is inverted or not
    if (invbit == NINV_OUT) {
        *reg &= ~(1 << 9); // Clear the bit 9 to select non-inverted
    } else {
        *reg |= (1 << 9); // Set the bit 9 to select inverted
    }
}

void GPIO_FuncOutputControlSelection(__IO uint32_t *reg, uint16_t s){
    // Set the function output control selection
    *reg &= ~(0x1FF); // Clear the lower 9 bits
    *reg |= (s & 0x1FF); // Set the new value
}

void GPIO_FunctionOutSelect_CustomRegConfig(__IO uint32_t *reg, FunctionOEnableInvSelectTypeDef invbit, SourceForOutputEnableTypeDef source, 
    FunctionOutputValInvSelectTypeDef invbit2, uint8_t s){
    // Custom configuration for the function output selection
    GPIO_SelectIfInvertOutENSignal(reg, invbit); // Select if the output enable signal is inverted
    GPIO_ForceOEnableSignalSource(reg, source); // Select the source for the output enable signal
    GPIO_SelectIfInvertOutSignal(reg, invbit2); // Select if the output signal is inverted
    GPIO_FuncOutputControlSelection(reg, s); // Set the function output control selection
    }