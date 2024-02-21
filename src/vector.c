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
    vector_item** items = (vector_item**)malloc(sizeof(vector_item*) * VECTOR_START_SIZE);
    if(items == NULL){
        perror("create_vector");
        free(vec);
        return NULL;
    }

    // Assign everything to the vector.
    vec->capacity = VECTOR_START_SIZE;
    vec->end_idx = 0;
    vec->items = items;

    return vec;
}


// Deconstructor
void vector_free(void* vec) {
    if (vec == NULL)
        return; 

    vector* v = (vector*)vec;
    int size = vector_size(v);

    for(int i = 0; i < size; i++) {
        vector_item* item = v->items[i];
        if (item != NULL && item->f_func != NULL) {
            item->f_func(item->item); 
        }
        free(item); 
    }

    if (v->items != NULL)
        free(v->items);
    free(v); 
}


// Modifiers 
void push_back(vector* vec, void* item, void* free_func) {
    if (vector_size(vec) >= vec->capacity) {
        // Resize the items array if necessary
        size_t new_capacity = vec->capacity * 2; // Double the capacity
        vector_item** new_items = (vector_item**)realloc(vec->items, sizeof(vector_item*)
                                                         * new_capacity);
        if (new_items == NULL) {
            perror("push_back: Failed to reallocate memory for items");
            return;
        }
        vec->items = new_items;
        vec->capacity = new_capacity;
    }

    vector_item* new_item = (vector_item*)malloc(sizeof(vector_item));
    if(new_item == NULL) {
        perror("push_back: Could allocate vector item.");
        exit(EXIT_FAILURE);
    }

    new_item->item = item;
    new_item->f_func = free_func;

    // Add the kitem to the end of the vector
    vec->items[vec->end_idx++] = new_item;
}


void pop_back(vector* vec) {
    if (vector_is_empty(vec)) {
        perror("pop_back: Vector is empty");
        return;
    }

    vec->end_idx--;

    vector_item* item = vec->items[vec->end_idx];

    if (item->f_func != NULL) {
        item->f_func(item->item);
    }

    vec->items[vec->end_idx] = NULL;
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


void vector_shrink_to_fit(vector* vec) {
    if(vec == NULL)
        return;

    int size = vector_size(vec);


}


// Element Access
void* vector_at(vector* vec, int idx) {
    if(idx > vec->end_idx || idx <= -1 || vec->items[idx] == NULL) {
        perror("vector_at: out of bounds");
        return NULL;
    }
    return vec->items[idx]->item;
}


vector_item** vector_begin(vector* vec) {
    if(!vector_is_empty(vec)) {
        return vec->items;
    }
    return NULL;
}


vector_item** vector_end(vector* vec) {
    if (!vector_is_empty(vec)) {
        return vec->items + (vector_size(vec) - 1);
    }
    return NULL;
}










