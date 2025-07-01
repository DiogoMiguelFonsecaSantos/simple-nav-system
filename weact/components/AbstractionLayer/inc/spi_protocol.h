/*
 * spi_protocol.h
 *
 *  Created on: 04/04/2025
 *      Author: Diogo
 */

// Pin definitions (match your hardware layout)
// Hardware wiring
// Purple = BUSY - GPIO34
// Orange = RST  - GPIO22
// White  = D/C  - GPIO25
// Blue   = CS   - GPIO33 
// Green  = SCL  - GPIO18 (SPI CLK)
// Yellow = SDA  - GPIO23 (SPI MOSI)
// Black  = GND
// Red    = VCC (3.3V)

#ifndef COMPONENTS_ABSTRACTIONLAYER_INC_SPI_PROTOCOL_H_
#define COMPONENTS_ABSTRACTIONLAYER_INC_SPI_PROTOCOL_H_

#include "driver/gpio.h"
#include "driver/spi_master.h"

#define MY_SPI_HOST VSPI_HOST
#define SPI_CLOCK_SPEED_HZ 1000000  // 1 MHz
#define SPI_MODE 0
#define SPI_QUEUE_SIZE 1

// SPI pin assignments
#define PIN_NUM_MISO       GPIO_NUM_19  // Not used by e-paper
#define PIN_NUM_MOSI       GPIO_NUM_23
#define PIN_NUM_CLK        GPIO_NUM_18
#define PIN_NUM_CS_MPU     GPIO_NUM_12  // Change if needed
#define PIN_NUM_CS_EPAPER  GPIO_NUM_33  // ✅ Final safe pin

esp_err_t SPI_PROTOCOLInit(void);
esp_err_t SPI_PROTOCOLTransmit_MPU(uint8_t *tx_data, uint8_t *rx_data, size_t length);
esp_err_t SPI_PROTOCOLTransmit_EPAPER_Command(uint8_t cmd);
esp_err_t SPI_PROTOCOLTransmit_EPAPER_Data(const uint8_t *data, size_t length);

#endif /* COMPONENTS_ABSTRACTIONLAYER_INC_SPI_PROTOCOL_H_ */