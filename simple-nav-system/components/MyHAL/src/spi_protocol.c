/*
 * spi_protocol.c
 *
 *  Created on: 04/04/2025
 *      Author: Diogo
 */

 #include "spi_protocol.h"

 static spi_device_handle_t spi_handle;
 
 esp_err_t SPI_PROTOCOLInit(void) {

    spi_bus_config_t bus_config = {
        .miso_io_num = PIN_NUM_MISO, // Master In Slave Out GPIO19
        .mosi_io_num = PIN_NUM_MOSI, // Master Out Slave In GPIO23
        .sclk_io_num = PIN_NUM_CLK,  // Serial Clock GPIO18
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4096
    };
 
    spi_device_interface_config_t dev_config = {
        .clock_speed_hz = SPI_CLOCK_SPEED_HZ,
        .mode = SPI_MODE,
        .spics_io_num = PIN_NUM_CS,
        .queue_size = SPI_QUEUE_SIZE,
    };
 
    // Initialize the SPI bus
    esp_err_t ret = spi_bus_initialize(MY_SPI_HOST, &bus_config, SPI_DMA_CH_AUTO);
    if (ret != ESP_OK) return ret;

    // Attach the device to the SPI bus
    ret = spi_bus_add_device(MY_SPI_HOST, &dev_config, &spi_handle);
    return ret;
 }
 
 esp_err_t SPI_PROTOCOLTransmit(uint8_t *tx_data, uint8_t *rx_data, size_t length) {
     
    spi_transaction_t transaction = {
        .length = length * 8, // Length in bits
        .tx_buffer = tx_data,
        .rx_buffer = rx_data,
    };

    return spi_device_transmit(spi_handle, &transaction);
 }