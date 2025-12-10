#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "function.h"

void menu(const char* program_name) {
    printf("Usage: %s <flag> <parameters>\n", program_name);
    printf("Available flags:\n");
    printf("'-q <epsilon> <a> <b> <c>' - solution of a quadratic equation\n");
    printf("'-m <a> <b>' - checking the multiplicity of numbers\n");
    printf("'-t <epsilon> <a> <b> <c>' - checking a right triangle\n");
}

int validate_numbers(int count, char* numbers[]) {
    for (int i = 0; i < count; i++) {
        char* endptr;
        strtod(numbers[i], &endptr);
        if (endptr == numbers[i] || *endptr != '\0') {
            fprintf(stderr, "Error: '%s' is not a valid number.\n", numbers[i]);
            return 1;
        }
    }
    return 0;
}

void solve_quadratic(double epsilon, double a, double b, double c) {
    if (fabs(a) < epsilon) {
        if (fabs(b) < epsilon) {
            if (fabs(c) < epsilon) {
                printf("An infinite number of solutions\n");
            } else {
                printf("No solutions\n");
            }
        } else {
            double x = -c / b;
            printf("x = %g\n", x);
        }
        return;
    }
    
    double discriminant = b * b - 4 * a * c;
    
    if (fabs(discriminant) < epsilon) {
        double x = -b / (2 * a);
        printf("One root: x = %g\n", x);
    } else if (discriminant > 0) {
        double x1 = (-b + sqrt(discriminant)) / (2 * a);
        double x2 = (-b - sqrt(discriminant)) / (2 * a);
        printf("Two roots: x1 = %g, x2 = %g\n", x1, x2);
    } else {
        printf("Complex roots\n");
    }
}

int flag_q(double epsilon, double a, double b, double c) {
    printf("Solutions of a quadratic equation with coefficients:\n");
    printf("a = %g, b = %g, c = %g\n", a, b, c);
    solve_quadratic(epsilon, a, b, c);
    printf("\n");
    double coefficients[3] = {a, b, c};
    bool used[3][3][3] = {false};
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j == i) continue;
            for (int k = 0; k < 3; k++) {
                if (k == i || k == j) continue;
                
                if (!used[i][j][k]) {
                    used[i][j][k] = true;
                    printf("Permutation: a = %g, b = %g, c = %g\n", 
                           coefficients[i], coefficients[j], coefficients[k]);
                    solve_quadratic(epsilon, coefficients[i], coefficients[j], coefficients[k]);
                    printf("\n");
                }
            }
        }
    }
    
    return 0;
}

int flag_m(int a, int b) {
    if (b == 0) {
        fprintf(stderr, "Error: The second number cannot be zero\n");
        return 1;
    }
    
    if (a % b == 0) {
        printf("%d is a multiple of %d\n", a, b);
    } else {
        printf("%d is not a multiple of %d\n", a, b);
    }
    
    return 0;
}

int flag_t(double epsilon, double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        printf("Numbers cannot be sides of a triangle\n");
        return 1;
    }
    
    if (a + b <= c || a + c <= b || b + c <= a) {
        printf("Numbers cannot be sides of a triangle (the triangle inequality is violated)\n");
        return 1;
    }
    
    double sides[3] = {a, b, c};
    bool is_right_triangle = false;
    
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            int k = 3 - i - j; 
            
            double side1 = sides[i];
            double side2 = sides[j];
            double hypotenuse = sides[k];
            
            if (fabs(side1 * side1 + side2 * side2 - hypotenuse * hypotenuse) < epsilon) {
                printf("The numbers %g, %g, and %g can be the sides of a right triangle\n", 
                       a, b, c);
                printf("(where %g^2 + %g^2 = %g^2)\n", side1, side2, hypotenuse);
                is_right_triangle = true;
                break;
            }
        }
        if (is_right_triangle) break;
    }
    
    if (!is_right_triangle) {
        printf("The numbers %g, %g, and %g cannot be the sides of a right triangle\n", a, b, c);
    }
    
    return 0;
}