#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "vector.h"

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


