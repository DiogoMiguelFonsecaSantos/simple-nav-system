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

typedef enum PINCFG_ResistorModeEnum {
	PULL_UP, REPEATER, NONE, PULL_DOWN
}PINCFG_ResistorModeType;

typedef enum PINCFG_OpenDrainModeEnum {
	NORMAL, OPEN_DRAIN
}PINCFG_OpenDrainModeType;

#endif /* COMPONENTS_MYHAL_INC_PINCONFIG_H_ */
