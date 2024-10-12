#include"run_processor.h"

int run_processor(int* instructions)
{
    struct SPU processor = {};
    struct my_stack stk = {}; MY_STACK_CTOR(&stk, 10);

    processor.stk = &stk;
    
    cycle_status run = DO;
    while(run){

        stack_elem_t x_1 = 0;
        stack_elem_t x_2 = 0;
        stack_elem_t output = 0;
        int tempor_ip = 0;

        switch(instructions[processor.ip])
        {
          case CMD_PUSH:
            MY_STACK_PUSH(&stk, instructions[++processor.ip]);
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
            MY_STACK_PUSH(&stk, x_1);
            break;
        
        case CMD_OUTPUT:
            MY_STACK_POP(&stk, &output);
            printf(YELLOW("Answer is %lg\n"), output); 
            break;
        //////////////////////
        case CMD_JA:
            MY_STACK_POP(&stk, &x_1);
            MY_STACK_POP(&stk, &x_2);
            if (x_1 - x_2 < 0)
            {
                tempor_ip = processor.ip + 1;
                processor.ip = instructions[tempor_ip] - 1;
            }
            break;
        
        case CMD_JAE:
            MY_STACK_POP(&stk, &x_1);
            MY_STACK_POP(&stk, &x_2);
            if (compare_double(x_1, x_2) || (x_1 - x_2 > 0))
            {
                tempor_ip = processor.ip + 1;
                processor.ip = instructions[tempor_ip] - 1;
            }
            break;
        
        case CMD_JB:
            MY_STACK_POP(&stk, &x_1);
            MY_STACK_POP(&stk, &x_2);
            if (x_1 - x_2 > 0)
            {
                tempor_ip = processor.ip + 1;
                processor.ip = instructions[tempor_ip] - 1;
            }
            break;

        case CMD_JBE:
            MY_STACK_POP(&stk, &x_1);
            MY_STACK_POP(&stk, &x_2);
            if (compare_double(x_1, x_2) || (x_1 - x_2 < 0))
            {
                tempor_ip = processor.ip + 1;
                processor.ip = instructions[tempor_ip] - 1;
            }
            break;

        case CMD_JE:
            MY_STACK_POP(&stk, &x_1);
            MY_STACK_POP(&stk, &x_2);
            if (compare_double(x_1, x_2))
            {
                tempor_ip = processor.ip + 1;
                processor.ip = instructions[tempor_ip] - 1;
            }
            break;

        case CMD_JNE:
            MY_STACK_POP(&stk, &x_1);
            MY_STACK_POP(&stk, &x_2);
            if (!compare_double(x_1, x_2))
            {
                tempor_ip = processor.ip + 1;
                processor.ip = instructions[tempor_ip] - 1;
            }
            break;

        case CMD_JMP:
            tempor_ip = processor.ip + 1;
            processor.ip = instructions[tempor_ip] - 1;
            break;
        //////////////////////////////
        case CMD_HAULT:
            printf(GREEN("PROGRAMM COMPLETED\n"));
            run = STOP;
            break;
        
        default:
            printf(RED("SNTXERR_PROCESSOR: %d"), instructions[processor.ip]); 
            run = STOP;
            break;
        }

    processor.ip++;
    }

    return 0;

}

