#include"processor.h"
//#define PROCESSOR_DEBUG
int processor_init(struct SPU* processor, struct my_stack* stk, int argc, char *argv[])
{
  processor->name_file   = argv[argc-3];
  processor->input_file  = fopen(argv[argc-3], "r");
  processor->output_file = fopen(argv[argc-2], "w");
  processor->output_bin  = fopen(argv[argc-1], "wb");
  
  assembler(processor);
  fclose(processor->output_bin);

  processor->instructions.script = (int*)calloc( sizeof(int), processor->instructions.size);
  assert(processor->instructions.script);

  processor->output_bin  = fopen(argv[argc-1], "rb");
  assert(processor->output_bin);

  fread(processor->instructions.script, sizeof(processor->instructions.script[0]), processor->instructions.size, processor->output_bin);
  
  MY_STACK_CTOR(stk, 10);
  
  double* registers = (double*)calloc(n_registers, sizeof(double));
  registers[n_registers - 1] = last_register;

  processor->stk = stk;
  processor->registers = registers;
  // printf("processor->name_file = %p\n", processor->name_file);
  // printf("processor->output_file = %p\n", processor->output_file);
  // printf("processor->input_file = %p\n", processor->input_file);
  // printf("processor->instructions.script = %p\n", processor->instructions.script);
  // printf("processor->ip = %d\n", processor->ip);
  // printf("processor->stk = %p\n", processor->stk);
  // printf("processor->registers = %p\n", processor->registers);

  return 0;
}

int run_processor(struct SPU* processor)
{
  cycle_status run = DO;
  while(run){
  ///////////////////////////////////////////////////////////////////////////////////////
    #ifdef PROCESSOR_DEBUG
    printf("processor->instructions.size = %d\n", processor->instructions.size);
    for (int i = 0; i < processor->instructions.size; i++)
    {
      printf(BLUE("%4i"), i);
    }
    printf("\n");

    for (int i = 0; i < processor->instructions.size; i++)
    {
      printf(MAGENTA("%4X"), processor->instructions.script[i]);
    }
    printf("\n");

    for (int i = 0; i < processor->ip; i++)
    {
      printf("    ");
    }
    printf(RED("   %c"), 3);

    getchar();
    printf("\n\n");
    #endif
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
        printf(GREEN("Processor completed the emplementation of the programm\n"));
        run = STOP;
        break;
    
      default:
        printf(RED("SNTXERR_PROCESSOR: %d %d\n"), processor->instructions.script[processor->ip], processor->ip); 
        printf("hlt!\n");
        run = STOP;
        break;
      }

  processor->ip++;
  }

  return 0;
}

int processor_dtor(struct SPU* processor)
{
  fclose(processor->input_file);
  fclose(processor->output_file);
  fclose(processor->output_bin);
  MY_STACK_DTOR(processor->stk);
  free(processor->registers); processor->registers = NULL;
  free(processor->instructions.script); processor->instructions.script = NULL;
  return 0;
}