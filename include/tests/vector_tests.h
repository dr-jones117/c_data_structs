#ifndef __VECTOR_TESTS_H_
#define __VECTOR_TESTS_H_

void int_free(void* int_ptr);
void double_free(void* double_ptr);

int* allocate_int(int num);
double* allocate_double(double num);
void run_int_vector_tests();
void run_str_vector_tests();
void run_2d_vector_tests();
void run_fit_vector_tests();
void run_vector_reserve_tests();

#endif

