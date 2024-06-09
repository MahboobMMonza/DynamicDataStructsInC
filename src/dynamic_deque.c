#include "../inc/dynamic_deque.h"
#include <stdlib.h>
#include <string.h>

typedef struct dynq {
    size_t __head, __tail, __capacity, __len, __data_size;
    unsigned char *__data_buf;
} DynamicDeque;

DynamicDeque *dynamic_deque_init(size_t buf_size, const size_t data_size) {
    // Use malloc since it's faster, we don't care about initial state of data
    DynamicDeque *dq = malloc(sizeof(DynamicDeque));
    *dq = (DynamicDeque){.__data_size = data_size,
                         .__capacity = buf_size,
                         .__head = 0,
                         .__tail = 0,
                         .__len = 0,
                         .__data_buf = malloc(buf_size * data_size)};
    return dq;
}

int __reallocate_data_buffer(DynamicDeque *dq) {
    unsigned char *new_buf = reallocarray(dq->__data_buf, 2 * dq->__capacity, dq->__data_size);
    if (new_buf == NULL) {
        return -1;
    }
    dq->__data_buf = new_buf;
    dq->__capacity = 2 * dq->__capacity;
    // loop around rearrangement
    if (dq->__tail < dq->__head) {
        // Area of interest should not overlap with existing data, so overwrite
        memcpy(dq->__data_buf + (dq->__len * dq->__data_size), dq->__data_buf,
               dq->__head * dq->__data_size);
        dq->__tail = dq->__head + dq->__len - 1;
    }
    if (dq->__head > (dq->__capacity >> 1)) {
        memmove(dq->__data_buf + ((dq->__capacity >> 2) * dq->__data_size),
                dq->__data_buf + (dq->__head * dq->__data_size),
                dq->__data_size * dq->__len);
        dq->__head = dq->__capacity >> 2;
        dq->__tail = dq->__head + dq->__len - 1;
    }
    return 0;
}

int dynamic_deque_empty(DynamicDeque *dq) {
    return dq->__len == 0;
}

int dynamic_deque_push_front(DynamicDeque *dq, void *new_data) {
    int resp = 0;
    if (dq->__len == dq->__capacity) {
        resp = __reallocate_data_buffer(dq);
    }
    if (resp == -1) {
        return resp;
    }
    if (dq->__len > 0) {
        if (dq->__head == 0) {
            dq->__head = dq->__capacity - 1;
        } else {
            dq->__head--;
        }
    }
    memcpy(dq->__data_buf + (dq->__head * dq->__data_size), new_data, dq->__data_size);
    dq->__len++;
    return resp;
}

int dynamic_deque_push_back(DynamicDeque *dq, void *new_data) {
    int resp = 0;
    if (dq->__len == dq->__capacity) {
        resp = __reallocate_data_buffer(dq);
    }
    if (resp == -1) {
        return resp;
    }
    if (dq->__len > 0) {
        dq->__tail++;
        if (dq->__tail == dq->__capacity) {
            dq->__tail = 0;
        }
    }
    memcpy(dq->__data_buf + (dq->__tail * dq->__data_size), new_data, dq->__data_size);
    dq->__len++;
    return resp;
}

int dynamic_deque_pop_front(DynamicDeque *dq) {
    if (dq->__len == 0) {
        return -1;
    }
    if (dq->__head == dq->__capacity - 1) {
        dq->__head = 0;
    } else {
        dq->__head++;
    }
    dq->__len--;
    return 0;
}

int dynamic_deque_pop_back(DynamicDeque *dq) {
    if (dq->__len == 0) {
        return -1;
    }
    if (dq->__tail == 0) {
        dq->__tail = dq->__capacity - 1;
    } else {
        dq->__tail--;
    }
    dq->__len--;
    return 0;
}

size_t dynamic_deque_capacity(DynamicDeque *dq) {
    return dq->__capacity;
}

size_t dynamic_deque_length(DynamicDeque *dq) {
    return dq->__len;
}

size_t dynamic_deque_data_size(DynamicDeque *dq) {
    return dq->__data_size;
}

void *dynamic_deque_peek_front(DynamicDeque *dq) {
    if (dq->__len == 0) {
        return NULL;
    }
    return dq->__data_buf + (dq->__head * dq->__data_size);
}

void *dynamic_deque_peek_back(DynamicDeque *dq) {
    if (dq->__len == 0) {
        return NULL;
    }
    return dq->__data_buf + (dq->__tail * dq->__data_size);
}

void dynamic_deque_clear(DynamicDeque *dq) {
    memset(dq->__data_buf, '\0', dq->__data_size * dq->__capacity);
    dq->__head = dq->__tail = dq->__len = 0;
}

void dynamic_deque_destroy(DynamicDeque **dq) {
    free((*dq)->__data_buf);
    free(*dq);
    *dq = NULL;
}
