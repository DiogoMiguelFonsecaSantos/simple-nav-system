/*
 * i2c_protocol.h
 *
 *  Created on: Jun 9, 2025
 *      Author: diogo
 */

#ifndef COMPONENTS_MYHAL_INC_I2C_PROTOCOL_H_
#define COMPONENTS_MYHAL_INC_I2C_PROTOCOL_H_

#include "esp_err.h"
#include "driver/i2c.h"

#define I2C_MASTER_NUM         I2C_NUM_0        // I2C port number
#define I2C_MASTER_SDA_IO      13               // SDA pin
#define I2C_MASTER_SCL_IO      15               // SCL pin
#define I2C_MASTER_FREQ_HZ     100000           // I2C frequency
#define I2C_MASTER_TX_BUF_DISABLE 0             // No TX buffer
#define I2C_MASTER_RX_BUF_DISABLE 0             // No RX buffer

/**
 * @brief Initialize the I2C master interface
 *
 * @return esp_err_t
 */
esp_err_t i2c_protocol_init(void);

/**
 * @brief Write a single byte to a slave device
 *
 * @param device_address I2C address of the slave
 * @param data Byte to write
 * @return esp_err_t
 */
esp_err_t i2c_protocol_write_byte(uint8_t device_address, uint8_t data);

/**
 * @brief Write multiple bytes to a slave device
 *
 * @param device_address I2C address of the slave
 * @param data Pointer to the data buffer
 * @param length Number of bytes to send
 * @return esp_err_t
 */
esp_err_t i2c_protocol_write_bytes(uint8_t device_address, const uint8_t *data, size_t length);

#endif /* COMPONENTS_MYHAL_INC_I2C_PROTOCOL_H_ */
