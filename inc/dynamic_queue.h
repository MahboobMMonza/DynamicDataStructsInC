#include <stdlib.h>
#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H

typedef struct dynq DynamicQueue;

extern DynamicQueue *dynamic_queue_init(size_t buf_size, const size_t data_size);
extern int dynamic_queue_empty(DynamicQueue *q);
extern int dynamic_queue_enqueue(DynamicQueue *q, void *new_data);
extern int dynamic_queue_dequeue(DynamicQueue *q);
extern size_t dynamic_queue_capacity(DynamicQueue *q);
extern size_t dynamic_queue_length(DynamicQueue *q);
extern size_t dynamic_queue_data_size(DynamicQueue *q);
extern void *dynamic_queue_peek(DynamicQueue *q);
extern void dynamic_queue_clear(DynamicQueue *q);
extern void dynamic_queue_destroy(DynamicQueue **q);

#endif // DYNAMIC_QUEUE_H
