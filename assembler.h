// #ifndef ASSERT_PROC
// #define ASSERT_PROC
//     #include"assert.h"
// #endif

#ifndef ASSEMBLER
#define ASSEMBLER

#include<sys/stat.h>
#include"string.h"

enum op_comands
{
    CMD_HAULT  = -1,
    CMD_PUSH   =  1,
    CMD_INPUT  =  2,
    CMD_OUTPUT =  3,
    CMD_POP    =  4,
    CMD_PUSHR  =  5,
    CMD_DRAW   =  6,
    CMD_CALL   =  7,
    CMD_RET    =  8,
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

const int size_cmd = 30;
const int instruct_size = 100;
const int size_label = 30;
int assembler(struct SPU* processor);

#endif