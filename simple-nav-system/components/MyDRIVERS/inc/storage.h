/*
 * storage.h
 *
 *  Created on: Jul 2, 2025
 *      Author: diogo
 */

#ifndef COMPONENTS_MYDRIVERS_INC_STORAGE_H_
#define COMPONENTS_MYDRIVERS_INC_STORAGE_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    char timestamp[32]; // YYYY-MM-DD HH:MM:SS + null terminator, extra safety
    double latitude;
    double longitude;
    double altitude;
    double cog;
} sample_t;

// Initialize storage (mount SPIFFS and prepare ring buffer file)
bool gps_storage_init(void);

// Append a sample (overwrites oldest if full)
bool gps_storage_append(const sample_t *sample);

// Read up to max_samples, oldest first (returns number read)
size_t gps_storage_read_last(sample_t *buffer, size_t max_samples);

// Clear all samples
bool gps_storage_clear(void);

#endif /* COMPONENTS_MYDRIVERS_INC_STORAGE_H_ */
