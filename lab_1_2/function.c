#include "function.h"
#include <stdlib.h>
#include <math.h>

int generate_primes(int n, int **primes_ptr, int *count_ptr) {
    if (n <= 0) return INPUT_ERROR;

    int limit;
    if (n < 6) {
        limit = 15;
    } else {
        limit = (int)(n * (log(n) + log(log(n))) + 10);
    }

    char *tmp = (char*)malloc((limit + 1) * sizeof(char));
    if (!tmp) return MEMORY_ERROR;

    for (int i = 0; i <= limit; i++) tmp[i] = 0;

    int *primes = (int*)malloc(n * sizeof(int));
    if (!primes) {
        free(tmp);
        return MEMORY_ERROR;
    }

    int idx = 0;
    for (int i = 2; i <= limit && idx < n; i++) {
        if (!tmp[i]) {
            primes[idx++] = i;
            if ((long long)i * i <= limit) {
                for (int j = i * i; j <= limit; j += i) {
                    tmp[j] = 1;
                }
            }
        }
    }

    free(tmp);
    *primes_ptr = primes;
    *count_ptr = idx;
    return OK;
}