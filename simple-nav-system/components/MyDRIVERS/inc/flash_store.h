/*
 * flash_store.h
 *
 *  Created on: 23/06/2025
 *      Author: Diogo
 */

#ifndef COMPONENTS_MYDRIVERS_INC_FLASH_STORE_H_
#define COMPONENTS_MYDRIVERS_INC_FLASH_STORE_H_

#include <stdbool.h>
#include <stddef.h>
#include "gps.h"

#define GPS_HISTORY_SIZE 1000

typedef struct {
    double latitude;
    double longitude;
    double altitude;
} gps_coord_t;

// Metadata struct for persistent ring buffer
typedef struct {
    size_t head;
    size_t tail;
    size_t count;
    gps_coord_t data[GPS_HISTORY_SIZE];
} gps_history_blob_t;

bool flash_store_save_gps_history(const gps_history_blob_t *blob);
bool flash_store_load_gps_history(gps_history_blob_t *blob);

#endif /* COMPONENTS_MYDRIVERS_INC_FLASH_STORE_H_ */
