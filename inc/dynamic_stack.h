#include <stdlib.h>
#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H

typedef struct {
    void *internals;
} DynamicStack;

extern DynamicStack dynamic_stack_init(size_t buf_size, const size_t data_size);
extern int dynamic_stack_empty(DynamicStack *q);
extern int dynamic_stack_push(DynamicStack *q, void *new_data);
extern int dynamic_stack_pop(DynamicStack *q);
extern size_t dynamic_stack_capacity(DynamicStack *q);
extern size_t dynamic_stack_length(DynamicStack *q);
extern size_t dynamic_stack_data_size(DynamicStack *q);
extern void *dynamic_stack_peek(DynamicStack *q);
extern void dynamic_stack_clear(DynamicStack *q);
extern void dynamic_stack_destroy(DynamicStack *q);

#endif // DYNAMIC_QUEUE_H
