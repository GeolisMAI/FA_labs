#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "function.h"

void Create(stack* s){
    s->top = 0;
    s->size = 0;
}

bool Empty(stack* s){
    return s->top == 0;
}

int Size(stack* s){
    return s->size;
}

bool Push(stack* s, char t){
    struct Item* i = malloc(sizeof(struct Item));
    if (!i){
        return false;
    }
    i->data = t;
    i->prev = s->top;
    s->top = i;
    s->size++;
    return true;
}

bool Pop(stack* s){
    if (Empty(s)){
        return false;
    }
    struct Item* i = s->top;
    s->top = s->top->prev;
    s->size--;
    free(i);
    return true;
}

char Top(stack* s){
    if (s->top){
        return s->top->data;
    }
    return '\0';
}

void Destroy(stack* s){
    while (s->top){
        struct Item* i = s->top;
        s->top = s->top->prev;
        free(i);
    }
    s->top = 0;
    s->size = 0;
}

int check_brackets(const char * str){
    stack s;
    Create(&s);
    const char left_bracket[] = "([{<";
    const char right_bracket[] = ")]}>";
    int flag = 0;
    int n = strlen(str);
    
    for (int i = 0; i < n; i++){
        if (strchr(left_bracket, str[i]) != NULL){
            Push(&s, str[i]);
        } else if (strchr(right_bracket, str[i]) != NULL){
            if (Empty(&s)){
                Destroy(&s);
                return 0;
            }
            char last_bracket = Top(&s);
            char* left_ptr = strchr(left_bracket, last_bracket);
            if (left_ptr == NULL) {
                Destroy(&s);
                return 0;
            }
            int index = left_ptr - left_bracket;
            if (str[i] == right_bracket[index]) {
                Pop(&s);
            } else {
                Destroy(&s);
                return 0;
            }
        }
    }
    flag = Empty(&s);
    Destroy(&s);
    return flag;
}