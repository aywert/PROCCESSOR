#include"run_processor.h"

int run_processor(int* instructions)
{
    my_stack stk = {};
    MY_STACK_CTOR(&stk, 10);
    cycle_status run = DO;

    int ip = 0;
     
    while(run){

    stack_elem_t x_1 = 0;
    stack_elem_t x_2 = 0;
    stack_elem_t output = 0;

    switch(instructions[ip])
    {
    case CMD_PUSH:
        MY_STACK_PUSH(&stk, instructions[++ip]);
        break;

    case CMD_ADD:
        MY_STACK_POP(&stk, &x_1);
        MY_STACK_POP(&stk, &x_2);
        MY_STACK_PUSH(&stk, x_1 + x_2);
        break;

    case CMD_SUBTRACT:
        MY_STACK_POP(&stk, &x_1);
        MY_STACK_POP(&stk, &x_2);
        MY_STACK_PUSH(&stk, x_2 - x_1);
        break;

    case CMD_DIVIDE:
        MY_STACK_POP(&stk, &x_1);
        MY_STACK_POP(&stk, &x_2);
        MY_STACK_PUSH(&stk, x_2 / x_1);
        break;

    case CMD_SIN:
        MY_STACK_POP(&stk, &x_1);
        MY_STACK_PUSH(&stk, sin((pi/180)*x_1));
        break;
    
    case CMD_COS:
        MY_STACK_POP(&stk, &x_1);
        MY_STACK_PUSH(&stk, cos((pi/180)*x_1));
        break;

    case CMD_SQRT:
        MY_STACK_POP(&stk, &x_1);
        MY_STACK_PUSH(&stk, sqrt(x_1));
        break;


    case CMD_MULTIPLY:
        MY_STACK_POP(&stk, &x_1);
        MY_STACK_POP(&stk, &x_2);
        MY_STACK_PUSH(&stk, x_2 * x_1);
        break;
    
    case CMD_INPUT:
        printf(BLUE("Please enter a number: "));
        scanf("%lg", &x_1); 
        break;
    
    case CMD_OUTPUT:
        MY_STACK_POP(&stk, &output);
        printf(YELLOW("Answer is %lg\n"), output); 
        break;

    case CMD_HAULT:
        printf(GREEN("PROGRAMM COMPLETED\n"));
        run = STOP;
        break;
    
    default:
        printf(RED("SNTXERR: %d"), instructions[ip]); run = STOP;
        break;
    }

    ip++;}

return 0;

}

