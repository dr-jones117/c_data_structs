#include <stdio.h>
#include <vector.h>
#include <stdlib.h>


// Constructor
vector* create_vector() {
    // Allocate memory for the vector.
    vector* vec = (vector*)malloc(sizeof(vector));
    if(vec == NULL) {
        perror("create_vector");
        return NULL;
    }

    // Allocate memory for the items.
    void** items = (void**)malloc(sizeof(void*) * START_SIZE);
    if(items == NULL){
        perror("create_vector");
        free(vec);
        return NULL;
    }

    // Assign everything to the vector.
    vec->capacity = START_SIZE;
    vec->end_idx = 0;
    vec->items = items;

    return vec;
}


// Deconstructor
void vector_free(vector* vec) {
    int size = vector_size(vec);
    for(int i = 0; i < size; i++) {
        free(vec->items[i]);
    }

    if (vec != NULL) {
        free(vec->items);
        free(vec);
    }
}


// Modifiers 
void push_back(vector* vec, void* item) {
    if (vector_size(vec) >= vec->capacity) {
        // Resize the items array if necessary
        size_t new_capacity = vec->capacity * 2; // Double the capacity
        void** new_items = (void**)realloc(vec->items, sizeof(void*) * new_capacity);
        if (new_items == NULL) {
            perror("push_back: Failed to reallocate memory for items");
            return;
        }
        vec->items = new_items;
        vec->capacity = new_capacity;
    }

    // Add the item to the end of the vector
    vec->items[vec->end_idx++] = item;
}


void pop_back(vector* vec) {
    if(!vector_is_empty(vec)) {
        free(vec->items[--vec->end_idx]);
        vec->items[vec->end_idx] = NULL;
    }
    else {
        perror("pop_back: Vector is empty");
    }
}


// Capacity
size_t vector_size(vector *vec) {
    return vec->end_idx;
}


bool vector_is_empty(vector *vec) {
    if(vec->end_idx == 0) {
        return true;
    }
    return false;
}


size_t vector_capacity(vector *vec) {
    return vec->capacity;
}


// Element Access
void* vector_at(vector* vec, int idx) {
    if(idx > vec->end_idx || idx <= -1) {
        perror("vector_at: out of bounds");
        return NULL;
    }
    return vec->items[idx];
}


void** vector_begin(vector* vec) {
    if(!vector_is_empty(vec)) {
        return vec->items;
    }
    return NULL;
}


void** vector_end(vector* vec) {
    if (!vector_is_empty(vec)) {
        return vec->items + (vector_size(vec) - 1);
    }
    return NULL;
}
