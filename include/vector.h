#ifndef __VECTOR_H_
#define __VECTOR_H_
#define START_SIZE 32

#include<stdlib.h>
#include<stdbool.h>


typedef void (*free_func)(void*);
typedef struct vector_item {
    free_func f_func;
    void* item;
} vector_item;

/* This vector object is generic. It holds a dynamic array
 * of pointers to objects. You can use mix any types, but
 * it's not recommended. */
typedef struct vector {
    int capacity;
    int end_idx;
    vector_item** items;
} vector;

// Constructor
vector* create_vector();

// Deconstructor
void vector_free(void* vec);
void vector_free_items(vector* vec);

// Modifiers
// You MUST give a pointer to a void function so that the object
// knows how to free itself from memory. keep free_func as NULL if
// the item wasn't allocated dynamically.
void push_back(vector* vec, void* item, void* free_func);
void pop_back(vector* vec);

// Capacity
size_t vector_size(vector* vec);
bool vector_is_empty(vector* vec);
void vector_reserve(vector* vec, size_t size);
size_t vector_capacity(vector* vec);
void vector_shrink_to_fit(vector* vec);

// Element access
void* vector_at(vector* vec, int idx);
vector_item** vector_begin(vector* vec);
vector_item** vector_end(vector* vec);


#endif 
