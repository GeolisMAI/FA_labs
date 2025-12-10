#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "function.h"
#include <limits.h>

#define ERROR_INPUT 1
#define GOOD 0

void menu() {
    printf("Enter a number and argument using '-' or '/'\nArguments:\n");
    printf("'-h' - output to the console natural numbers up to and including 100 that are multiples of x\n");
    printf("'-p' - check if x is a prime number; check if x is a composite number\n");
    printf("'-s' - divide the number x into separate digits of the base 16 number system\n");
    printf("'-e' - display a table of powers of bases from 1 to 10\n");
    printf("'-a' - calculate the sum of all natural numbers from 1 to x\n");
    printf("'-f' - calculate the factorial of x\n");
}

int bad_input(int argc, char* argv[], long* x, char* flag) {
    if (argc != 3) {
        fprintf(stderr, "Error: Expected 2 arguments, but received %d\n", argc - 1);
        return 1;
    }   
    strncpy(flag, argv[2], 2);
    flag[2] = '\0';    
    char* endptr;
    *x = strtol(argv[1], &endptr, 10); 
    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: '%s' is not a valid number\n", argv[1]);
        return 1;
    }  
    return 0;
}

int flag_h(long x) {
    if (x == 0) {
        printf("There are no divisible numbers: the divisor is zero\n");
        return 0;
    }
    
    long abs_x = labs(x);
    if (abs_x > 100) {
        printf("No natural number up to 100 is divisible by %ld\n", x);
        return 0;
    }
    
    bool found = false;
    printf("Numbers divisible by %ld up to 100:\n", x);
    
    for (long i = abs_x; i <= 100; i += abs_x) {
        printf("%ld ", i);
        found = true;
    }
    
    if (!found) {
        printf("No natural number up to 100 is divisible by %ld\n", x);
    } else {
        printf("\n");
    }
    
    return 0;
}

int flag_p(long x) {
    if (x < 2) {
        printf("%ld is neither simple nor compound\n", x);
        return 0;
    }
    
    if (x == 2) {
        printf("%ld is simple\n", x);
        return 0;
    }
    
    if (x % 2 == 0) {
        printf("%ld is composite\n", x);
        return 0;
    }
    
    bool is_prime = true;
    for (long i = 3; i * i <= x; i += 2) {
        if (x % i == 0) {
            is_prime = false;
            break;
        }
    }
    
    if (is_prime) {
        printf("%ld is simple\n", x);
    } else {
        printf("%ld is composite.\n", x);
    }
    
    return 0;
}

int flag_s(long x) {
    if (x == 0) {
        printf("0\n");
        return 0;
    }
    
    char hex_digits[16];
    int index = 0;
    long temp = labs(x);
    
    while (temp > 0) {
        int digit = temp % 16;
        hex_digits[index++] = (digit < 10) ? ('0' + digit) : ('A' + digit - 10);
        temp /= 16;
    }
    
    printf("Hexadecimal digits %ld: ", x);
    for (int i = index - 1; i >= 0; i--) {
        printf("%c ", hex_digits[i]);
    }
    printf("\n");
    
    return 0;
}

int flag_e(int max_degree, long long table[][10]) {
    if ((max_degree <= 0) || (max_degree > 10)) {
        return ERROR_INPUT;
    }

    for (int degree = 1; degree <= max_degree; degree++) {
        for (int footing = 1; footing <= 10; footing++) {
            long long mean = 1;
            for (int i = 0; i < degree; i++) {
                mean *= footing;
            }
            table[degree - 1][footing - 1] = mean;
        }
    }

    return GOOD;
}

int flag_a(long x) {
    if (x < 1) {
        fprintf(stderr, "Error: the -a flag must be a positive natural number\n");
        return 1;  
    }
    
    if (x > 0 && (unsigned long long)x > (ULLONG_MAX - 1) / 2) {
        fprintf(stderr, "Error: The amount is too large to calculate\n");
        return 1;
    }
    
    unsigned long long sum = (unsigned long long)x * (x + 1) / 2;
    printf("Sum of natural numbers from 1 to %ld: %llu\n", x, sum);
    return 0;
}

int flag_f(long x) {
    if (x < 0) {
        fprintf(stderr, "Error: The factorial is not defined for negative numbers\n");
        return 1;
    }
    
    if (x == 0) {
        printf("Factorial 0: 1\n");
        return 0;
    }
    
    unsigned long long factorial = 1;
    
    for (long i = 1; i <= x; i++) {
        if (factorial > ULLONG_MAX / i) {
            fprintf(stderr, "Error: The factorial of %ld is too large to calculate\n", x);
            return 1;
        }
        factorial *= i;
    }
    
    printf("Factorial %ld: %llu\n", x, factorial);
    return 0;
}