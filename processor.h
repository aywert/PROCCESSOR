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

struct label
{
    int pc;
    char label[];
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
    double* registers;
};

int free_label(label* table_labels);
int is_label(char* cmd);
int find_label(label* table_labels, char* label);
label* labels_init(void);
int labels_dtor(label* processor_labels);

int processor_init(struct SPU* processor, struct my_stack* stk, int argc, char *argv[]);
int run_processor(struct SPU* processor);
int processor_dtor(struct SPU* processor);


#endif