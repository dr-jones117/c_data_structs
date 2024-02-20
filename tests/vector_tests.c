#include "vector_tests.h"
#include <string.h>
#include <vector.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>


void int_free(void* int_ptr) {
    free((int*)int_ptr);
}


void double_free(void* double_ptr) {
    free((double*)double_ptr);
}


int* allocate_int(int num) {
    int* ptr = (int*)malloc(sizeof(int));
    if(ptr == NULL) {
        perror("allocate_int: Couldn't allocate the integer");
        exit(EXIT_FAILURE);
    }
    *ptr = num;
    return ptr;
}


double* allocate_double(double num) {
    double* ptr = (double*)malloc(sizeof(double));
    if(ptr == NULL) {
        perror("allocate_double: Couldn't allocate the double");
        exit(EXIT_FAILURE);
    }
    *ptr = num;
    return ptr;
}


void run_int_vector_tests() {
    vector* vec = create_vector();
    assert(vec != NULL);
    assert(vector_capacity(vec) == START_SIZE);
    assert(vector_is_empty(vec) == true);

    push_back(vec, allocate_int(12), &int_free);

    assert(vector_is_empty(vec) == false);
    assert(vector_size(vec) == 1);
    assert(*(int*)vector_at(vec, 0) == 12);

    push_back(vec, allocate_int(52), &int_free);
    push_back(vec, allocate_int(26), &int_free);
    push_back(vec, allocate_int(828371), &int_free);


    assert(vector_is_empty(vec) == false);
    assert(vector_size(vec) == 4);

    assert(*(int*)vector_at(vec, 1) == 52);
    assert(*(int*)vector_at(vec, 2) == 26);
    assert(*(int*)vector_at(vec, 3) == 828371);

    // Do a test to test vector_at out of bounds
    assert((int*)vector_at(vec, 4) == NULL);
    assert((int*)vector_at(vec, -1) == NULL);

    assert(vector_capacity(vec) == START_SIZE);

    push_back(vec, allocate_int(213), &int_free);
    assert(*(int*)vector_at(vec, 4) == 213);

    push_back(vec, allocate_int(-13), &int_free);
    assert(*(int*)vector_at(vec, 5) == -13);
    push_back(vec, allocate_int(1000), &int_free);
    assert(*(int*)vector_at(vec, 6) == 1000);
    assert(*(int*)vector_at(vec, 6) != -1);

    // Do more assertions for 1, 2, 3 to see if the items still exist
    assert(*(int*)vector_at(vec, 0) == 12);
    assert(*(int*)vector_at(vec, 1) == 52);
    assert(*(int*)vector_at(vec, 2) == 26);
    assert(*(int*)vector_at(vec, 3) == 828371);
    assert(vector_size(vec) == 7);

    // Example using for loop
    int size = vector_size(vec);
    for(int i = 0; i < size; i++) {
        printf("%d\n", *(int*)vector_at(vec, i));
    }

    printf("\n\n");

    /*
    // Example using while loop
    void** begin = vector_begin(vec);
    while (*begin != NULL) {
        printf("%d\n", **(int**)begin);  // Cast void* to int* before dereferencing
        begin++;  // Increment the pointer by 1 (size of void*)
    }

    printf("\n%d\n", **(int**)vector_end(vec));
    */

    assert(*(int*)(**(vector_item**)vector_end(vec)).item == 1000);

    pop_back(vec);
    pop_back(vec);
    pop_back(vec);

    assert(*(int*)(**(vector_item**)vector_end(vec)).item == 828371);
    assert(vector_size(vec) == 4);

    pop_back(vec);
    pop_back(vec);
    pop_back(vec);
    pop_back(vec);

    assert(vector_is_empty(vec));
    assert(vector_size(vec) == 0);
    assert((void*)vector_at(vec, 0) == NULL);

    vector_free(vec); 
    printf("All integer vector tests passed!\n");
}



//running test when startsize is 16!!!
void run_str_vector_tests() {
    vector* vec = create_vector();
    assert(vector_capacity(vec) == START_SIZE);

    push_back(vec, "wow", NULL);
    push_back(vec, "cool", NULL);
    push_back(vec, "jonah morgan", NULL);
    push_back(vec, "chris morgan", NULL);

    push_back(vec, "jada morgan", NULL);
    push_back(vec, "jess morgan", NULL);
    push_back(vec, "wow", NULL);
    push_back(vec, "cool", NULL);

    push_back(vec, "wow", NULL);
    push_back(vec, "cool", NULL);
    push_back(vec, "jonah morgan", NULL);
    push_back(vec, "chris morgan", NULL);

    push_back(vec, "jada morgan", NULL);
    push_back(vec, "jess morgan", NULL);
    push_back(vec, "wow", NULL);
    push_back(vec, "cool", NULL);

    push_back(vec, "wow", NULL);
    push_back(vec, "cool", NULL);
    push_back(vec, "jonah morgan", NULL);
    push_back(vec, "chris morgan", NULL);

    push_back(vec, "jada morgan", NULL);
    push_back(vec, "jess morgan", NULL);
    push_back(vec, "wow", NULL);
    push_back(vec, "cool", NULL);

    push_back(vec, "wow", NULL);
    push_back(vec, "cool", NULL);
    push_back(vec, "jonah morgan", NULL);
    push_back(vec, "chris morgan", NULL);

    push_back(vec, "jada morgan", NULL);
    push_back(vec, "jess morgan", NULL);
    push_back(vec, "wow", NULL);
    push_back(vec, "cool", NULL);

    push_back(vec, "cool", NULL);

    assert(vector_size(vec) == 33);
    assert(vector_capacity(vec) == START_SIZE * 2);
    assert(!vector_is_empty(vec));

    int size = vector_size(vec);
    for(int i = 0; i < size; i++) {
        printf("%s\n", (char*)vector_at(vec, i));
    }
    
    assert(strcmp((char*)vector_at(vec, 0), "wow") == 0);
    assert(strcmp((char*)vector_at(vec, 15), "cool") == 0);
    assert(strcmp((char*)vector_at(vec, 31), "cool") == 0);

    int init_size = vector_size(vec);
    for(int i = 0; i < init_size; i++) {
        pop_back(vec);
        assert(vector_size(vec) == init_size - (i + 1));
    }
    assert(vector_is_empty(vec));
    assert(vector_size(vec) == 0);

    //write a function to free only vector items so that you can run this correctly
    vector_free(vec);
    printf("All vector string tests passed!\n");
}

double randfrom(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

void run_2d_vector_tests() {
    vector* vec_2d = create_vector();
    int y = 5;
    int x = 3;

    for(int i = 0; i < y; i++) {
        vector* inner_vec = create_vector();
        for(int j = 0; j < x; j++) {
            push_back(inner_vec, allocate_double(randfrom(0, 1000)), &double_free);
        }
        push_back(vec_2d, inner_vec, &vector_free);
    }

    for(int i = 0; i < y; i++) {
        vector* inner_vec = vector_at(vec_2d, i);
        for(int j = 0; j < x; j++) {
           printf("%1f ", *(double*)vector_at(inner_vec, j)); 
        }
        printf("\n");
    }

    printf("\nDONE!\n");

    vector_free(vec_2d);
}







