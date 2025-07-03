/*
 * circular_buffer.h
 *
 *  Created on: 27 gen 2025
 *      Author: William
 */

#ifndef MW_CIRCULAR_BUFFER_CIRCULAR_BUFFER_H_
#define MW_CIRCULAR_BUFFER_CIRCULAR_BUFFER_H_

#include <stdint.h>
#include <stdbool.h>
#include <iso646.h>

#define DATATYPE uint32_t

void cb_enqueue(DATATYPE element);
DATATYPE cb_dequeue();
uint32_t cb_size();

#if 0
#define BUFFER_SIZE 5

#define CB_LOG_ENABLED
#ifdef CB_LOG_ENABLED
#define CB_LOG(...) printf(__VA_ARGS__, "")
#else
#define CB_LOG(...)
#endif

typedef uint32_t cb_error_t;

typedef struct
{
    int buffer[BUFFER_SIZE];
    int head;
    int tail;
    int count;
} circular_buffer_t;

void cb_init(circular_buffer_t *cb);
bool cb_is_full(circular_buffer_t *cb);
bool cb_is_empty(circular_buffer_t *cb);
void cb_enqueue(circular_buffer_t *cb, int32_t item);
cb_error_t cb_dequeue(circular_buffer_t *cb, int32_t *item);
#endif

#endif /* MW_CIRCULAR_BUFFER_CIRCULAR_BUFFER_H_ */
