#include <sys/types.h>
#include <vector_tests.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    run_int_vector_tests();
    run_str_vector_tests();
    run_2d_vector_tests();
    run_fit_vector_tests();
    run_vector_reserve_tests();
    printf("\nTESTS PASSED!\n");
   
    return 0;
}










