#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

int main(){
    char s[1000];
    scanf("%999[^\n]", s);
    printf("%d\n", check_brackets(s));
    return 0;
}