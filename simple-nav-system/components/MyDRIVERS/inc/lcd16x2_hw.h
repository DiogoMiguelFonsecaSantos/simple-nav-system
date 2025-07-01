
#ifndef COMPONENTS_MYDRIVERS_INC_LCD16X2_HW_H_
#define COMPONENTS_MYDRIVERS_INC_LCD16X2_HW_H_

#include "i2c_protocol.h"
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

// LCD instructions
#define LCD_CLEAR_DISPLAY       0x01
#define LCD_RETURN_HOME         0x02
#define LCD_ENTRY_MODE_SET      0x04
#define LCD_DISPLAY_CONTROL     0x08
#define LCD_FUNCTION_SET        0x20
#define LCD_SET_DDRAM_ADDR      0x80

// LCD flags
#define LCD_ENTRY_LEFT          0x02
#define LCD_DISPLAY_ON          0x04
#define LCD_DISPLAY_OFF         0x00
#define LCD_CURSOR_ON           0x02
#define LCD_CURSOR_OFF          0x00
#define LCD_BLINK_ON            0x01
#define LCD_BLINK_OFF           0x00
#define LCD_2LINE               0x08
#define LCD_5x8DOTS             0x00

// PCF8574 pin mapping (common)
#define LCD_BACKLIGHT           0x08
#define LCD_ENABLE              0x04
#define LCD_RW                  0x02
#define LCD_RS                  0x01

#define LCD_I2C_ADDR            0x27    // Change if needed

#define PULSE_PERIOD 500
#define CMD_PERIOD 4100

#define BACKLIGHT 8
#define DATA 1

void lcd_send_byte(uint8_t byte, uint8_t mode);
void lcd_send_nibble(uint8_t nibble, uint8_t mode);

#endif /* COMPONENTS_MYDRIVERS_INC_LCD16X2_HW_H_ */