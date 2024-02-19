#ifndef __VECTOR_H_
#define __VECTOR_H_
#define START_SIZE 32

#include<stdlib.h>
#include<stdbool.h>

/* This vector object is generic. It holds a dynamic array
 * of pointers to objects. You can use mix any types, but
 * it's not recommended. */
typedef struct vector {
    int capacity;
    int end_idx;
    void** items;
} vector;

// Constructor
vector* create_vector();

// Deconstructor
void vector_free(vector* vec);
void vector_free_items(vector* vec);

// Modifiers
void push_back(vector* vec, void* item);
void pop_back(vector* vec);

// Capacity
size_t vector_size(vector* vec);
bool vector_is_empty(vector* vec);
void vector_reserve(vector* vec, size_t size);
size_t vector_capacity(vector* vec);
void vector_shrink_to_fit(vector* vec);

// Element access
void* vector_at(vector* vec, int idx);
void** vector_begin(vector* vec);
void** vector_end(vector* vec);


#endif 
