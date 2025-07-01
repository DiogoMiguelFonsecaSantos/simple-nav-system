/*
 * spi_protocol.h
 *
 *  Created on: 04/04/2025
 *      Author: Diogo
 */

#ifndef COMPONENTS_MYHAL_INC_SPI_PROTOCOL_H_
#define COMPONENTS_MYHAL_INC_SPI_PROTOCOL_H_

#include "driver/gpio.h"
#include "driver/spi_master.h"

// spi_protocol.h
#define MY_SPI_HOST VSPI_HOST
#define SPI_CLOCK_SPEED_HZ 1000000 // 1 MHz
#define SPI_MODE 0				   // SPI Mode 0 (CPOL = 0, CPHA = 0)
#define SPI_QUEUE_SIZE 1

// Pin Definitions
#define PIN_NUM_MISO GPIO_NUM_19
#define PIN_NUM_MOSI GPIO_NUM_23
#define PIN_NUM_CLK GPIO_NUM_18
#define PIN_NUM_CS_MPU GPIO_NUM_5
#define PIN_NUM_CS_EPAPER GPIO_NUM_12

// Function Prototypes
esp_err_t SPI_PROTOCOLInit(void);
esp_err_t SPI_PROTOCOLTransmit_MPU(uint8_t *tx_data, uint8_t *rx_data,
								   size_t length);
esp_err_t SPI_PROTOCOLTransmit_EPAPER_Command(uint8_t cmd);
esp_err_t SPI_PROTOCOLTransmit_EPAPER_Data(const uint8_t *data, size_t length);

#endif /* COMPONENTS_MYHAL_INC_SPI_PROTOCOL_H_ */