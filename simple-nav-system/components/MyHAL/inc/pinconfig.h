/*
 * pinconfig.h
 *
 *  Created on: 04/04/2025
 *      Author: Diogo
 */

#ifndef COMPONENTS_MYHAL_INC_PINCONFIG_H_
#define COMPONENTS_MYHAL_INC_PINCONFIG_H_


#include <stdint.h>
#include <stdbool.h>
#include "gpio_matrix.h"
#include "pin.h"
#include "io_mux.h"
#include "regs_gpio_matrix.h"
#include "regs_io_mux.h"

typedef enum PINCFG_ResistorModeEnum {
	PULL_UP, NONE, PULL_DOWN
}PINCFG_ResistorModeType;

typedef enum PINCFG_OpenDrainModeEnum {
	NORMAL, OPEN_DRAIN
}PINCFG_OpenDrainModeType;

void PINCONFIG_DisableInput(uint8_t pinId);
void PINCONFIG_EnableInput(uint8_t pinId);
void PINCONFIG_Function(PIN_ValueType pinId, IO_MUX_MCU_SEL_FunctionType func);
void PINCONFIG_ResistorMode(PINCFG_ResistorModeType mode, uint8_t pin);
void PINCONFIG_OpenDrainMode(PINCFG_OpenDrainModeType mode, uint8_t pin);
void PINCONFIG_SetDriveStrength(uint8_t pinId, IO_MUX_FUN_DRV_StrengthType strength);

#endif /* COMPONENTS_MYHAL_INC_PINCONFIG_H_ */
