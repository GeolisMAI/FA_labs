#pragma once

#include <stdio.h>
#include "status_codes.h"

typedef int (*callback_t)(FILE *inp, FILE *outp);

int flag_d(FILE *inp, FILE *outp);
int flag_i(FILE *inp, FILE *outp);
int flag_s(FILE *inp, FILE *outp);
int flag_a(FILE *inp, FILE *outp);

int GetOpts(int argc, char **argv, Opts *option, FILE **input, FILE **output);
void print_errors(int error_code);