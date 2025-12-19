#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

#include "status_codes.h"
#include "function.h"

#define BUFFER_SIZE 1024
#define STR_SIZE 256

int find_number_system(const char* num) {
    char base = '0';
    for (int i = 0; i < strlen(num); i++) {
        if (tolower(num[i]) >= 'a' && tolower(num[i]) <= 'z') {
            base = tolower(num[i]) > base ? tolower(num[i]) : base;
        } else if (num[i] >= '0' && num[i] <= '9') {
            base = num[i] > base ? num[i] : base;
        }
    }

    int res_base;
    if (base >= 'a' && base <= 'z') {
        res_base = base - 'a' + 11;
    } else {
        res_base = base - '0' + 1;
    }

    return res_base < 2 ? 2 : res_base;
}

int to_dec(const char* num, const int base, int* error_flag) {
    *error_flag = 0;
    if (base < 2 || base > 36) {
        *error_flag = 1;
        return 0;
    }
    unsigned long long acc = 0ULL;
    int i = 0;
    if (num[0] == '-') {
        i++;
    }
    if (num[i] == '\0') {
        return 0;
    }
    for (; num[i] != '\0'; i++) {
        char ch = num[i];
        unsigned long long digit;
        if (isdigit((unsigned char)ch)) {
            digit = (unsigned long long)(ch - '0');
        } else if (isalpha((unsigned char)ch)) {
            digit = (unsigned long long)(tolower((unsigned char)ch) - 'a' + 10);
        } else {
            continue;
        }
        if (digit >= (unsigned long long)base) {
            continue;
        }
        if (acc > ULLONG_MAX / (unsigned long long)base) {
            *error_flag = 1;
            return 0;
        }
        unsigned long long temp = acc * (unsigned long long)base;
        if (temp > ULLONG_MAX - digit) {
            *error_flag = 1;
            return 0;
        }
        acc = temp + digit;
    }
    if (acc > (unsigned long long)INT_MAX) {
        *error_flag = 1;
        return 0;
    }
    return (int)acc;
}

int read_file(FILE* file, char buffer[][256]) {
    int token_index = 0;
    int write_pos = 0;
    int in_token = 0;
    int has_nonzero = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF && token_index < BUFFER_SIZE) {
        if (isalnum(ch)) {
            if (!in_token) {
                in_token = 1;
                has_nonzero = 0;
                write_pos = 0;
            }

            if (ch != '0' || isalpha(ch)) {
                has_nonzero = 1;
            }

            if (has_nonzero || write_pos > 0) {
                if (write_pos < STR_SIZE - 1) {
                    buffer[token_index][write_pos++] = (char)ch;
                } else {
                    buffer[token_index][STR_SIZE - 1] = '\0';
                    token_index++;
                    in_token = 0;
                    write_pos = 0;
                    has_nonzero = 0;
                    while (isalnum(ch = fgetc(file))) {
                    }
                }
            }
        } else if (in_token) {
            if (write_pos == 0 || !has_nonzero) {
                buffer[token_index][0] = '0';
                buffer[token_index][1] = '\0';
            } else {
                buffer[token_index][write_pos] = '\0';
            }
            token_index++;
            in_token = 0;
            write_pos = 0;
            has_nonzero = 0;
        }
    }

    if (in_token && token_index < BUFFER_SIZE) {
        if (write_pos == 0 || !has_nonzero) {
            buffer[token_index][0] = '0';
            buffer[token_index][1] = '\0';
        } else {
            buffer[token_index][write_pos] = '\0';
        }
        token_index++;
    }

    return token_index;
}

int write_file(FILE* file, char buffer[][256], int* bases, int* dec_numbers, int size) {
    if (size <= 0) return OK;
    for (int i = 0; i < size; i++) {
        fprintf(file, "%s %d %d\n", buffer[i], bases[i], dec_numbers[i]);
    }
    return OK;
}