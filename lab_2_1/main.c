#include <stdio.h>
#include <stdlib.h>
#include "function.h"

#define COUNTER 30
#define ARGS 0.7, 1.0 / 3.0, 0.125, 0.14285714285714, 0.16666666666666, 0.2, 0.25, 0.3, 0.375, 0.4, 0.42857142857142, 0.5, 0.55, 0.6, 0.625, 0.66666, 0.777777, 0.75, 0.7, 0.8, 0.83333333333333, 0.85714285714285, 0.875, 0.88888888888888, 0.9, 0.11111111111111, 0.22222222222222, 0.44444444444444, 0.71428571428571, 0.05

int main(int argc, char **argv){

    if (argc != 2) {
        handle(INVALID_INPUT);
        return INVALID_INPUT;
    }

    char *end = NULL;
    int base = (int)strtol(argv[1], &end, 10);
    if (end == argv[1] || *end != '\0' || base > 36 || base < 2){
        handle(INVALID_INPUT);
        return INVALID_INPUT;
    }

    Array res = {0, COUNTER, NULL};
    res.data = (double*)malloc(sizeof(double) * res.capacity);
    if (res.data == NULL) {
        handle(MEMORY_ALLOCATING_ERROR);
        return MEMORY_ALLOCATING_ERROR;
    }

    ReturnCode status = ifThen(&res, base, COUNTER, ARGS);
    if (status != OK) {
        handle(status);
        free(res.data);
        return status;
    }
    printf("Final fractions in the %d number system: \n", base);
    for (int i = 0; i < res.size; i++) {
        printf("%lf\n", res.data[i]);
    }
    free(res.data);
    return OK;
}