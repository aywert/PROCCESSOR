#include"processor.h"
#include"assembler.h"
//#define PROCESSOR_DEBUG

static double get_arg(SPU* processor);

int processor_init(struct SPU* processor, struct my_stack* stk, struct my_stack* adr_stk, int argc, char *argv[])
{
  assert(processor);
  assert(stk);
  assert(argc);
  assert(argv);

  processor->name_file   = argv[argc-3];
  processor->input_file  = fopen(argv[argc-3], "r");  assert(processor->input_file);
  processor->output_file = fopen(argv[argc-2], "w");  assert(processor->output_file);
  processor->output_bin  = fopen(argv[argc-1], "wb"); assert(processor->output_bin);
  
  assembler(processor);
 
  fclose(processor->output_bin);

  processor->instructions.size = instruct_size;
  processor->RAW.size          = size_RAW;

  processor->instructions.script = (int*)calloc( sizeof(int), processor->instructions.size);
  processor->RAW.script          = (int*)calloc( sizeof(int), processor->RAW.size);

  assert(processor->instructions.script);
  assert(processor->RAW.script);
  
  for (int i = 0; i < 50; i++)
  {
    if (i%2 != 0)
      processor->RAW.script[i] = 1; //code_for '*'
    else 
      processor->RAW.script[i] = 0; //code_for ' '
    if (i%6 == 0)
      processor->RAW.script[i] = 2; //code_for '\n'
  }
    

  processor->output_bin  = fopen(argv[argc-1], "rb");
  assert(processor->output_bin);

  int n_elem = fread(processor->instructions.script, sizeof(processor->instructions.script[0]), processor->instructions.size, processor->output_bin);
  assert(n_elem);
  // for (int i = 0; i < processor->instructions.size; i++)
  //   printf("%d\n", processor->instructions.script[i]);
  MY_STACK_CTOR(stk, 10);
  MY_STACK_CTOR(adr_stk, 10);
  
  double* registers = (double*)calloc(n_registers, sizeof(double));
  assert(registers);
  registers[n_registers - 1] = last_register;

  processor->stk = stk;
  processor->adr_stk = adr_stk;
  processor->registers = registers;
  //printf("====================================================");
  // printf("processor->name_file = %p\n", processor->name_file);
  // printf("processor->output_file = %p\n", processor->output_file);
  // printf("processor->input_file = %p\n", processor->input_file);
  // printf("processor->instructions.script = %p\n", processor->instructions.script);
  // printf("processor->ip = %d\n", processor->ip);
  // printf("processor->stk = %p\n", processor->stk);
  // printf("processor->registers = %p\n", processor->registers);
  //printf("====================================================");
  return 0;
}

int run_processor(struct SPU* processor)
{
  assert(processor);
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
    stack_elem_t tempr = 0;
    int tempor_ip = 0;

    // for (int i = 0; i < n_registers; i++)
    // {
    //   printf("registers[%d] =  %d\n", i, processor->registers[i]);
    // }
    // printf("==========================================\n");
    // printf("processor->ip = %d\n", processor->ip);
    // printf("processor->instructions =  %d\n", processor->instructions.script[processor->ip]);
    switch(processor->instructions.script[processor->ip])
    {
      case CMD_PUSH:
        //MY_STACK_PUSH(processor->stk, processor->instructions.script[++processor->ip]);
        MY_STACK_PUSH(processor->stk, get_arg(processor));
        break;

      case CMD_CALL:
        MY_STACK_PUSH(processor->adr_stk, processor->instructions.script[++processor->ip]-1);
        //processor->registers[6] = processor->instructions.script[++processor->ip];
        tempor_ip = processor->ip;
        processor->ip = processor->instructions.script[tempor_ip+1] - 1;
        break;

      case CMD_RET:
        MY_STACK_POP(processor->adr_stk, &tempr);
        processor->ip = (int)tempr;
        // printf(" processor->ip = %d\n", processor->ip);
        // printf("tempor_ip = %lg\n", tempor_ip);
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

      case CMD_DRAW:
        for (int i = 0; i < processor->RAW.size; i++)
        {
          if (i%100 == 0)
            printf("%c", 3);
        }
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
        printf(GREEN("\nProcessor completed the emplementation of the programm\n"));
        run = STOP;
        break;
    
      default:
        printf(RED("\nSNTXERR_PROCESSOR: %d %d\n"), processor->instructions.script[processor->ip], processor->ip); 
        run = STOP;
        break;
      }

  processor->ip++;
  }

  return 0;
}

// 1 - push directly
// 2 - push from registers
// 3 - push from RAW

static double get_arg(SPU* processor)
{
  int arg_t = processor->instructions.script[++processor->ip];
  double result = 0;
  if (arg_t & push_f_con) result = processor->instructions.script[++processor->ip];
  if (arg_t & push_f_reg) result = processor->registers[processor->instructions.script[++processor->ip]];
  return result;
}

int processor_dtor(struct SPU* processor)
{
  assert(processor);
  fclose(processor->input_file);
  fclose(processor->output_file);
  fclose(processor->output_bin);
  
  MY_STACK_DTOR(processor->stk);

  free(processor->registers); processor->registers = NULL;
  free(processor->instructions.script); processor->instructions.script = NULL;
  return 0;
}