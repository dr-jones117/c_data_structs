#include <allocate.h>
#include <stdlib.h>
#include <stdio.h>

void int_free(void* int_ptr) {
    free(int_ptr);
}


void double_free(void* double_ptr) {
    free(double_ptr);
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


