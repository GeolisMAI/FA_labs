#ifndef SOLUTION_H
#define SOLUTION_H

typedef enum {
    OK = 0,
    INPUT_ERROR = -1,
    MEMORY_ERROR = -2,
    PRIME_ERROR = -3
} Error_results;

int generate_primes(int n, int **primes_ptr, int *count_ptr);

#endif