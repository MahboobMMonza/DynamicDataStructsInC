#include "../inc/dynamic_stack.h"
#include "../inc/dynamic_deque.h"
#include <stdlib.h>

DynamicStack dynamic_stack_init(size_t buf_size, const size_t data_size) {
    DynamicDeque ddq = dynamic_deque_init(buf_size, data_size);
    DynamicStack q = *(DynamicStack *)&ddq;
    return q;
}

int dynamic_stack_empty(DynamicStack *q) { return dynamic_deque_empty((DynamicDeque *)q); }

int dynamic_stack_push(DynamicStack *q, void *new_data) { return dynamic_deque_push_back((DynamicDeque *)q, new_data); }

int dynamic_stack_pop(DynamicStack *q) { return dynamic_deque_pop_back((DynamicDeque *)q); }

size_t dynamic_stack_capacity(DynamicStack *q) { return dynamic_deque_capacity((DynamicDeque *)q); }

size_t dynamic_stack_length(DynamicStack *q) { return dynamic_deque_length((DynamicDeque *)q); }

size_t dynamic_stack_data_size(DynamicStack *q) { return dynamic_deque_data_size((DynamicDeque *)q); }

void *dynamic_stack_peek(DynamicStack *q) { return dynamic_deque_peek_back((DynamicDeque *)q); }

void dynamic_stack_clear(DynamicStack *q) { dynamic_deque_clear((DynamicDeque *)q); }

void dynamic_stack_destroy(DynamicStack *q) { dynamic_deque_destroy((DynamicDeque *)q); }
