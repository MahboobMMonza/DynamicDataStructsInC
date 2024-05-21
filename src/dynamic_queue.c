#include "dynamic_queue.h"
#include "dynamic_deque.h"
#include <stdlib.h>

DynamicQueue dynamic_queue_init(size_t buf_size, const size_t data_size) {
    DynamicDeque ddq = dynamic_deque_init(buf_size, data_size);
    DynamicQueue q = *(DynamicQueue *)&ddq;
    return q;
}

int dynamic_queue_empty(DynamicQueue *q) { return dynamic_deque_empty((DynamicDeque *)q); }

int dynamic_queue_enqueue(DynamicQueue *q, void *new_data) { return dynamic_deque_push_back((DynamicDeque *)q, new_data); }

int dynamic_queue_dequeue(DynamicQueue *q) { return dynamic_deque_pop_front((DynamicDeque *)q); }

size_t dynamic_queue_capacity(DynamicQueue *q) { return dynamic_deque_capacity((DynamicDeque *)q); }

size_t dynamic_queue_length(DynamicQueue *q) { return dynamic_deque_length((DynamicDeque *)q); }

size_t dynamic_queue_data_size(DynamicQueue *q) { return dynamic_deque_data_size((DynamicDeque *)q); }

void *dynamic_queue_peek(DynamicQueue *q) { return dynamic_deque_peek_front((DynamicDeque *)q); }

void dynamic_queue_destroy(DynamicQueue *q) { dynamic_deque_destroy((DynamicDeque *)q); }
