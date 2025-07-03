/*
 * circular_buffer.c
 *
 *  Created on: 27 gen 2025
 *      Author: William
 */
#include "circular_buffer.h"
#include "queue"

std::queue<DATATYPE> q;

void cb_enqueue(DATATYPE element)
{
	q.push(element);
	return q.size();
}

DATATYPE cb_dequeue()
{
	DATATYPE front = q.front();
	q.pop();
	return front;
}

uint32_t cb_size()
{
	return q.size();
}

#if 0
void cb_init(circular_buffer_t *cb)
{
	CB_LOG("%s\n", __FUNCTION__);
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

bool cb_is_full(circular_buffer_t *cb)
{
	CB_LOG("%s\n", __FUNCTION__);
    return cb->count == BUFFER_SIZE;
}

bool cb_is_empty(circular_buffer_t *cb)
{
	CB_LOG("%s\n", __FUNCTION__);
    return cb->count == 0;
}

void cb_enqueue(circular_buffer_t *cb, int32_t item)
{
	CB_LOG("%s\n", __FUNCTION__);
    if (cb_is_full(cb))
    {
    	CB_LOG("Buffer pieno\n");
        return;
    }
    cb->buffer[cb->head] = item;
    cb->head = (cb->head + 1) % BUFFER_SIZE;
    cb->count++;
}

cb_error_t cb_dequeue(circular_buffer_t *cb, int32_t *item)
{
	CB_LOG("%s\n", __FUNCTION__);
    if (cb_is_full(cb))
    {
    	CB_LOG("Buffer vuoto\n");
        return -1;
    }
    *item = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    cb->count--;
    return 0;
}
#endif
