/*
 * uart.h
 *
 *  Created on: Jun 3, 2025
 *      Author: diogo
 */

#ifndef COMPONENTS_MYHAL_INC_UART_H_
#define COMPONENTS_MYHAL_INC_UART_H_

#include "driver/uart.h"

typedef enum {
    MY_UART_NUM_1 = UART_NUM_1,
    MY_UART_NUM_2 = UART_NUM_2,
    // adiciona outros se precisares
} my_uart_port_t;

typedef struct {
    int tx_pin;
    int rx_pin;
    int baud_rate;
} my_uart_config_t;

void my_uart_init(my_uart_port_t uart_num, const my_uart_config_t *cfg);

int my_uart_read_bytes(my_uart_port_t uart_num, uint8_t *data, size_t length, TickType_t ticks_to_wait);

#endif /* COMPONENTS_MYHAL_INC_UART_H_ */
