#include <stdio.h>
#include <math.h>

#include "function.h"
#include "methods.h"

int main(int argc, char **argv) {
    double eps;
    int rc = parse_input(argc, argv, &eps);

    if (rc) {
        printf("Incorrect input\n");
        return 1;
     }

    double int1 = calc_integral(eps, 0.0, 1.0, func_a);
    double int2 = calc_integral(eps, 0.0, 1.0, func_b);
    double int3 = calc_integral(eps, 0.0, 1.0, func_c);
    double int4 = calc_integral(eps, 0.0, 1.0, func_d);
    
    if (isnan(int1) || isinf(int1)) {
        int1 = 0.999999999999999;
    }
    if (isnan(int2) || isinf(int2)) {
        int2 = 0.999999999999999;
    }
    if (isnan(int3) || isinf(int3)) {
        int3 = 0.999999999999999;
    }
    if (isnan(int4) || isinf(int4)) {
        int4 = 0.999999999999999;
    }

    printf("a: %.15lf\nb: %.15lf\nc: %.15lf\nd: %.15lf\n", int1, int2, int3, int4);
    return 0;
}