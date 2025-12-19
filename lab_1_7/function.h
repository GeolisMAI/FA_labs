#pragma once

int find_number_system(const char* num);
int to_dec(const char* num, int base, int* error_flag);

int read_file(FILE* file, char buffer[][256]);
int write_file(FILE* file, char buffer[][256], int* bases, int* dec_numbers, int size);