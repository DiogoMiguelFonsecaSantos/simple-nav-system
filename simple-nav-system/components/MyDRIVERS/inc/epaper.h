/*
 * epaper.h
 *
 *  Created on: May 18, 2025
 *      Author: diogo
 */

#ifndef COMPONENTS_MYDRIVERS_INC_EPAPER_H_
#define COMPONENTS_MYDRIVERS_INC_EPAPER_H_

#include "spi_protocol.h"
#include "driver/gpio.h"
#include "freertos/task.h"
#include "esp_err.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "C:\SNS\PFC\simple-nav-system\components\MyFONTS\inc\epaper_fonts.h" 
#include "C:\SNS\PFC\simple-nav-system\components\MyFONTS\inc\epaper-29-ws.h"
#include "C:\SNS\PFC\simple-nav-system\components\MyFONTS\inc\u8g2.h"
#include "C:\SNS\PFC\simple-nav-system\components\MyFONTS\inc\u8x8.h"

// Pin definitions (match your hardware layout)
// Hardware wiring
// Purple = BUSY - GPIO15
// Orange = RST  - GPIO22
// White  = D/C  - GPIO17
// Blue   = CS   - GPIO16 (controlled by spi_protocol.c)
// Green  = SCL  - GPIO18 (SPI CLK)
// Yellow = SDA  - GPIO23 (SPI MOSI)
// Black  = GND
// Red    = VCC (3.3V)

#define EPAPER_BUSY_PIN   15
#define EPAPER_RST_PIN    22
#define EPAPER_DC_PIN     17
#define EPAPER_CS_PIN     16

#define EPAPER_WIDTH  296
#define EPAPER_HEIGHT 128
#define EPAPER_BUFFER_SIZE (EPAPER_WIDTH * EPAPER_HEIGHT / 8)

// bool initDisplayDone;

void EPAPER_WriteCMD(uint8_t cmd);
void EPAPER_WriteData(const uint8_t *data, size_t len);
void EPAPER_WaitUntilIdle(void);
void EPAPER_HardReset(void);

esp_err_t EPAPER_ClearBW(void);
void EPAPER_SetInitConfig(void);
void EPAPER_SendInitCode(void);
void EPAPER_LoadWaveformLUT(void);
esp_err_t EPAPER_Init(void);
esp_err_t EPAPER_Clear(void);
esp_err_t EPAPER_DisplayFramebuffer(const uint8_t *framebuffer);
esp_err_t EPAPER_Sleep(void);

#endif /* COMPONENTS_MYDRIVERS_INC_EPAPER_H_ */
