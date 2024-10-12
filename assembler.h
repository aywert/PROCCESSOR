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
    CMD_ADD      = 1<<4,
    CMD_SUBTRACT = 2<<4,
    CMD_DIVIDE   = 3<<4,
    CMD_MULTIPLY = 4<<4,
    CMD_SIN      = 5<<4,
    CMD_COS      = 6<<4,
    CMD_SQRT     = 7<<4,
};

enum go_to
{
    CMD_JA  = 1<<8,
    CMD_JAE = 2<<8,
    CMD_JB  = 3<<8,
    CMD_JBE = 4<<8,
    CMD_JE  = 5<<8,
    CMD_JNE = 6<<8,
    CMD_JMP = 7<<8,
};



const int instruct_size = 100;
int* assembler(FILE* input_file, FILE* output_file);

#endif