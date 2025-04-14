/*
 * gpio_matrix.c
 *
 *  Created on: 13/04/2025
 *      Author: Diogo
 */

 #include "gpio_matrix.h"
 #include <stdint.h>
 #include <stdbool.h>

 void GPIO_SetOutput(uint8_t gpio) {
     if (gpio < 32) {
         GPIO_MATRIX->OUT_W1TS_REG = (1 << gpio);
     } else if (gpio <= 39) {
         GPIO_MATRIX->OUT1_W1TS_REG = (1 << (gpio - 32));
     }
 }
 
 void GPIO_ClearOutput(uint8_t gpio) {
     if (gpio < 32) {
         GPIO_MATRIX->OUT_W1TC_REG = (1 << gpio);
     } else if (gpio <= 39) {
         GPIO_MATRIX->OUT1_W1TC_REG = (1 << (gpio - 32));
     }
 }
 
 void GPIO_EnableOutput(uint8_t gpio) {
     if (gpio < 32) {
         GPIO_MATRIX->ENABLE_W1TS_REG = (1 << gpio);
     } else if (gpio <= 39) {
         GPIO_MATRIX->ENABLE1_W1TS_REG = (1 << (gpio - 32));
     }
 }
 
 void GPIO_DisableOutput(uint8_t gpio) {
     if (gpio < 32) {
         GPIO_MATRIX->ENABLE_W1TC_REG = (1 << gpio);
     } else if (gpio <= 39) {
         GPIO_MATRIX->ENABLE1_W1TC_REG = (1 << (gpio - 32));
     }
 }
 
 bool GPIO_ReadInput(uint8_t gpio) {
     if (gpio < 32) {
         return (GPIO_MATRIX->IN_REG >> gpio) & 0x1;
     } else if (gpio <= 39) {
         return (GPIO_MATRIX->IN1_REG >> (gpio - 32)) & 0x1;
     }
     return false;
 }
 


