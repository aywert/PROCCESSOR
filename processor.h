#ifndef STACK_FUNC
#define STACK_FUNC
    #include"STACK\stack_functions.h"
#endif

#ifndef PROCCESSOR
#define PROCCESSOR

const int n_registers = 8;
const int last_register = -1;
const int size_RAW = 1024;
const double pi =  3.1415926535;

enum push_reg
{
    push_f_con  = 1,
    push_f_reg  = 2,
};

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
    FILE* output_bin;
    struct massive instructions;
    int ip;
    struct my_stack* stk;
    struct my_stack* adr_stk;
    struct massive RAW;
    double* registers;
};

int processor_init(struct SPU* processor, struct my_stack* stk, struct my_stack* adr_stk, int argc, char *argv[]);
int run_processor(struct SPU* processor);
int processor_dtor(struct SPU* processor);


#endif