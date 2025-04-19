/*
 * pin.h
 *
 *  Created on: 04/04/2025
 *      Author: Diogo
 */

#ifndef COMPONENTS_MYHAL_INC_PIN_H_
#define COMPONENTS_MYHAL_INC_PIN_H_

#include <stdint.h>
#include <stdbool.h>

#define GPIO_MATRIX_OUT_BASE 0x3FF44530
#define GPIO_MATRIX_OUT_SZ   0x00000004

typedef enum {
    PIN_GPIO0 = 0,
    PIN_U0TXD = 1,
    PIN_GPIO2 = 2,
    PIN_U0RXD = 3,
    PIN_GPIO4 = 4,
    PIN_GPIO5 = 5,
    PIN_SD_CLK = 6,
    PIN_SD_DATA0 = 7,
    PIN_SD_DATA1 = 8,
    PIN_SD_DATA2 = 9,
    PIN_SD_DATA3 = 10,
    PIN_SD_CMD = 11,
    PIN_MTDI = 12,
    PIN_MTCK = 13,
    PIN_MTMS = 14,
    PIN_MTDO = 15,
    PIN_GPIO16 = 16,
    PIN_GPIO17 = 17,
    PIN_GPIO18 = 18,
    PIN_GPIO19 = 19,
    PIN_GPIO21 = 21,
    PIN_GPIO22 = 22,
    PIN_GPIO23 = 23,
    PIN_GPIO25 = 25,
    PIN_GPIO26 = 26,
    PIN_GPIO27 = 27,
    PIN_XP_32K = 32,
    PIN_XN_32K = 33,
    PIN_VDET_1 = 34,
    PIN_VDET_2 = 35,
    PIN_SENSOR_VP = 36,
    PIN_SENSOR_CAPP = 37,
    PIN_SENSOR_CAPN = 38,
    PIN_SENSOR_VN = 39
} PIN_ValueType;

typedef enum PIN_DirectionEnum{ //direction is either input or output
	INPUT, OUTPUT
} PIN_DirectionEnumType;

void PIN_Direction(PIN_ValueType pinId, PIN_DirectionEnumType dir);
void PIN_Set(PIN_ValueType pinId);   
void PIN_Clear(PIN_ValueType pinId);
bool PIN_Value(PIN_ValueType pinId);
void PIN_Reset(PIN_ValueType pinId); //pin reset
void PIN_SetPinAsOutput(PIN_ValueType pinId); //set pin as output
void PIN_InitGPIO_OutputPin(PIN_ValueType pinId); //initialize GPIO output pin

//pin reset

#endif /* COMPONENTS_MYHAL_INC_PIN_H_ */
