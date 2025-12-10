#ifndef OPERATIONS_H
#define OPERATIONS_H

void menu();
int bad_input(int argc, char* argv[], long* x, char* flag);
int flag_h(long x);
int flag_p(long x);
int flag_s(long x);
int flag_a(long x);
int flag_f(long x);
int flag_e(int max_degree, long long table[][10]);

#endif