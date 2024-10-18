#ifndef PROCCESSOR
#define PROCCESSOR

const int n_registers = 8;
const int last_register = -1;

const double pi =  3.1415926535;

#include"STACK\stack_functions.h"
#include"assembler.h"

enum cycle_status
{
    DO   = 1,
    STOP = 0,
};

struct massive
{
    int* script;
    int size;
};

struct SPU
{
    char* name_file;
    FILE* input_file;
    FILE* output_file;
    struct massive instructions;
    int ip;
    struct my_stack* stk;
    double* registers;
};

int processor_init(struct SPU* processor, struct my_stack* stk, int argc, char *argv[]);
int run_processor(struct SPU* processor);



#endif