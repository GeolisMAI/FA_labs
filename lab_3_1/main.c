#include <stdio.h>
#include "function.h"

int main() {
    unsigned value;
    int r;
    char res[33];

    printf("Enter the value: ");
    if (scanf("%u", &value) != 1) {
        printf("Invalid input for value.\n");
        return 1;
    }

    printf("Enter the base (base must be in range(1, 5)): ");
    if (scanf("%d", &r) != 1) {
        printf("Invalid input for base.\n");
        return 1;
    }

    if (convert_base(value, r, res) == -1) {
        printf("Error: base must be between 1 and 5.\n");
        return 1;
    }

    printf("Result in base %d: %s\n", r, res);
    return 0;
}