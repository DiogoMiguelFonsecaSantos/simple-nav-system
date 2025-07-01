/*
 * ring_buffer.h
 *
 *  Created on: 23/06/2025
 *      Author: Diogo
 */

#ifndef COMPONENTS_MYDRIVERS_INC_RING_BUFFER_H_
#define COMPONENTS_MYDRIVERS_INC_RING_BUFFER_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    RINGBUFFER_OK = 0,
    RINGBUFFER_ERROR,
    RINGBUFFER_FULL,
    RINGBUFFER_EMPTY
} RINGBUFFER_Status_t;

typedef struct {
    void *data;
    size_t size;
    size_t element_size;
    size_t head;
    size_t tail;
} ring_buffer_t;

RINGBUFFER_Status_t RINGBUFFER_Init(ring_buffer_t *buffer, void *data, size_t size, size_t element_size);
bool RINGBUFFER_IsEmpty(ring_buffer_t *buffer);
bool RINGBUFFER_IsFull(ring_buffer_t *buffer);
RINGBUFFER_Status_t RINGBUFFER_Put(ring_buffer_t *buffer, const void *data);
RINGBUFFER_Status_t RINGBUFFER_Get(ring_buffer_t *buffer, void *data);
RINGBUFFER_Status_t RINGBUFFER_Peek(ring_buffer_t *buffer, void *data);
RINGBUFFER_Status_t RINGBUFFER_SetData(ring_buffer_t *buffer, void *data, size_t num_elements);
RINGBUFFER_Status_t RINGBUFFER_GetString(ring_buffer_t *buffer, char *data, size_t size);
int RINGBUFFER_FindString(ring_buffer_t *buffer, const char *str, size_t str_len);

#endif /* COMPONENTS_MYDRIVERS_INC_RING_BUFFER_H_ */
