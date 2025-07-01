/*
 * epaper.c
 *
 *  Created on: May 18, 2025
 *      Author: diogo
 */

#include "epaper.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"
#include "pin.h"
#include <string.h>

//Hardware Reset: Toggle the display’s RST pin low and then high (e.g. 10 ms each) to reset the controller
//Software Reset: SW Reset (0x12): Send the software-reset command and wait briefly.

void EPAPER_WriteCMD(uint8_t cmd) {
    gpio_set_level(EPAPER_CS_PIN, 0);      // CS LOW
    gpio_set_level(EPAPER_DC_PIN, 0);      // Command mode
    SPI_PROTOCOLTransmit_EPAPER_Command(cmd);
    gpio_set_level(EPAPER_CS_PIN, 1);      // CS HIGH
    gpio_set_level(EPAPER_DC_PIN, 1);      // Data mode
}

void EPAPER_WriteData(const uint8_t *data, size_t len) {
    gpio_set_level(EPAPER_CS_PIN, 0);      // CS LOW
    SPI_PROTOCOLTransmit_EPAPER_Data(data, len);
    gpio_set_level(EPAPER_CS_PIN, 1);      // CS HIGH
}

void EPAPER_WaitUntilIdle(void) {
    while (gpio_get_level(EPAPER_BUSY_PIN) == 1) {
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void EPAPER_HardReset(void) {
    gpio_set_level(EPAPER_RST_PIN, 0); 
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(EPAPER_RST_PIN, 1);
    vTaskDelay(pdMS_TO_TICKS(10));
}

void EPAPER_SetInitConfig(void){

    EPAPER_HardReset();
    EPAPER_WriteCMD(0x12); // SWRESET
    vTaskDelay(pdMS_TO_TICKS(10));
}

void EPAPER_SendInitCode(void){

    EPAPER_WriteCMD(0x01); // Driver Output Control
    uint8_t driver_output[] = {0x27, 0x01, 0x00}; // Set display's vertical resolution with 296 pixels and Gate scanning sequence and direction to default
    EPAPER_WriteData(driver_output, 3);

    EPAPER_WriteCMD(0x11); // Data Entry Mode
    uint8_t data_entry = 0x03; // Set data entry sequence as Y increment, X increment and  the address counter is updated in the X direction
    EPAPER_WriteData(&data_entry, 1);

    EPAPER_WriteCMD(0x44); // Set RAM X address start/end
    uint8_t ram_x[] = {0x00, 0x0F}; // X start = 0x00, X end = 0x0F (0~15, for 128 pixels: 16*8 bits)
    EPAPER_WriteData(ram_x, 2);

    EPAPER_WriteCMD(0x45); // Set RAM Y address start/end
    uint8_t ram_y[] = {0x00, 0x00, 0x27, 0x01}; // Y start = 0x0000, Y end = 0x0127 (0~295, for 296 pixels)
    EPAPER_WriteData(ram_y, 4);

    EPAPER_WriteCMD(0x3C); // Border Waveform Control
    uint8_t border_waveform_forVBD[] = {0xC0}; //  Set border waveform for VBD: VBD as HIZ
    EPAPER_WriteData(border_waveform_forVBD, 1);

}

void EPAPER_LoadWaveformLUT(void) {
    
    EPAPER_WriteCMD(0x18); // Select the Temperature Sensor Control
    uint8_t temp_sensor_control[] = {0x80}; // Set temperature sensor control to default
    EPAPER_WriteData(temp_sensor_control, 1);

    EPAPER_WriteCMD(0x22);
    uint8_t operating_sequence[] = {0xB1}; // Set the operating sequence for the display
    EPAPER_WriteData(operating_sequence, 1); // Enable LUT load
    EPAPER_WriteCMD(0x20); // Master Activation
    EPAPER_WaitUntilIdle();

}

esp_err_t EPAPER_Init(void) {

    PIN_SetDirection(EPAPER_DC_PIN, OUTPUT);
    PIN_SetDirection(EPAPER_RST_PIN, OUTPUT);

    PIN_SetDirection(EPAPER_DC_PIN, INPUT);
    
    gpio_set_direction(EPAPER_BUSY_PIN, GPIO_MODE_INPUT);
    gpio_set_level(EPAPER_DC_PIN, 1);      // Data mode
    EPAPER_SetInitConfig();
    EPAPER_SendInitCode();
    EPAPER_LoadWaveformLUT();

    return ESP_OK;
}

esp_err_t EPAPER_Clear(void) {
    uint8_t buffer[EPAPER_BUFFER_SIZE];
    memset(buffer, 0xFF, EPAPER_BUFFER_SIZE);
    return EPAPER_DisplayFramebuffer(buffer);
}

esp_err_t EPAPER_DisplayFramebuffer(const uint8_t *framebuffer) {
    EPAPER_WriteCMD(0x4E); // Set RAM X address counter
    uint8_t x_address[] = {0x00}; // Set X address to 0
    EPAPER_WriteData(x_address, 1);

    EPAPER_WriteCMD(0x4F); // Set RAM Y address counter
    uint8_t y_address[] = {0x00, 0x00}; // Set X address to 0
    EPAPER_WriteData(y_address, 2);

    EPAPER_WriteCMD(0x24); // Write RAM
    EPAPER_WriteData(framebuffer, EPAPER_BUFFER_SIZE);

    EPAPER_WriteCMD(0x0C); // Booster Soft Start
    uint8_t softstart_param[] = {0xAE, 0xC7, 0xC3}; // Set the soft start parameters
    EPAPER_WriteData(softstart_param, 3);

    EPAPER_WriteCMD(0x22); // Display Update Control
    uint8_t update_ctrl[] = {0xC7}; // Set the soft start parameters
    EPAPER_WriteData(update_ctrl, 1);
    EPAPER_WriteCMD(0x20); // Master Activation
    EPAPER_WaitUntilIdle();

    return ESP_OK;
}

esp_err_t EPAPER_Sleep(void) {
    EPAPER_WriteCMD(0x10); // Enter deep sleep
    uint8_t deep_sleep_cmd[] = {0x01}; // Deep sleep command
    EPAPER_WriteData(deep_sleep_cmd, 1);
    return ESP_OK;
}