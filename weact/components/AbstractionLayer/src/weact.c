#include "weact.h"
#include "spi_protocol.h"
#include "driver/gpio.h"
#include "freertos/task.h"
#include <string.h>

// Example resolution for 2.9" e-paper
#define EPAPER_WIDTH  296
#define EPAPER_HEIGHT 128
#define EPAPER_BUFFER_SIZE ((EPAPER_WIDTH * EPAPER_HEIGHT) / 8)

static const char *TAG = "weact";

// Initialize GPIOs for e-paper
esp_err_t WEACT_Epaper_Init(void) {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << EPAPER_PIN_DC) | (1ULL << EPAPER_PIN_RST),
        .mode = GPIO_MODE_OUTPUT,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&io_conf));

    gpio_config_t input_conf = {
        .pin_bit_mask = (1ULL << EPAPER_PIN_BUSY),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&input_conf));

    WEACT_Epaper_Reset();
    return ESP_OK;
}

void WEACT_Epaper_Reset(void) {
    gpio_set_level(EPAPER_PIN_RST, 0);
    vTaskDelay(pdMS_TO_TICKS(200));
    gpio_set_level(EPAPER_PIN_RST, 1);
    vTaskDelay(pdMS_TO_TICKS(200));
}

void WEACT_Epaper_WaitUntilIdle(void) {
    while (gpio_get_level(EPAPER_PIN_BUSY) == 1) {
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

// Send command to the e-paper
esp_err_t WEACT_Epaper_SendCommand(uint8_t cmd) {
    gpio_set_level(EPAPER_PIN_DC, 0);  // Command mode
    esp_err_t ret = SPI_PROTOCOLTransmit_EPAPER_Command(cmd);
    gpio_set_level(EPAPER_PIN_DC, 1);  // Data mode
    return ret;
}

// Send data to the e-paper
esp_err_t WEACT_Epaper_SendData(const uint8_t *data, size_t length) {
    gpio_set_level(EPAPER_PIN_DC, 1);  // Data mode
    return SPI_PROTOCOLTransmit_EPAPER_Data(data, length);
}

esp_err_t WEACT_Epaper_PaintBlack(void) {
    static uint8_t black_buf[EPAPER_BUFFER_SIZE];
    memset(black_buf, 0x00, sizeof(black_buf));  // Fill buffer with black

    WEACT_Epaper_SendCommand(0x10); // Data Start Transmission 1
    WEACT_Epaper_SendData(black_buf, sizeof(black_buf));

    WEACT_Epaper_SendCommand(0x12); // Display Refresh
    WEACT_Epaper_WaitUntilIdle();

    return ESP_OK;
}

esp_err_t WEACT_Epaper_PaintWhite(void) {
    static uint8_t white_buf[EPAPER_BUFFER_SIZE];
    memset(white_buf, 0xFF, sizeof(white_buf));  // Fill buffer with white

    WEACT_Epaper_SendCommand(0x10); // Data Start Transmission 1
    WEACT_Epaper_SendData(white_buf, sizeof(white_buf));

    WEACT_Epaper_SendCommand(0x12); // Display Refresh
    WEACT_Epaper_WaitUntilIdle();

    return ESP_OK;
}