#include <stdio.h>

#include "vector.h"

int main(void)
{
    Vector vec = { 0 };

    if (!vector_init_vector(&vec, sizeof(int)))
        return 1;

    int item = 42;
    if (!vector_push_back(&vec, (char*)&item))
        return 1;

    item = 37;
    if (!vector_push_back(&vec, (char*)&item))
        return 1;

    for (int i = 0; i < (int)vec.len; ++i) {
        printf("%d\n", *(int*)VECTOR_PTR_AT(&vec, i));
    }
    int* last = (int*)vector_pop_back(&vec);
    if (last) {
        printf("last: %d\n", *last);
    }
    printf("new last: %d\n", VECTOR_AT(int, &vec, vec.len - 1));

    vector_deinit_vector(&vec);

    return 0;
}
