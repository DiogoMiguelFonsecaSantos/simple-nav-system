/*
 * flash_store.c
 *
 *  Created on: 23/06/2025
 *      Author: Diogo
 */

#include "flash_store.h"
#include "nvs_flash.h"
#include "nvs.h"

#define NVS_NAMESPACE "gpsdata"
#define NVS_KEY_HISTORY "gps_history_blob"

bool flash_store_save_gps_history(const gps_history_blob_t *blob) {
    nvs_handle_t handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &handle);
    if (err != ESP_OK) return false;
    err = nvs_set_blob(handle, NVS_KEY_HISTORY, blob, sizeof(gps_history_blob_t));
    err |= nvs_commit(handle);
    nvs_close(handle);
    return err == ESP_OK;
}

bool flash_store_load_gps_history(gps_history_blob_t *blob) {
    nvs_handle_t handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READONLY, &handle);
    if (err != ESP_OK) return false;
    size_t required_size = sizeof(gps_history_blob_t);
    err = nvs_get_blob(handle, NVS_KEY_HISTORY, blob, &required_size);
    nvs_close(handle);
    return err == ESP_OK;
}