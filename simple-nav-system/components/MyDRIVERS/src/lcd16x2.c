/*
 * lcd16x2.c
 *
 *  Created on: Jun 9, 2025
 *      Author: diogo
 */

#include "lcd16x2.h"

void lcd_command(uint8_t cmd)
{
    lcd_send_byte(cmd, 0);
    if (cmd == LCD_CLEAR_DISPLAY || cmd == LCD_RETURN_HOME) {
        vTaskDelay(pdMS_TO_TICKS(2));
    } else {
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

void lcd_write_char(char c)
{
    lcd_send_byte((uint8_t)c, LCD_RS);
    vTaskDelay(pdMS_TO_TICKS(1));
}

void lcd_clear(void)
{
    lcd_command(LCD_CLEAR_DISPLAY);


#define LCD_RETURN_HOME 0x02


}

void lcd_home(void)
{
    lcd_command(LCD_RETURN_HOME);
}

void lcd_set_cursor(uint8_t col, uint8_t row)
{
    static const uint8_t row_offsets[] = {0x00, 0x40};
    if (row > 1) row = 1;
    lcd_command(LCD_SET_DDRAM_ADDR | (col + row_offsets[row]));
}

void lcd_write_string(const char *str)
{
    uint8_t row = 0, col = 0;
    lcd_set_cursor(col, row);
    while (*str) {
        if (*str == '\n') {
            row++;
            if (row > 1) row = 1; // Only 2 rows for 16x2
            col = 0;
            lcd_set_cursor(col, row);
        } else {
            lcd_write_char(*str);
            col++;
            if (col >= 16) { // Auto-wrap to next line if needed
                col = 0;
                row++;
                if (row > 1) row = 1;
                lcd_set_cursor(col, row);
            }
        }
        str++;
    }
}

void lcd_backlight_on(void)
{
    lcd_backlight_state = LCD_BACKLIGHT;
    lcd_send_byte(0, 0); // Refresh
}

void lcd_backlight_off(void)
{
    lcd_backlight_state = 0x00;
    lcd_send_byte(0, 0); // Refresh
}

void lcd_init(void)
{
    vTaskDelay(pdMS_TO_TICKS(50)); // Wait for LCD power-up

    // Initialization sequence (HD44780 datasheet)
    lcd_send_nibble(0x30, 0);
    vTaskDelay(pdMS_TO_TICKS(10));
    lcd_send_nibble(0x30, 0);
    vTaskDelay(pdMS_TO_TICKS(10));
    lcd_send_nibble(0x30, 0);
    vTaskDelay(pdMS_TO_TICKS(10));
    lcd_send_nibble(0x20, 0); // 4-bit mode
    vTaskDelay(pdMS_TO_TICKS(10));

    lcd_command(LCD_FUNCTION_SET | LCD_2LINE | LCD_5x8DOTS);
    lcd_command(LCD_DISPLAY_CONTROL | LCD_DISPLAY_ON | LCD_CURSOR_ON | LCD_BLINK_ON);
    lcd_clear();
    lcd_command(LCD_ENTRY_MODE_SET | LCD_ENTRY_LEFT);
    lcd_backlight_on();
}


