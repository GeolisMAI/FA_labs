#include <stdio.h>
#include <string.h>
#include "function.h"
#include "status_codes.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Incorrect count of arguments\n");
        return INCORRECT_COUNT_INPUT;
    }

    // Проверяем, не один ли это и тот же файл
    int same_file = (strcmp(argv[1], argv[2]) == 0);
    
    // Открываем входной файл для чтения
    FILE *inp = fopen(argv[1], "r");
    if (inp == NULL) {
        printf("File is not open\n");
        return ERROR_OPEN_FILE;
    }

    // Читаем данные ВСЕ в память
    char strs[1024][256];
    int count_nums = read_file(inp, strs);
    fclose(inp);  // Закрываем входной файл сразу после чтения
    
    if (count_nums < 0) {
        printf("Error reading file\n");
        return INCORRECT_INPUT;
    }

    // Теперь открываем выходной файл для записи
    // Если это тот же файл, он будет очищен, но данные уже в памяти
    FILE *outp = fopen(argv[2], "w");
    if (outp == NULL) {
        printf("Output file is not open\n");
        return ERROR_OPEN_FILE;
    }

    // Обрабатываем данные
    int bases[1024];
    int dec_nums[1024];
    int overflow_count = 0;
    
    for (int i = 0; i < count_nums; ++i) {
        int numbers = find_number_system(strs[i]);
        bases[i] = numbers;
        
        int error = 0;
        int dec_number = to_dec(strs[i], numbers, &error);
        
        if (error) {
            dec_nums[i] = -1;
            overflow_count++;
            fprintf(stderr, "Warning: Number '%s' (base %d) is too large or invalid\n", 
                    strs[i], numbers);
        } else {
            dec_nums[i] = dec_number;
        }
    }
    
    if (overflow_count > 0) {
        fprintf(stderr, "Total numbers with overflow: %d\n", overflow_count);
    }

    // Записываем результаты
    if (write_file(outp, strs, bases, dec_nums, count_nums) != OK) {
        printf("Error writing to file\n");
    }

    fclose(outp);
    return 0;
}