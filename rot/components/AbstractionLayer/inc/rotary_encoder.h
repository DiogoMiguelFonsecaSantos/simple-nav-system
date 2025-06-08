/*
 * rotary_encoder.h
 *
 *  Created on: Jun 5, 2025
 *      Author: diogo
 */

#ifndef COMPONENTS_INC_ROTARY_ENCODER_H_
#define COMPONENTS_INC_ROTARY_ENCODER_H_

#include <stdint.h>

typedef enum {
    BUTTON_NOT_PRESSED = 0,
    BUTTON_CLICKED,
    BUTTON_DOUBLE_CLICKED,
    BUTTON_HELD
} encoder_button_event_t;

void rotary_encoder_init(void);
int32_t rotary_encoder_get_value(void);
encoder_button_event_t rotary_encoder_get_button(void);

#endif /* COMPONENTS_INC_ROTARY_ENCODER_H_ */
