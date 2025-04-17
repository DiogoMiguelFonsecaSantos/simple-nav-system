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

typedef enum{

    GPIO0 = 0,
    U0TXD = 1,
    GPIO2 = 2,
    U0RXD = 3,
    GPIO4 = 4,
    GPIO5 = 5,
    SD_CLK = 6,
    SD_DATA0 = 7,
    SD_DATA1 = 8,
    SD_DATA2 = 9,
    SD_DATA3 = 10,
    SD_CMD = 11,
    MTDI = 12,
    MTCK = 13,
    MTMS = 14,
    MTDO = 15,
    GPIO16 = 16,
    GPIO17 = 17,
    GPIO18 = 18,
    GPIO19 = 19,
    GPIO21 = 21,
    GPIO22 = 22,
    GPIO23 = 23,
    GPIO25 = 25,
    GPIO26 = 26,
    GPIO27 = 27,
    XP_32K = 32,
    XN_32K = 33,
    VDET_1 = 34,
    VDET_2 = 35,
    SENSOR_VP = 36,
    SENSOR_CAPP = 37,
    SENSOR_CAPN = 38,
    SENSOR_VN = 39
}PIN_ValueType;

typedef enum PIN_DirectionEnum{ //direction is either input or output
	INPUT, OUTPUT
} PIN_DirectionEnumType;

void PIN_Direction(PIN_ValueType pinId, PIN_DirectionEnumType dir);
void PIN_Set(PIN_ValueType pinId);   
void PIN_Clear(PIN_ValueType pinId);
bool PIN_Value(PIN_ValueType pinId);


//pin reset
//pin direction

#endif /* COMPONENTS_MYHAL_INC_PIN_H_ */
