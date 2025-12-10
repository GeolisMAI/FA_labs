#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

static int char_to_val(char ch) {
    if (ch >= '0' && ch <= '9') return ch - '0';
    if (ch >= 'A' && ch <= 'Z') return ch - 'A' + 10;
    return -1;
}

static char val_to_char(int val) {
    const char *digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return digits[val];
}

ErrorCode str_to_int(const char *str, int base, long long *out) {
    if (!str || !out) return ERROR_NULL_POINTER;
    if (base < MIN_BASE || base > MAX_BASE) return ERROR_INVALID_BASE;

    int sign = 1;
    size_t i = 0;
    if (str[i] == '-') { sign = -1; i++; }
    else if (str[i] == '+') i++;

    if (str[i] == '\0') return ERROR_INVALID_INPUT;

    long long result = 0;
    for (; str[i]; i++) {
    int val = char_to_val(str[i]);
    if (val < 0 || val >= base)
        return ERROR_INVALID_INPUT;

        if (result > (INT64_MAX - val) / base)
            return ERROR_CONVERSION_FAILED;

        result = result * base + val;
    }

    *out = result * sign;
    return ERROR_OK;
}

ErrorCode int_to_str(long long value, int base, char *buffer, size_t buf_size) {
    if (!buffer) return ERROR_NULL_POINTER;
    if (base < MIN_BASE || base > MAX_BASE) return ERROR_INVALID_BASE;

    char temp[TEMP_BUFFER];
    size_t i = 0;
    int negative = value < 0;
    unsigned long long u = negative ? (unsigned long long)(-value) : (unsigned long long)value;

    do {
        temp[i++] = val_to_char(u % (unsigned long long)base);
        u /= (unsigned long long)base;
    } while (u > 0);

    if (negative) temp[i++] = '-';
    if (i + 1 > buf_size) return ERROR_BUFFER_TOO_SMALL;

    for (size_t j = 0; j < i; j++)
        buffer[j] = temp[i - j - 1];
    buffer[i] = '\0';
    return ERROR_OK;
}

ErrorCode read_base(int *base) {
    if (!base) return ERROR_NULL_POINTER;
    printf("Enter base (%d-%d): ", MIN_BASE, MAX_BASE);
    if (scanf("%d", base) != 1 || *base < MIN_BASE || *base > MAX_BASE) {
        while (getchar() != '\n');
        return ERROR_INVALID_BASE;
    }
    while (getchar() != '\n');
    return ERROR_OK;
}

ErrorCode read_line(char **out_str) {
    if (!out_str) return ERROR_NULL_POINTER;
    char buf[MAX_LINE_LENGTH];

    if (!fgets(buf, sizeof(buf), stdin))
        return ERROR_INVALID_INPUT;

    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') buf[len - 1] = '\0';

    *out_str = malloc(strlen(buf) + 1);
    if (!*out_str) return ERROR_MEMORY_FAILED;
    strcpy(*out_str, buf);
    return ERROR_OK;
}

ErrorCode is_stop(const char *str) {
    if (!str) return ERROR_NULL_POINTER;
    return strcmp(str, "Stop") == 0 ? ERROR_STOP_INPUT : ERROR_OK;
}

ErrorCode validate_number(const char *str, int base) {
    if (!str || base < MIN_BASE || base > MAX_BASE)
        return ERROR_INVALID_INPUT;

    size_t i = 0;
    if (str[0] == '-' || str[0] == '+') i++;

    if (str[0] == '-' && str[1] == '0' && str[2] == '\0') 
    return ERROR_INVALID_INPUT;

    for (; str[i]; i++) {
        char c = str[i];

        if (c >= 'a' && c <= 'z')
            c -= 32;

        int val = char_to_val(c);
        if (val < 0 || val >= base)
            return ERROR_INVALID_INPUT;
    }

    return ERROR_OK;
}


void print_in_bases(long long value, int original_base, const int *bases, size_t num_bases) {
    char buf[TEMP_BUFFER];
    printf("\nMax absolute number (base %d): ", original_base);
    if (int_to_str(value, original_base, buf, sizeof(buf)) == ERROR_OK)
        printf("%s\n", buf);
    else
        printf("Conversion error.\n");

    for (size_t i = 0; i < num_bases; i++) {
        if (int_to_str(value, bases[i], buf, sizeof(buf)) == ERROR_OK)
            printf("Base %d: %s\n", bases[i], buf);
    }
}