#include <stdio.h>
#include "status_codes.h"
#include "function.h"

int main(int argc, char **argv) {
    Opts opt;
    FILE *input = NULL;
    FILE *output = NULL;

    int rc = GetOpts(argc, argv, &opt, &input, &output);
    print_errors(rc);

    callback_t handlers[] = {
        flag_d,
        flag_i,
        flag_s,
        flag_a
    };

    handlers[opt](input, output);

    if (input) fclose(input);
    if (output) fclose(output);
    return 0;
}