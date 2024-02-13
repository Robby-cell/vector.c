#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define DEFAULT_VECTOR_CAP 8
#define GROWTH_RATE 1.5f

#define VECTOR_PTR_AT(VECTOR_PTR, INDEX) (((char*)(VECTOR_PTR)->ptr + (INDEX * (VECTOR_PTR)->item_size)))
#define VECTOR_AT(TYPE, VECTOR_PTR, INDEX) (*(((TYPE*)(VECTOR_PTR)->ptr) + INDEX))

typedef struct vector
{
    void* ptr;
    size_t capacity;
    size_t len;
    int item_size;
} Vector;

struct vector* vector_init_vector(struct vector* vec, int item_size)
{
    vec->len = 0;
    vec->capacity = 0;
    vec->item_size = item_size;
    vec->ptr = NULL;

    return vec;
}

bool vector_ensure_capacity_vector(struct vector* vec, size_t new_size)
{
    if (vec->capacity < DEFAULT_VECTOR_CAP) {
        vec->capacity = DEFAULT_VECTOR_CAP;
    }
    if (!vec->ptr) {
        vec->ptr = malloc(vec->capacity * vec->item_size);
        if (!vec->ptr) {
            return false;
        }
    }

    if (vec->capacity > new_size) {
        return true;
    }

    size_t new_cap = vec->capacity * GROWTH_RATE;

    void* new_ptr = realloc(vec->ptr, new_cap * vec->item_size);
    if (!new_ptr) {
        return false;
    }

    vec->ptr = new_ptr;
    vec->capacity = new_cap;
    return true;
}

bool vector_push_back(struct vector* restrict vec, char const* item_ptr)
{
    if (!vector_ensure_capacity_vector(vec, vec->len + 1)) {
        return false;
    }

    void* ptr = (char*)vec->ptr + vec->len * vec->item_size;
    if (!memcpy(ptr, item_ptr, vec->item_size)) {
        return false;
    }
    vec->len++;
    return true;
}

void* vector_pop_back(struct vector* vec)
{
    if (!(vec->len > 0)) {
        return NULL;
    }
    void* ptr = (void*)VECTOR_PTR_AT(vec, --vec->len);
    return ptr;
}

void vector_deinit_vector(struct vector* vec)
{
    if (vec->ptr) {
        free(vec->ptr);
    }
}

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
