#include "../inc/dynamic_deque.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t __head, __tail, __capacity, __len, __data_size;
    unsigned char *__data_buf;
} ddq_internals;

DynamicDeque dynamic_deque_init(size_t buf_size, const size_t data_size) {
    ddq_internals *internals = malloc(sizeof(ddq_internals));
    // Use malloc since it's faster, we don't care about initial state of data
    *internals = (ddq_internals){.__data_size = data_size,
                                 .__capacity = buf_size,
                                 .__head = 0,
                                 .__tail = 0,
                                 .__len = 0,
                                 .__data_buf = malloc(buf_size * data_size)};
    DynamicDeque dq = {.internals = internals};
    return dq;
}

int __reallocate_data_buffer(DynamicDeque *dq) {
    ddq_internals *internals = dq->internals;
    unsigned char *new_buf = reallocarray(internals->__data_buf, 2 * internals->__capacity, internals->__data_size);
    if (new_buf == NULL) {
        return -1;
    }
    internals->__data_buf = new_buf;
    internals->__capacity = 2 * internals->__capacity;
    // loop around rearrangement
    if (internals->__tail < internals->__head) {
        // Area of interest should not overlap with existing data, so overwrite
        memcpy(internals->__data_buf + (internals->__len * internals->__data_size), internals->__data_buf,
               internals->__head * internals->__data_size);
        internals->__tail = internals->__head + internals->__len - 1;
    }
    if (internals->__head > internals->__capacity / 2) {
        memmove(internals->__data_buf + ((internals->__capacity / 4) * internals->__data_size), internals->__data_buf + (internals->__head * internals->__data_size), internals->__data_size * internals->__len);
        internals->__head = internals->__capacity / 4;
        internals->__tail = internals->__head + internals->__len - 1;
    }
    return 0;
}

int dynamic_deque_empty(DynamicDeque *dq) {
    ddq_internals *internals = dq->internals;

    return internals->__len == 0;
}

int dynamic_deque_push_front(DynamicDeque *dq, void *new_data) {
    ddq_internals *internals = dq->internals;
    int resp = 0;
    if (internals->__len == internals->__capacity) {
        resp = __reallocate_data_buffer(dq);
    }
    if (resp == -1) {
        return resp;
    }
    if (internals->__len > 0) {
        if (internals->__head == 0) {
            internals->__head = internals->__capacity - 1;
        } else {
            internals->__head--;
        }
    }
    memcpy(internals->__data_buf + (internals->__head * internals->__data_size), new_data, internals->__data_size);
    internals->__len++;
    return resp;
}

int dynamic_deque_push_back(DynamicDeque *dq, void *new_data) {
    ddq_internals *internals = dq->internals;
    int resp = 0;
    if (internals->__len == internals->__capacity) {
        resp = __reallocate_data_buffer(dq);
    }
    if (resp == -1) {
        return resp;
    }
    if (internals->__len > 0) {
        internals->__tail++;
        if (internals->__tail == internals->__capacity) {
            internals->__tail = 0;
        }
    }
    memcpy(internals->__data_buf + (internals->__tail * internals->__data_size), new_data, internals->__data_size);
    internals->__len++;
    return resp;
}

int dynamic_deque_pop_front(DynamicDeque *dq) {
    ddq_internals *internals = dq->internals;
    if (internals->__len == 0) {
        return -1;
    }
    if (internals->__head == internals->__capacity - 1) {
        internals->__head = 0;
    } else {
        internals->__head++;
    }
    internals->__len--;
    return 0;
}

int dynamic_deque_pop_back(DynamicDeque *dq) {
    ddq_internals *internals = dq->internals;
    if (internals->__len == 0) {
        return -1;
    }
    if (internals->__tail == 0) {
        internals->__tail = internals->__capacity - 1;
    } else {
        internals->__tail--;
    }
    internals->__len--;
    return 0;
}

size_t dynamic_deque_capacity(DynamicDeque *dq) {
    ddq_internals *internals = dq->internals;
    return internals->__capacity;
}

size_t dynamic_deque_length(DynamicDeque *dq) {
    ddq_internals *internals = dq->internals;
    return internals->__len;
}

size_t dynamic_deque_data_size(DynamicDeque *dq) {
    ddq_internals *internals = dq->internals;
    return internals->__data_size;
}

void *dynamic_deque_peek_front(DynamicDeque *dq) {
    ddq_internals *internals = dq->internals;
    if (internals->__len == 0) {
        return NULL;
    }
    return internals->__data_buf + (internals->__head * internals->__data_size);
}

void *dynamic_deque_peek_back(DynamicDeque *dq) {
    ddq_internals *internals = dq->internals;
    if (internals->__len == 0) {
        return NULL;
    }
    return internals->__data_buf + (internals->__tail * internals->__data_size);
}

void dynamic_deque_clear(DynamicDeque *dq) {
    ddq_internals *internals = dq->internals;
    memset(internals->__data_buf, '\0', internals->__data_size * internals->__capacity);
    internals->__head = internals->__tail = internals->__len = 0;
}

void dynamic_deque_destroy(DynamicDeque *dq) {
    ddq_internals *internals = dq->internals;
    free(internals->__data_buf);
    free(internals);
    dq->internals = NULL;
}
