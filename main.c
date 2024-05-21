#include "dynamic_deque.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    int q;
    DynamicDeque dq = dynamic_deque_init(16, sizeof(int));
    printf("INTERNALS ADDRESS: %p\n", dq.internals);
    printf("CAPACITY: %ld\n", dynamic_deque_capacity(&dq));
    for (int i = 0; i < 16; i++) {
        printf("Pushing %d to FRONT\n", i);
        dynamic_deque_push_front(&dq, &i);
    }
    printf("LENGTH: %ld\n", dynamic_deque_length(&dq));
    for (int i = 16; i < 24; i++) {
        printf("Pushing %d to BACK\n", i);
        dynamic_deque_push_back(&dq, &i);
    }
    printf("LENGTH: %ld\n", dynamic_deque_length(&dq));
    printf("CAPACITY: %ld\n", dynamic_deque_capacity(&dq));
    while (!dynamic_deque_empty(&dq)) {
        q = *(int *)dynamic_deque_peek_front(&dq);
        printf("Popping %d from FRONT\n", q);
        dynamic_deque_pop_front(&dq);
    }
    dynamic_deque_destroy(&dq);
    if (dq.internals == NULL) {
        printf("SUCCESSFULLY DESTROYED DYNAMIC DEQUE\n");
    }
    return EXIT_SUCCESS;
}
