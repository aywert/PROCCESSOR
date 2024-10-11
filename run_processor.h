#ifndef PROCCESSOR
#define PROCCESSOR

enum cycle_status
{
    DO   = 1,
    STOP = 0,
};

#include"STACK\stack_functions.h"
#include"assembler.h"
int run_processor(int* instructions);
const double pi =  3.1415926535;


#endif