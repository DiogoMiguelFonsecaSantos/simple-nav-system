/*
 * uart.c
 *
 *  Created on: Jun 3, 2025
 *      Author: diogo
 */

#include "uart.h"
#include "driver/uart.h"  // Usamos a API de baixo nível do ESP-IDF como base mínima
#include "esp_log.h"

#define TAG "MY_HAL_UART"

void my_uart_init(my_uart_port_t uart_num, const my_uart_config_t *cfg) {
	esp_err_t err;
    uart_config_t uart_cfg = {
        .baud_rate = cfg->baud_rate,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };
	
    err = uart_driver_install(uart_num, 2048, 0, 0, NULL, 0);
	if (err != ESP_OK) {
	    ESP_LOGE("UART", "Erro ao instalar driver: %s", esp_err_to_name(err));
	}

	err = uart_param_config(uart_num, &uart_cfg);
	if (err != ESP_OK) {
	    ESP_LOGE("UART", "Erro na config UART: %s", esp_err_to_name(err));
	}

	err = uart_set_pin(uart_num, cfg->tx_pin, cfg->rx_pin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
	if (err != ESP_OK) {
	    ESP_LOGE("UART", "Erro nos pinos: %s", esp_err_to_name(err));
	}
	
}

int my_uart_read_bytes(my_uart_port_t uart_num, uint8_t *data, size_t length, TickType_t ticks_to_wait) {
    return uart_read_bytes(uart_num, data, length, ticks_to_wait);
}





