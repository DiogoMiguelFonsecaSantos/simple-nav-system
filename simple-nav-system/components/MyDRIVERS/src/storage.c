/*
 * storage.c
 *
 *  Created on: Jul 2, 2025
 *      Author: diogo
 */

#include "storage.h"
#include "esp_spiffs.h"
#include <stdio.h>
#include <string.h>

#define GPS_RINGBUF_MAX 1000

#define GPS_RINGBUF_PATH "/spiffs/gps_ringbuf.bin"

typedef struct {
    uint32_t head;
    uint32_t count;
} gps_ringbuf_meta_t;

static gps_ringbuf_meta_t meta = {0, 0};

static bool gps_ringbuf_load_meta(FILE *f) {
    rewind(f);
    return fread(&meta, sizeof(meta), 1, f) == 1;
}

static bool gps_ringbuf_save_meta(FILE *f) {
    rewind(f);
    return fwrite(&meta, sizeof(meta), 1, f) == 1;
}

bool gps_storage_init(void) {
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs",
        .partition_label = NULL,
        .max_files = 5,
        .format_if_mount_failed = true
    };
    if (esp_vfs_spiffs_register(&conf) != ESP_OK)
        return false;

    FILE *f = fopen(GPS_RINGBUF_PATH, "rb+");
    if (!f) {
        // Create new file with empty meta and zeroed data
        f = fopen(GPS_RINGBUF_PATH, "wb+");
        if (!f) return false;
        meta.head = 0; meta.count = 0;
        fwrite(&meta, sizeof(meta), 1, f);
        sample_t zero = {0};
        for (size_t i = 0; i < GPS_RINGBUF_MAX; ++i)
            fwrite(&zero, sizeof(zero), 1, f);
        fflush(f);
    } else {
        gps_ringbuf_load_meta(f);
    }
    fclose(f);
    return true;
}

bool gps_storage_append(const sample_t *sample) {
    FILE *f = fopen(GPS_RINGBUF_PATH, "rb+");
    if (!f) return false;
    gps_ringbuf_load_meta(f);

    // Write sample at head position
    size_t pos = sizeof(meta) + (meta.head % GPS_RINGBUF_MAX) * sizeof(sample_t);
    fseek(f, pos, SEEK_SET);
    fwrite(sample, sizeof(sample_t), 1, f);

    // Update meta
    meta.head = (meta.head + 1) % GPS_RINGBUF_MAX;
    if (meta.count < GPS_RINGBUF_MAX) meta.count++;
    gps_ringbuf_save_meta(f);

    fclose(f);
    return true;
}

size_t gps_storage_read_last(sample_t *buffer, size_t max_samples) {
    FILE *f = fopen(GPS_RINGBUF_PATH, "rb");
    if (!f) return 0;
    gps_ringbuf_load_meta(f);

    size_t n = (meta.count < max_samples) ? meta.count : max_samples;
    size_t start = (meta.head + GPS_RINGBUF_MAX - n) % GPS_RINGBUF_MAX;

    for (size_t i = 0; i < n; ++i) {
        size_t idx = (start + i) % GPS_RINGBUF_MAX;
        size_t pos = sizeof(meta) + idx * sizeof(sample_t);
        fseek(f, pos, SEEK_SET);
        fread(&buffer[i], sizeof(sample_t), 1, f);
    }
    fclose(f);
    return n;
}

bool gps_storage_clear(void) {
    FILE *f = fopen(GPS_RINGBUF_PATH, "rb+");
    if (!f) return false;
    meta.head = 0; meta.count = 0;
    gps_ringbuf_save_meta(f);
    fclose(f);
    return true;
}