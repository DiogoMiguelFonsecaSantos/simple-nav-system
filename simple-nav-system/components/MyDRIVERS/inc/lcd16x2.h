/*
 * lcd16x2.h
 *
 *  Created on: Jun 9, 2025
 *      Author: diogo
 */

#ifndef COMPONENTS_MYDRIVERS_INC_LCD16X2_H_
#define COMPONENTS_MYDRIVERS_INC_LCD16X2_H_

#include "lcd16x2_hw.h"

extern uint8_t lcd_backlight_state;

void lcd_command(uint8_t cmd);
void lcd_clear(void);
void lcd_write_char(char c);
void lcd_home(void);
void lcd_set_cursor(uint8_t col, uint8_t row);
void lcd_write_string(const char *str);
void lcd_backlight_on(void);
void lcd_backlight_off(void);
void lcd_init(void);

#endif /* COMPONENTS_MYDRIVERS_INC_LCD16X2_H_ */
