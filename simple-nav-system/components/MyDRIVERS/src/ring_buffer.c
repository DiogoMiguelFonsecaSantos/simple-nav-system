/*
 * ring_buffer.c
 *
 *  Created on: 23/06/2025
 *      Author: Diogo
 */

#include "ring_buffer.h"
#include <string.h>
#include <stdint.h>

RINGBUFFER_Status_t RINGBUFFER_Init(ring_buffer_t *buffer, void *data, size_t size, size_t element_size) {
    if (buffer == NULL || data == NULL || size == 0 || element_size == 0) {
        return RINGBUFFER_ERROR;
    }
    buffer->data = data;
    buffer->size = size;
    buffer->element_size = element_size;
    buffer->head = 0;
    buffer->tail = 0;
    return RINGBUFFER_OK;
}

bool RINGBUFFER_IsEmpty(ring_buffer_t *buffer) {
    if (buffer == NULL) {
        return false;
    }
    return buffer->head == buffer->tail;
}

bool RINGBUFFER_IsFull(ring_buffer_t *buffer) {
    if (buffer == NULL) {
        return false;
    }
    size_t next_head = (buffer->head + 1) % buffer->size;
    return next_head == buffer->tail;
}

RINGBUFFER_Status_t RINGBUFFER_Put(ring_buffer_t *buffer, const void *data) {
    if (buffer == NULL || data == NULL) {
        return RINGBUFFER_ERROR;
    } else if (RINGBUFFER_IsFull(buffer)) {
        return RINGBUFFER_FULL;
    }
    memcpy((uint8_t*)buffer->data + buffer->head * buffer->element_size, data, buffer->element_size);
    buffer->head = (buffer->head + 1) % buffer->size;
    return RINGBUFFER_OK;
}

RINGBUFFER_Status_t RINGBUFFER_Get(ring_buffer_t *buffer, void *data) {
    if (buffer == NULL || data == NULL) {
        return RINGBUFFER_ERROR;
    } else if (RINGBUFFER_IsEmpty(buffer)) {
        return RINGBUFFER_EMPTY;
    }
    memcpy(data, (uint8_t*)buffer->data + buffer->tail * buffer->element_size, buffer->element_size);
    buffer->tail = (buffer->tail + 1) % buffer->size;
    return RINGBUFFER_OK;
}

RINGBUFFER_Status_t RINGBUFFER_Peek(ring_buffer_t *buffer, void *data) {
    if (buffer == NULL || data == NULL) {
        return RINGBUFFER_ERROR;
    } else if (RINGBUFFER_IsEmpty(buffer)) {
        return RINGBUFFER_EMPTY;
    }
    memcpy(data, (uint8_t*)buffer->data + buffer->tail * buffer->element_size, buffer->element_size);
    return RINGBUFFER_OK;
}

RINGBUFFER_Status_t RINGBUFFER_SetData(ring_buffer_t *buffer, void *data, size_t num_elements) {
    if (buffer == NULL || data == NULL || num_elements == 0) {
        return RINGBUFFER_ERROR;
    }
    if (num_elements > buffer->size) {
        return RINGBUFFER_ERROR;
    }
    memcpy(buffer->data, data, num_elements * buffer->element_size);
    buffer->head = num_elements;
    buffer->tail = 0;
    return RINGBUFFER_OK;
}

RINGBUFFER_Status_t RINGBUFFER_GetString(ring_buffer_t *buffer, char *data, size_t size) {
    if (buffer == NULL || data == NULL || size == 0) {
        return RINGBUFFER_ERROR;
    }
    size_t length = (buffer->head >= buffer->tail)
        ? (buffer->head - buffer->tail) * buffer->element_size
        : (buffer->size - buffer->tail + buffer->head) * buffer->element_size;
    if (length > size - 1) {
        length = size - 1;
    }
    size_t start = buffer->tail * buffer->element_size;
    if (start + length <= buffer->size * buffer->element_size) {
        memcpy(data, (uint8_t*)buffer->data + start, length);
    } else {
        size_t first_part = buffer->size * buffer->element_size - start;
        memcpy(data, (uint8_t*)buffer->data + start, first_part);
        memcpy(data + first_part, buffer->data, length - first_part);
    }
    data[length] = '\0';
    return RINGBUFFER_OK;
}

int RINGBUFFER_FindString(ring_buffer_t *buffer, const char *str, size_t str_len) {
    if (!buffer || !str || str_len == 0) {
        return -1;
    }
    size_t buffer_bytes = (buffer->head >= buffer->tail)
        ? (buffer->head - buffer->tail) * buffer->element_size
        : (buffer->size - buffer->tail + buffer->head) * buffer->element_size;
    if (buffer_bytes < str_len) {
        return -1;
    }
    uint8_t *data = (uint8_t *)buffer->data;
    for (size_t byte_offset = 0; byte_offset <= buffer_bytes - str_len; ++byte_offset) {
        bool match = true;
        for (size_t i = 0; i < str_len; ++i) {
            size_t absolute_byte_index =
                ((buffer->tail * buffer->element_size) + byte_offset + i) %
                (buffer->size * buffer->element_size);
            uint8_t buffer_byte = data[absolute_byte_index];
            if (buffer_byte != (uint8_t)str[i]) {
                match = false;
                break;
            }
        }
        if (match) {
            return (int)byte_offset;
        }
    }
    return -1;
}


