/*
 * gpio_matrix.h
 *
 *  Created on: 13/04/2025
 *      Author: Diogo
 */

#ifndef COMPONENTS_MYHAL_INC_GPIO_MATRIX_H_
#define COMPONENTS_MYHAL_INC_GPIO_MATRIX_H_

#include <stdint.h>
#include <stdbool.h>
#include "regs_gpio_matrix.h"

void GPIO_OverwriteOutput(uint8_t gpio);
void GPIO_SetOutput(uint8_t gpio);
void GPIO_ClearOutput(uint8_t gpio);
void GPIO_OVWREnable(uint8_t gpio);
void GPIO_EnableOutput(uint8_t gpio);
void GPIO_DisableOutput(uint8_t gpio);
bool GPIO_ReadInput(uint8_t gpio);

#endif /* COMPONENTS_MYHAL_INC_GPIO_MATRIX_H_ */
