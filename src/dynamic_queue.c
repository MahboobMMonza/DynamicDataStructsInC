#include "../inc/dynamic_queue.h"
#include "../inc/dynamic_deque.h"
#include <stdlib.h>

typedef struct dynq {
    DynamicDeque *ddq;
} DynamicQueue;

DynamicQueue *dynamic_queue_init(size_t buf_size, const size_t data_size) {
    DynamicDeque *ddq = dynamic_deque_init(buf_size, data_size);
    DynamicQueue *q = malloc(sizeof(DynamicQueue));
    q->ddq = ddq;
    return q;
}

int dynamic_queue_empty(DynamicQueue *q) { return dynamic_deque_empty(q->ddq); }

int dynamic_queue_enqueue(DynamicQueue *q, void *new_data) { return dynamic_deque_push_back(q->ddq, new_data); }

int dynamic_queue_dequeue(DynamicQueue *q) { return dynamic_deque_pop_front(q->ddq); }

size_t dynamic_queue_capacity(DynamicQueue *q) { return dynamic_deque_capacity(q->ddq); }

size_t dynamic_queue_length(DynamicQueue *q) { return dynamic_deque_length(q->ddq); }

size_t dynamic_queue_data_size(DynamicQueue *q) { return dynamic_deque_data_size(q->ddq); }

void *dynamic_queue_peek(DynamicQueue *q) { return dynamic_deque_peek_front(q->ddq); }

void dynamic_queue_clear(DynamicQueue *q) { dynamic_deque_clear(q->ddq); }

void dynamic_queue_destroy(DynamicQueue **q) {
    dynamic_deque_destroy(&(*q)->ddq);
    *q = NULL;
}
