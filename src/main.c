#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector.h>

void int_free(void* int_ptr) {
    free((int*)int_ptr);
}

int* allocate_int(int num) {
    int* ptr = (int*)malloc(sizeof(int));
    if(ptr == NULL) {
        perror("allocate_int");
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
    /*
    int size = vector_size(vec);
    for(int i = 0; i < size; i++) {
        printf("%d\n", *(int*)vector_at(vec, i));
    }

    printf("\n\n");

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
/*
void run_str_vector_tests() {
    vector* vec = create_vector();
    assert(vector_capacity(vec) == START_SIZE);

    push_back(vec, "wow");
    push_back(vec, "cool");
    push_back(vec, "jonah morgan");
    push_back(vec, "chris morgan");

    push_back(vec, "jada morgan");
    push_back(vec, "jess morgan");
    push_back(vec, "wow");
    push_back(vec, "cool");

    push_back(vec, "jonah morgan");
    push_back(vec, "chris morgan");
    push_back(vec, "jada morgan");
    push_back(vec, "jess morgan");

    push_back(vec, "wow");
    push_back(vec, "cool");
    push_back(vec, "jonah morgan");
    push_back(vec, "chris morgan");

    push_back(vec, "wow");
    push_back(vec, "cool");
    push_back(vec, "jonah morgan");
    push_back(vec, "chris morgan");
    
    push_back(vec, "jada morgan");
    push_back(vec, "jess morgan");
    push_back(vec, "wow");
    push_back(vec, "cool");

    push_back(vec, "jonah morgan");
    push_back(vec, "chris morgan");
    push_back(vec, "jada morgan");
    push_back(vec, "jess morgan");

    push_back(vec, "wow");
    push_back(vec, "cool");
    push_back(vec, "jonah morgan");
    push_back(vec, "chris morgan");
    push_back(vec, "chris morgan");

    assert(vector_size(vec) == 33);
    assert(vector_capacity(vec) == START_SIZE * 2);
    assert(!vector_is_empty(vec));

    
    int size = vector_size(vec);
    for(int i = 0; i < size; i++) {
        printf("%s\n", (char*)vector_at(vec, i));
    }
    

    assert(strcmp((char*)vector_at(vec, 0), "wow") == 0);
    assert(strcmp((char*)vector_at(vec, 15), "chris morgan") == 0);
    assert(strcmp((char*)vector_at(vec, 31), "chris morgan") == 0);

    //write a function to free only vector items so that you can run this correctly
    vector_free(vec);
    printf("All vector string tests passed!\n");
}
*/

int main(int argc, char** argv) {
    run_int_vector_tests();
    //run_str_vector_tests();
    return 0;
}










