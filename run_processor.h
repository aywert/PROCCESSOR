#ifndef PROCCESSOR
#define PROCCESSOR

const int n_registers = 8;
const int last_register = -1;

enum cycle_status
{
    DO   = 1,
    STOP = 0,
};

struct SPU
{
    int* instructions;
    int ip;
    struct my_stack* stk;
    double* registers;
};

#include"STACK\stack_functions.h"
#include"assembler.h"
int run_processor(int* instructions);
const double pi =  3.1415926535;


#endif