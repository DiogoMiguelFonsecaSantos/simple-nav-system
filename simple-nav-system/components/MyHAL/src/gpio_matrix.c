/*
 * gpio_matrix.c
 *
 *  Created on: 13/04/2025
 *      Author: Diogo
 */

 #include "gpio_matrix.h"
 #include "regs_gpio_matrix.h"
 #include <stdint.h>
 #include <stdbool.h>

void GPIO_OverwriteOutput(uint8_t gpio) {
    if (gpio < 32) {
        // Overwrite GPIO 0-31 output
        GPIO_MATRIX->OUT = (1 << gpio);
    } else if (gpio < 40) {
        // Overwrite GPIO 32-39 output
        GPIO_MATRIX->OUT1 = (1 << (gpio - 32));
    }
}

void GPIO_OVWREnable(uint8_t gpio) {
    if (gpio < 32) {
        // Enable GPIO 0-31 overwrite
        GPIO_MATRIX->ENABLE = (1 << gpio);
    } else if (gpio < 40) {
        // Enable GPIO 32-39 overwrite
        GPIO_MATRIX->ENABLE1 = (1 << (gpio - 32));
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
