#include "function.h"
#include <stdint.h>

void increment(uintptr_t* ptr) {
    int carry = 1;
    while (carry != 0) {
        int new_carry = *ptr & carry;
        *ptr ^= carry;
        carry = new_carry << 1;
    }
}

void decrement(uintptr_t* ptr) {
    int borrow = 1;
    while (borrow != 0) {
        int new_borrow = (~(*ptr)) & borrow;
        *ptr ^= borrow;
        borrow = new_borrow << 1;
    }
}



int convert_base(unsigned number, int r, char* res) {
    if (r < 1 || r > 5) {
        return -1;
    }

    char* p = res;
    if (number == 0) {
        *p = '0';
        uintptr_t new_p = (uintptr_t)p;
        increment(&new_p);
        p = (char*)new_p;
        *p = '\0';
        return 0;
    }

    char all_digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUV";

    unsigned mask = ~(~0 << r);
    while (number > 0) {
        unsigned digit = number & mask;
        char symbol = all_digits[digit];

        *p = symbol;
        uintptr_t new_p = (uintptr_t)p;
        increment(&new_p);
        p = (char*)new_p;

        number >>= r;
    }

    *p = '\0';

    char *left = res;

    uintptr_t new_p = (uintptr_t)p;
    decrement(&new_p);
    p = (char*)new_p;
    char *right = p;
    while (left < right) {
        char temp = *left;
        *left = *right;
        *right = temp;

        uintptr_t new_p = (uintptr_t)left;
        increment(&new_p);
        left = (char*)new_p;

        new_p = (uintptr_t)right;
        decrement(&new_p);
        right = (char*)new_p;
    }
    return 0;
}