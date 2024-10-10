#include"STACK/ASSERT.h"
#include"STACK/stack_functions.h"
#include"assembler.h"

int run_proccessor(int* instructions);

enum cycle_status
{
    DO   = 1,
    STOP = 0,
};

int main(int argc, char *argv[])
{
    if(argc < 2)
        return STOP;
    
    FILE* file = fopen(argv[argc-1], "r");
    int* instructions = assembler(file);

    /*for (int i = 0; i <= 12; i++)
    {
        if (instructions[i] == CMD_PUSH)
            printf("%d ", instructions[i]);
        else
            printf("%d\n", instructions[i]);
    }
    printf("___________________\n");*/

    run_proccessor(instructions); return 0; 
    
}

int run_proccessor(int* instructions)
{
    my_stack stk = {};
    MY_STACK_CTOR(&stk, 10);
    cycle_status run = DO;

    int ip = 0; 
    while(run)
    {
        if (instructions[ip] == CMD_PUSH)
        {
            MY_STACK_PUSH(&stk, instructions[++ip]);
            ip++;
            continue;
        }

        if (instructions[ip] == CMD_ADD)
        {
            stack_elem_t x_1 = 0;
            stack_elem_t x_2 = 0;
            MY_STACK_POP(&stk, &x_1);
            MY_STACK_POP(&stk, &x_2);
            MY_STACK_PUSH(&stk, x_1 + x_2);
            ip++;
            continue;
        }

        if (instructions[ip] == CMD_SUBTRACT)
        {
            stack_elem_t x_1 = 0;
            stack_elem_t x_2 = 0;
            MY_STACK_POP(&stk, &x_1);
            MY_STACK_POP(&stk, &x_2);
            MY_STACK_PUSH(&stk, x_2 - x_1);
            ip++;
            continue;
        }

        if (instructions[ip] == CMD_DIVIDE)
        {
            stack_elem_t x_1 = 0;
            stack_elem_t x_2 = 0;
            MY_STACK_POP(&stk, &x_1);
            MY_STACK_POP(&stk, &x_2);
            MY_STACK_PUSH(&stk, x_2 / x_1);
            ip++;
            continue;
        }

        if (instructions[ip] == CMD_MULTIPLY)
        {
            stack_elem_t x_1 = 0;
            stack_elem_t x_2 = 0;
            MY_STACK_POP(&stk, &x_1);
            MY_STACK_POP(&stk, &x_2);
            MY_STACK_PUSH(&stk, x_2 * x_1);
            ip++;
            continue;
        }

        if (instructions[ip] == CMD_OUTPUT)
        {
            stack_elem_t output = 0;
            MY_STACK_POP(&stk, &output);
            printf(YELLOW("Answer is %lg\n"), output); 
            ip++;
            continue;       
        }

        if (instructions[ip] == CMD_HAULT)
        {
            printf(GREEN("PROGRAMM COMPLETED\n"));
            run = STOP;
        }

        else{printf(RED("SNTXERR: %d"), instructions[ip]); run = STOP;}
    }
    return 0;
}

