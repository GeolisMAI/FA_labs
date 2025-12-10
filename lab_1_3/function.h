#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

void menu(const char* program_name);
int flag_q(double epsilon, double a, double b, double c);
int flag_m(int a, int b);
int flag_t(double epsilon, double a, double b, double c);
int validate_numbers(int count, char* numbers[]);

#endif