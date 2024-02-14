#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdlib.h>
#include <stdbool.h>

#define DEFAULT_VECTOR_CAP 8
#define GROWTH_RATE 1.5f

#define VECTOR_PTR_AT(VECTOR_PTR, INDEX) (((char*)(VECTOR_PTR)->ptr + (INDEX * (VECTOR_PTR)->item_size)))
#define VECTOR_AT(TYPE, VECTOR_PTR, INDEX) (*(((TYPE*)(VECTOR_PTR)->ptr) + INDEX))

#ifdef __cplusplus
extern "C" {
#endif

typedef struct vector
{
    void* ptr;
    size_t capacity;
    size_t len;
    int item_size;
} Vector;

struct vector* vector_init_vector(struct vector* vec, int item_size);

bool vector_ensure_capacity_vector(struct vector* vec, size_t new_size);

bool vector_push_back(struct vector* restrict, char const* item_ptr);

void* vector_pop_back(struct vector* vec);

void vector_deinit_vector(struct vector* vec);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // VECTOR_H_
