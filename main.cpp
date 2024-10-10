#include"../STACK/ASSERT.h"
#include"../STACK/stack_functions.h"
#include"string.h"

int run_proccessor(FILE* name);

enum cycle_status
{
    DO   = 1,
    STOP = 0,
};

enum op_comands
{
    CMD_PUSH     =  1,
    CMD_OUTPUT   =  2,
    CMD_OUTPUT   =  3,
    CMD_HAULT    =  4,
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

int main()
{
    FILE* name = fopen("code_instruct.txt", "r");
    run_proccessor(name);
}

int run_proccessor(FILE* name)
{
    my_stack stk = {};
    MY_STACK_CTOR(&stk, 10);
    int run = DO;
    while(run)
    {
        /*static int i = 0;
        i++;
        printf("times in cycle = %d\n", i);*/
        char cmd[50] = "";
        fscanf(name, "%s", cmd);
        if (strcmp(cmd, "push") == 0)
        {
            int arg = 0;
            fscanf(name, "%d", &arg);
            MY_STACK_PUSH(&stk, arg);
            continue;
        }

        if (strcmp(cmd, "add") == 0)
        {
            stack_elem_t x_1 = 0;
            stack_elem_t x_2 = 0;
            MY_STACK_POP(&stk, &x_1);
            MY_STACK_POP(&stk, &x_2);
            MY_STACK_PUSH(&stk, x_1 + x_2);
            continue;
        }

        if (strcmp(cmd, "sub") == 0)
        {
            stack_elem_t x_1 = 0;
            stack_elem_t x_2 = 0;
            MY_STACK_POP(&stk, &x_1);
            MY_STACK_POP(&stk, &x_2);
            MY_STACK_PUSH(&stk, x_2 - x_1);
            continue;
        }

        if (strcmp(cmd, "div") == 0)
        {
            stack_elem_t x_1 = 0;
            stack_elem_t x_2 = 0;
            MY_STACK_POP(&stk, &x_1);
            MY_STACK_POP(&stk, &x_2);
            MY_STACK_PUSH(&stk, x_2 / x_1);
            continue;
        }

        if (strcmp(cmd, "mul") == 0)
        {
            stack_elem_t x_1 = 0;
            stack_elem_t x_2 = 0;
            MY_STACK_POP(&stk, &x_1);
            MY_STACK_POP(&stk, &x_2);
            MY_STACK_PUSH(&stk, x_2 * x_1);
            continue;
        }

        if (strcmp(cmd, "out") == 0)
        {
            stack_elem_t output = 0;
            MY_STACK_POP(&stk, &output);
            printf(YELLOW("Answer is %lg\n"), output); 
            continue;       
        }

        if (strcmp(cmd, "hlt") == 0)
        {
            printf(GREEN("PROGRAMM COMPLETED\n"));
            run = STOP;
        }

        else{printf(RED("SNTXERR: %s"), cmd); run = STOP;}
    }
}