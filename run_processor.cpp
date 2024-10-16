#include"run_processor.h"

int processor_init(struct SPU* processor, struct my_stack* stk, int argc, char *argv[])
{
  processor->name_file   = argv[argc-2];
  processor->input_file  = fopen(argv[argc-2], "r");
  processor->output_file = fopen(argv[argc-1], "w+");

  assembler(processor);

  MY_STACK_CTOR(stk, 10);
  
  double* registers = (double*)calloc(n_registers, sizeof(double));
  registers[n_registers - 1] = last_register;

  processor->stk = stk;
  processor->registers = registers;
}

int run_processor(struct SPU* processor)
{
  cycle_status run = DO;
  while(run){
  ///////////////////////////////////////////////////////////////////////////////////////
    for (int i = 0; i < processor->instructions.size; i++)
    {
      printf("%4X", i);
    }
    printf("\n");

    for (int i = 0; i < processor->instructions.size; i++)
    {
      printf("%4X", processor->instructions.script[i]);
    }
    printf("\n");

    for (int i = 0; i < processor->ip; i++)
    {
      printf("    ");
    }
    printf(RED("   %c"), 3);

    getchar();
    printf("\n\n");
//////////////////////////////////////////////////////////////////////////////////////////
    stack_elem_t x_1 = 0;
    stack_elem_t x_2 = 0;
    stack_elem_t output = 0;
    int tempor_ip = 0;
    
    switch(processor->instructions.script[processor->ip])
    {
      case CMD_PUSH:
        MY_STACK_PUSH(processor->stk, processor->instructions.script[++processor->ip]);
        break;

      case CMD_PUSHR:
        MY_STACK_PUSH(processor->stk, processor->registers[processor->instructions.script[++processor->ip]]);
        break;

      case CMD_ADD:
        MY_STACK_POP(processor->stk, &x_1);
        MY_STACK_POP(processor->stk, &x_2);
        MY_STACK_PUSH(processor->stk, x_1 + x_2);
        break;

      case CMD_SUBTRACT:
        MY_STACK_POP(processor->stk, &x_1);
        MY_STACK_POP(processor->stk, &x_2);
        MY_STACK_PUSH(processor->stk, x_2 - x_1);
        break;

      case CMD_DIVIDE:
        MY_STACK_POP(processor->stk, &x_1);
        MY_STACK_POP(processor->stk, &x_2);
        MY_STACK_PUSH(processor->stk, x_2 / x_1);
        break;

      case CMD_SIN:
        MY_STACK_POP(processor->stk, &x_1);
        MY_STACK_PUSH(processor->stk, sin((pi/180)*x_1));
        break;
    
      case CMD_COS:
        MY_STACK_POP(processor->stk, &x_1);
        MY_STACK_PUSH(processor->stk, cos((pi/180)*x_1));
        break;

      case CMD_SQRT:
        MY_STACK_POP(processor->stk, &x_1);
        MY_STACK_PUSH(processor->stk, sqrt(x_1));
        break;

      case CMD_MULTIPLY:
        MY_STACK_POP(processor->stk, &x_1);
        MY_STACK_POP(processor->stk, &x_2);
        MY_STACK_PUSH(processor->stk, x_2 * x_1);
        break;
    
      case CMD_INPUT:
        printf(BLUE("Please enter a number: "));
        scanf("%lg", &x_1); 
        MY_STACK_PUSH(processor->stk, x_1);
        break;
    
      case CMD_OUTPUT:
        MY_STACK_POP(processor->stk, &output);
        printf(YELLOW("Answer is %lg\n"), output); 
        break;

      case CMD_POP:
        MY_STACK_POP(processor->stk, &x_1);
        processor->registers[processor->instructions.script[++processor->ip]] = x_1;
        break;
    //////////////////////////////////
      case CMD_JA:
        MY_STACK_POP(processor->stk, &x_2);
        MY_STACK_POP(processor->stk, &x_1);

        if (x_1 - x_2 > 0)
        {
            tempor_ip = processor->ip + 1;
            processor->ip = processor->instructions.script[tempor_ip] - 1;
        }
        else 
            processor->ip++;
        break;
    
      case CMD_JAE:
        MY_STACK_POP(processor->stk, &x_2);
        MY_STACK_POP(processor->stk, &x_1);
        if (compare_double(x_1, x_2) || (x_1 - x_2 > 0))
        {
            tempor_ip = processor->ip + 1;
            processor->ip = processor->instructions.script[tempor_ip] - 1;
        }
        else 
            processor->ip++;

        break;
    
      case CMD_JB:
        MY_STACK_POP(processor->stk, &x_2);
        MY_STACK_POP(processor->stk, &x_1);
        if (x_1 - x_2 < 0)
        {
            tempor_ip = processor->ip + 1;
            processor->ip = processor->instructions.script[tempor_ip] - 1;
        }
        else 
            processor->ip++;

        break;

      case CMD_JBE:
        MY_STACK_POP(processor->stk, &x_2);
        MY_STACK_POP(processor->stk, &x_1);
        if (compare_double(x_1, x_2) || (x_1 - x_2 < 0))
        {
            tempor_ip = processor->ip + 1;
            processor->ip = processor->instructions.script[tempor_ip] - 1;
        }
        else 
            processor->ip++;

        break;

      case CMD_JE:
        MY_STACK_POP(processor->stk, &x_2);
        MY_STACK_POP(processor->stk, &x_1);
        if (compare_double(x_1, x_2))
        {
            tempor_ip = processor->ip + 1;
            processor->ip = processor->instructions.script[tempor_ip] - 1;
        }
        else 
            processor->ip++;

        break;

      case CMD_JNE:
        MY_STACK_POP(processor->stk, &x_2);
        MY_STACK_POP(processor->stk, &x_1);
        if (!compare_double(x_1, x_2))
        {
            tempor_ip = processor->ip + 1;
            processor->ip = processor->instructions.script[tempor_ip] - 1;
        }
        else 
            processor->ip++;

        break;

      case CMD_JMP:
        tempor_ip = processor->ip + 1;
        processor->ip = processor->instructions.script[tempor_ip] - 1;
        break;
    //////////////////////////////
      case CMD_HAULT:
        printf(GREEN("PROGRAMM COMPLETED\n"));
        run = STOP;
        break;
    
      default:
        printf(RED("SNTXERR_PROCESSOR: %d"), processor->instructions.script[processor->ip]); 
        run = STOP;
        break;
      }

  processor->ip++;
  }

  return 0;

  MY_STACK_DTOR(processor->stk);
  free(processor->instructions.script); processor->instructions.script = NULL;
}
