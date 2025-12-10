#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main(void) {
    int base;
    if (read_base(&base) != ERROR_OK) {
        printf("Invalid base!\n");
        return ERROR_INVALID_BASE;
    }

    long long max_value = 0;
    int first = 1;

    while (1) {
        printf("Enter number (or Stop): ");
        char *str = NULL;

        ErrorCode err = read_line(&str);
        if (err != ERROR_OK) {
            printf("Input error.\n");
            continue;
        }

        if (is_stop(str) == ERROR_STOP_INPUT) {
            free(str);
            break;
        }

        if (validate_number(str, base) != ERROR_OK) {
            printf("Invalid number for base %d.\n", base);
            free(str);
            continue;
        }

        long long value;
        if (str_to_int(str, base, &value) != ERROR_OK) {
            fprintf(stderr, "Number is too large or invalid for base %d.\n", base);
            free(str);
            continue;
        }

        free(str);

        if (first) {
            max_value = value;
            first = 0;
        } else if (llabs(value) > llabs(max_value)) {
            max_value = value;
        }
    }

    if (first) {
        printf("No numbers entered.\n");
        return ERROR_OK;
    }

    const int bases[] = {9, 18, 27, 36};
    print_in_bases(max_value, base, bases, 4);

    return ERROR_OK;
}