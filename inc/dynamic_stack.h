#include <stdlib.h>
#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H

typedef struct dyns DynamicStack;

extern DynamicStack *dynamic_stack_init(size_t buf_size, const size_t data_size);
extern int dynamic_stack_empty(DynamicStack *stk);
extern int dynamic_stack_push(DynamicStack *stk, void *new_data);
extern int dynamic_stack_pop(DynamicStack *stk);
extern size_t dynamic_stack_capacity(DynamicStack *stk);
extern size_t dynamic_stack_length(DynamicStack *stk);
extern size_t dynamic_stack_data_size(DynamicStack *stk);
extern void *dynamic_stack_peek(DynamicStack *stk);
extern void dynamic_stack_clear(DynamicStack *stk);
extern void dynamic_stack_destroy(DynamicStack **stk);

#endif // DYNAMIC_QUEUE_H
