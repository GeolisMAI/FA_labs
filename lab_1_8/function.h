#ifndef SOLUTION_H
#define SOLUTION_H

#include <stddef.h>
#include <stdint.h>

#define MAX_LINE_LENGTH 128
#define MAX_BASE 36
#define MIN_BASE 2
#define TEMP_BUFFER 128

typedef enum {
    ERROR_OK = 0,
    ERROR_INVALID_INPUT,
    ERROR_MEMORY_FAILED,
    ERROR_INVALID_BASE,
    ERROR_CONVERSION_FAILED,
    ERROR_STOP_INPUT,
    ERROR_NULL_POINTER,
    ERROR_BUFFER_TOO_SMALL,
    ERROR_INPUT_TOO_LONG
} ErrorCode;

ErrorCode str_to_int(const char *str, int base, long long *out);
ErrorCode int_to_str(long long value, int base, char *buffer, size_t buf_size);

ErrorCode read_base(int *base);
ErrorCode read_line(char **out_str);
ErrorCode is_stop(const char *str);
ErrorCode validate_number(const char *str, int base);

void print_in_bases(long long value, int original_base, const int *bases, size_t num_bases);

#endif