#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main(void) {
    int T;
    if (scanf("%d", &T) != 1 || T <= 0) {
        printf("Input error\n");
        return INPUT_ERROR;
    }

    int *queries = (int*)malloc(T * sizeof(int));
    if (!queries) {
        printf("Memory error\n");
        return MEMORY_ERROR;
    }

    int max_val = 0;
    for (int i = 0; i < T; i++) {
        if (scanf("%d", &queries[i]) != 1 || queries[i] <= 0) {
            printf("Invalid query\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            
            queries[i] = -1;
            continue;
        }
        if (queries[i] > max_val) max_val = queries[i];
    }

    if (max_val == 0) {
        printf("No valid queries\n");
        free(queries);
        return INPUT_ERROR;
    }

    int *primes = NULL;
    int total = 0;
    int status = generate_primes(max_val, &primes, &total);
    if (status != OK) {
        printf("Prime generation error\n");
        free(queries);
        return status;
    }

    for (int i = 0; i < T; i++) {
        if (queries[i] == -1) {
            continue;
        }
        int idx = queries[i] - 1;
        if (idx < total) {
            printf("%d\n", primes[idx]);
        } else {
            printf("Error: prime index %d out of range\n", queries[i]);
        }
    }

    free(primes);
    free(queries);
    return OK;
}