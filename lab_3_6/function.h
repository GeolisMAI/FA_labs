#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdbool.h>

struct Item{
    char data;
    struct Item* prev;
};

typedef struct{
    struct Item* top;
    int size;
} stack;

void Create(stack* s);
bool Empty(stack* s);
int Size(stack* s);
bool Push(stack* s, char t);
bool Pop(stack* s);
char Top(stack* s);
void Destroy(stack* s);

int check_brackets(const char * str);

#endif