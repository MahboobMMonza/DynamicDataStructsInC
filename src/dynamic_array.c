#include "../inc/dynamic_array.h"
#include <stdlib.h>
#include <string.h>

typedef struct a {
    size_t __len, __capacity, __data_size;
} da_internals;

DynamicArray dynamic_array_init(const size_t buf_size, const size_t data_size) {
    da_internals *internals = malloc(sizeof(da_internals));
    *internals = (da_internals){.__len = 0, .__capacity = buf_size, .__data_size = data_size};
    unsigned char *data = malloc(data_size * buf_size);
    return (DynamicArray){.internals = internals, .data = data};
}

int __reallocate_data_buffer(DynamicArray *arr) {
    da_internals *internals = arr->internals;
    unsigned char *new_buf = reallocarray(arr->data, 2 * internals->__capacity, internals->__data_size);
    if (new_buf == NULL) {
        return -1;
    }
    arr->data = new_buf;
    internals->__capacity = 2 * internals->__capacity;
    return 0;
}

int dynamic_array_empty(DynamicArray *arr) {
    da_internals *internals = arr->internals;
    return internals->__len == 0;
}

int dynamic_array_push_back(DynamicArray *arr, const void *new_data) {
    da_internals *internals = arr->internals;
    int resp = 0;
    if (internals->__capacity == internals->__len) {
        resp = __reallocate_data_buffer(arr);
    }
    if (resp) {
        return resp;
    }
    memcpy(arr->data + (internals->__data_size * internals->__len), new_data, internals->__data_size);
    ++internals->__len;
    return resp;
}

int dynamic_array_pop_back(DynamicArray *arr) {
    da_internals *internals = arr->internals;
    if (internals->__len == 0) {
        return -1;
    }
    --internals->__len;
    return 0;
}

int dynamic_array_insert(DynamicArray *arr, const void *new_data, const size_t idx) {
    da_internals *internals = arr->internals;
    int resp = 0;
    if (internals->__len == internals->__capacity) {
        resp = __reallocate_data_buffer(arr);
    }
    if (idx >= internals->__len) {
        resp = -1;
    }
    if (resp) {
        return resp;
    }
    // Only shift if item is not inserted at the end
    if (idx < internals->__len - 1) {
        memmove(arr->data + (internals->__data_size * (idx + 1)), arr->data + (internals->__data_size * idx),
                internals->__data_size * (internals->__len - idx));
    }
    memcpy(arr->data + (internals->__data_size * idx), new_data, internals->__data_size);
    ++internals->__len;
    return resp;
}

int dynamic_array_delete(DynamicArray *arr, const size_t idx) {
    da_internals *internals = arr->internals;
    if (idx >= internals->__len) {
        return -1;
    }
    // Only shift if the item being deleted is not the last element
    if (idx < internals->__len - 1) {
        memmove(arr->data + (internals->__data_size * idx), arr->data + (internals->__data_size * (idx + 1)),
                internals->__data_size * (internals->__len - idx - 1));
    }
    --internals->__len;
    return 0;
}

size_t dynamic_array_capacity(const DynamicArray *arr) { return ((da_internals *)arr->internals)->__capacity; }

size_t dynamic_array_length(const DynamicArray *arr) { return ((da_internals *)arr->internals)->__len; }

size_t dynamic_array_data_size(const DynamicArray *arr) { return ((da_internals *)arr->internals)->__data_size; }

void *dynamic_array_back(const DynamicArray *arr) {
    da_internals *internals = arr->internals;
    if (internals->__len == 0) {
        return NULL;
    }
    return arr->data + (internals->__data_size * (internals->__len - 1));
}

void *dynamic_array_at(const DynamicArray *arr, const size_t idx) {
    da_internals *internals = arr->internals;
    if (idx >= internals->__len) {
        return NULL;
    }
    return arr->data + (internals->__data_size * idx);
}

void dynamic_array_clear(DynamicArray *arr) {
    da_internals *internals = arr->internals;
    // to clear what was deleted as well so that no trace remains
    memset(arr->data, '\0', internals->__data_size * internals->__capacity);
}

void dynamic_array_destroy(DynamicArray *arr) {
    free(arr->internals);
    free(arr->data);
    arr->internals = arr->data = NULL;
}
