#ifndef ASSEMBLER
#define ASSEMBLER

#include<sys/stat.h>
#include"string.h"
#include"..\STACK\stack_functions.h"

enum op_comands
{
    CMD_PUSH     = 1,
    CMD_INPUT    = 2,
    CMD_OUTPUT   = 3,
    CMD_HAULT    = 4,
};

enum math_comands
{
    CMD_ADD      = 11,
    CMD_SUBTRACT = 12,
    CMD_DIVIDE   = 13,
    CMD_MULTIPLY = 14,
    CMD_SIN      = 15,
    CMD_COS      = 16,
    CMD_SQRT     = 17,
};

const int instruct_size = 100;
int* assembler(FILE* input_file, FILE* output_file);

#endif