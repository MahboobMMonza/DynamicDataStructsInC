#include <stdlib.h>
#ifndef DYNAMIC_DEQUE_H
#define DYNAMIC_DEQUE_H

typedef struct dynq DynamicDeque;

extern DynamicDeque *dynamic_deque_init(size_t buf_size, const size_t data_size);
extern int dynamic_deque_empty(DynamicDeque *dq);
extern int dynamic_deque_push_front(DynamicDeque *dq, void *new_data);
extern int dynamic_deque_push_back(DynamicDeque *dq, void *new_data);
extern int dynamic_deque_pop_front(DynamicDeque *dq);
extern int dynamic_deque_pop_back(DynamicDeque *dq);
extern size_t dynamic_deque_capacity(DynamicDeque *dq);
extern size_t dynamic_deque_length(DynamicDeque *dq);
extern size_t dynamic_deque_data_size(DynamicDeque *dq);
extern void *dynamic_deque_peek_front(DynamicDeque *dq);
extern void *dynamic_deque_peek_back(DynamicDeque *dq);
extern void dynamic_deque_clear(DynamicDeque *dq);
extern void dynamic_deque_destroy(DynamicDeque **dq);

#endif // DYNAMIC_DEQUE_H
