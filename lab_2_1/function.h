#pragma once
#include <stdbool.h>
#include <stdio.h>

typedef enum {
    OK,
    INVALID_INPUT,
    MEMORY_ALLOCATING_ERROR,
} ReturnCode;

typedef struct {
    long numer;
    long denumer;
} Fraction;

typedef struct {
    int size;
    int capacity;
    double *data;
} Array;

void handle(ReturnCode status);
long gcd(long a, long b);
Fraction dTF(double num);
bool check(Fraction f, int base);
int ifThen(Array *res, int base, int cnt, ...);