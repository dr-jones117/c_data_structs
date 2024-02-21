#ifndef __ALLOCATE_H_
#define __ALLOCATE_H_

// Free objects from memory
void int_free(void* int_ptr);
void double_free(void* double_ptr);

// Allocate objects into memory
int* allocate_int(int num);
double* allocate_double(double num);

#endif 
