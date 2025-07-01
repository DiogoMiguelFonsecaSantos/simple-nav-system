/*
 * i2c_protocol.c
 *
 *  Created on: Jun 9, 2025
 *      Author: diogo
 */

#include "i2c_protocol.h"
#include "esp_log.h"

#define TAG "I2C_PROTOCOL"

esp_err_t i2c_protocol_init(void)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    esp_err_t err;

    err = i2c_param_config(I2C_MASTER_NUM, &conf);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure I2C: %s", esp_err_to_name(err));
        return err;
    }

    err = i2c_driver_install(I2C_MASTER_NUM, conf.mode,
                             I2C_MASTER_RX_BUF_DISABLE,
                             I2C_MASTER_TX_BUF_DISABLE, 0);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to install I2C driver: %s", esp_err_to_name(err));
    }

    return err;
}

esp_err_t i2c_protocol_write_byte(uint8_t device_address, uint8_t data)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    esp_err_t err;

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (device_address << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, data, true);
    i2c_master_stop(cmd);

    err = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, pdMS_TO_TICKS(1000));
    i2c_cmd_link_delete(cmd);

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "I2C write failed: %s", esp_err_to_name(err));
    }

    return err;
}

esp_err_t i2c_protocol_write_bytes(uint8_t device_address, const uint8_t *data, size_t length)
{
    if (data == NULL || length == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    esp_err_t err;

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (device_address << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write(cmd, (uint8_t *)data, length, true);
    i2c_master_stop(cmd);

    err = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, pdMS_TO_TICKS(1000));
    i2c_cmd_link_delete(cmd);

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "I2C multi-byte write failed: %s", esp_err_to_name(err));
    }

    return err;
}



