#include "../inc/dynamic_stack.h"
#include "../inc/dynamic_deque.h"
#include <stdlib.h>

typedef struct dyns {
    DynamicDeque *ddq;
} DynamicStack;

DynamicStack *dynamic_stack_init(size_t buf_size, const size_t data_size) {
    DynamicDeque *ddq = dynamic_deque_init(buf_size, data_size);
    DynamicStack *stk = malloc(sizeof(DynamicStack));
    stk->ddq = ddq;
    return stk;
}

int dynamic_stack_empty(DynamicStack *stk) { return dynamic_deque_empty(stk->ddq); }

int dynamic_stack_push(DynamicStack *stk, void *new_data) { return dynamic_deque_push_back(stk->ddq, new_data); }

int dynamic_stack_pop(DynamicStack *stk) { return dynamic_deque_pop_back(stk->ddq); }

size_t dynamic_stack_capacity(DynamicStack *stk) { return dynamic_deque_capacity(stk->ddq); }

size_t dynamic_stack_length(DynamicStack *stk) { return dynamic_deque_length(stk->ddq); }

size_t dynamic_stack_data_size(DynamicStack *stk) { return dynamic_deque_data_size(stk->ddq); }

void *dynamic_stack_peek(DynamicStack *stk) { return dynamic_deque_peek_back(stk->ddq); }

void dynamic_stack_clear(DynamicStack *stk) { dynamic_deque_clear(stk->ddq); }

void dynamic_stack_destroy(DynamicStack **stk) {
    dynamic_deque_destroy(&(*stk)->ddq);
    *stk = NULL;
}
