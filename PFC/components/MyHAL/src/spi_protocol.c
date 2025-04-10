#include "spi_protocol.h"
#include "esp_log.h"

static const char *TAG = "SPI_PROTOCOL";

// SPI Bus and Device Configurations
static spi_device_handle_t spi_handle;

static spi_bus_config_t bus_config = {
    .miso_io_num = PIN_NUM_MISO,
    .mosi_io_num = PIN_NUM_MOSI,
    .sclk_io_num = PIN_NUM_CLK,
    .quadwp_io_num = -1, // Not used
    .quadhd_io_num = -1, // Not used
    .max_transfer_sz = 4096,
};

static spi_device_interface_config_t device_config = {
    .clock_speed_hz = SPI_CLOCK_SPEED_HZ,
    .mode = SPI_MODE,
    .spics_io_num = PIN_NUM_CS,
    .queue_size = SPI_QUEUE_SIZE,
};

esp_err_t SPI_PROTOCOLInit(void) {
    // Initialize SPI bus
    esp_err_t ret = spi_bus_initialize(MY_SPI_HOST, &bus_config, SPI_DMA_CHAN);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize SPI bus: %d", ret);
        return ret;
    }

    // Add SPI device
    ret = spi_bus_add_device(MY_SPI_HOST, &device_config, &spi_handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to add SPI device: %d", ret);
    }

    return ret;
}

esp_err_t SPI_PROTOCOLTransmit(const uint8_t *tx_data, uint8_t *rx_data, size_t length) {
    spi_transaction_t transaction = {
        .length = length * 8, // Length in bits
        .tx_buffer = tx_data,
        .rx_buffer = rx_data,
    };

    esp_err_t ret = spi_device_transmit(spi_handle, &transaction);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "SPI transmit failed: %d", ret);
    }

    return ret;
}