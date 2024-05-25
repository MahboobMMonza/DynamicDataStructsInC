#include <stdlib.h>
#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

typedef struct {
    void *internals;
    unsigned char *data;
} DynamicArray;

extern DynamicArray dynamic_array_init(const size_t buf_size, const size_t data_size);
extern int dynamic_array_empty(DynamicArray *arr);
extern int dynamic_array_push_back(DynamicArray *arr, const void *new_data);
extern int dynamic_array_pop_back(DynamicArray *arr);
extern int dynamic_array_insert(DynamicArray *arr, const void *new_data, const size_t idx);
extern int dynamic_array_delete(DynamicArray *arr, const size_t idx);
extern size_t dynamic_array_capacity(const DynamicArray *arr);
extern size_t dynamic_array_length(const DynamicArray *arr);
extern size_t dynamic_array_data_size(const DynamicArray *arr);
extern void *dynamic_array_back(const DynamicArray *arr);
extern void *dynamic_array_at(const DynamicArray *arr, const size_t idx);
extern void dynamic_array_clear(DynamicArray *arr);
extern void dynamic_array_destroy(DynamicArray *arr);

#endif // DYNAMIC_ARRAY_H
