#pragma once

#include <stdint.h>

void increment(uintptr_t* ptr);
void decrement(uintptr_t* ptr);
int convert_base(unsigned number, int r, char* res);