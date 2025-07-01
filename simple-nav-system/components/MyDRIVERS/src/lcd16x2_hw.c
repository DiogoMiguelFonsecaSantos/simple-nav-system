
#include "lcd16x2_hw.h"

uint8_t lcd_backlight_state = LCD_BACKLIGHT;

void lcd_send_nibble(uint8_t nibble, uint8_t mode)
{
    uint8_t data = (nibble & 0xF0) | lcd_backlight_state | mode;
    i2c_protocol_write_byte(LCD_I2C_ADDR, data | LCD_ENABLE);
    vTaskDelay(pdMS_TO_TICKS(1));
    i2c_protocol_write_byte(LCD_I2C_ADDR, data & ~LCD_ENABLE);
    vTaskDelay(pdMS_TO_TICKS(1));
}

void lcd_send_byte(uint8_t byte, uint8_t mode)
{
    lcd_send_nibble(byte & 0xF0, mode);
    lcd_send_nibble((byte << 4) & 0xF0, mode);
}