#ifndef STACK_FUNC
#define STACK_FUNC
    #include"STACK\stack_functions.h"
#endif

#include"processor.h"
#include"assembler.h"
#include"processor_labels.h"
int assembler(struct SPU* processor) 
{
  // printf("=========================================\n");
  // printf("processor->name_file = %p\n", processor->name_file);
  // printf("processor->output_file = %p\n", processor->output_file);
  // printf("processor->input_file = %p\n", processor->input_file);
  // printf("processor->instructions = %p\n", processor->instructions);
  // printf("processor->ip = %d\n", processor->ip);
  // printf("processor->stk = %p\n", processor->stk);
  // printf("processor->registers = %p\n", processor->registers);
  // printf("=========================================\n");
  assert(processor);
  int* instructions = (int*)calloc(sizeof(int), instruct_size); 
  assert(instructions);
  label* table_labels = labels_init(size_label);

  int eof = 0;
  char cmd[size_cmd] = {}; 
  for (int n_pass = 1; n_pass <= 3; n_pass++){ 
    int pc  = 0;
    int run = 1;
    do 
    {
      eof = fscanf(processor->input_file, "%s", cmd);
      if (eof == EOF)
        break;
      //printf("cmd = %s\n", cmd);
      if (is_label(cmd, size_cmd) == 1)
      {
        //printf("i am label\n");
        int free_lab = free_label(table_labels, size_label);
        for (int i = 0; i < size_cmd; i++)
        {
          table_labels[free_lab].label[i] = cmd[i]; cmd[i] = 0;
          printf("%c", table_labels[free_lab].label[i]);
          if (table_labels[free_lab].label[i] == ':')\
            table_labels[free_lab].label[i] = '\0';
        }
        printf("\n");
        
        table_labels[free_lab].pc = pc;
        printf("pc = %d\n", pc);

    //      for(int i = 0; i < 3; i++)
    // {
    //   for (int j = 0; j < 10; j++)
    //   {
    //     printf("table_labels[%d].label[%d] = %c\n", i, j, table_labels[i].label[j]);
    //   }
    //   printf("table_labels[%d].pc = %d\n", i, table_labels[i].pc);
    //   printf("======================================\n");
    // }
    
        continue;
      }

      if (strcmp(cmd, "call") == 0)
      {
        instructions[pc] = CMD_CALL; pc++; 
        //printf("i was here\n");
        char arg[size_label] = "";
        fscanf(processor->input_file, "%s", &arg[0]);
        int found_label = find_label(table_labels, arg, size_label);
        printf("found_label = %d\n", found_label);

    //      for(int i = 0; i < 3; i++)
    // {
    //   for (int j = 0; j < 10; j++)
    //   {
    //     printf("table_labels[%d].label[%d] = %c\n", i, j, table_labels[i].label[j]);
    //   }
    //   printf("table_labels[%d].pc = %d\n", i, table_labels[i].pc);
    //   printf("======================================\n");
    // }
        if (found_label >= 0)
        {
          instructions[pc] = pc + 2; pc++; // 
          instructions[pc] = table_labels[found_label].pc; pc++;
        }
        else
        {
          pc += 2;
        }
        continue;
      }

      if (strcmp(cmd, "ret") == 0)
      {
        instructions[pc++] = CMD_RET;
        continue;
      }

      if (strcmp(cmd, "push") == 0)
      {
        //printf("was here push\n");
        int arg_1 = 0;
        fscanf(processor->input_file, "%d", &arg_1);
        instructions[pc++] = CMD_PUSH;
        instructions[pc++] = arg_1;

        if (arg_1 & 1)
        {
          int arg_2 = 0;
          fscanf(processor->input_file, "%d", &arg_2);
          instructions[pc++] = arg_2;
          continue;
        }

        if (arg_1 & 2)
        {
          char arg[size_cmd] = "";
          fscanf(processor->input_file, "%s", &arg[0]); 
          if (strcmp(arg, "AX") == 0)
          {
            instructions[pc++] = 0;
            continue;
          }

          if (strcmp(arg, "BX") == 0)
          {
            instructions[pc++] = 1;
            continue;
          }

          if (strcmp(arg, "CX") == 0)
          {
            instructions[pc++] = 2;
            continue;
          }

          if (strcmp(arg, "DX") == 0)
          {
            instructions[pc++] = 3;
            continue;
          }

          if (strcmp(arg, "EX") == 0)
          {
            instructions[pc++] = 4;
            continue;
          }

          if (strcmp(arg, "FX") == 0)
          {
            instructions[pc++] = 5;
            continue;
          }

          if (strcmp(arg, "GX") == 0)
          {
            instructions[pc++] = 6;
            continue;
          }
        }
      }

      if (strcmp(cmd, "add") == 0)
      {
        instructions[pc] = CMD_ADD; pc++;
        printf("add\n"); 
        continue;
      }

      if (strcmp(cmd, "sub") == 0)
      {
        instructions[pc] = CMD_SUBTRACT; pc++; 
        continue;
      }

      if (strcmp(cmd, "div") == 0)
      {
        instructions[pc] = CMD_DIVIDE; pc++;
        continue;
      }

      if (strcmp(cmd, "mul") == 0)
      {
        instructions[pc] = CMD_MULTIPLY; pc++; 
        continue;
      }
      
      if (strcmp(cmd, "sin") == 0)
      {
        instructions[pc] = CMD_SIN; pc++; 
        continue;
      }
      
      if (strcmp(cmd, "cos") == 0)
      {
        instructions[pc] = CMD_COS; pc++; 
        continue;
      }
      
      if (strcmp(cmd, "sqrt") == 0)
      {
        instructions[pc] = CMD_SQRT; pc++; 
        continue;
      }

      if (strcmp(cmd, "pop") == 0)
      {
        instructions[pc++] = CMD_POP;

        char arg[size_cmd] = "";
        fscanf(processor->input_file, "%s", &arg[0]);
          
        if (strcmp(arg, "AX") == 0)
        {
          instructions[pc++] = 0;
          continue;
        }

        if (strcmp(arg, "BX") == 0)
        {
          instructions[pc++] = 1;
          continue;
        }

        if (strcmp(arg, "CX") == 0)
        {
          instructions[pc++] = 2;
          continue;
        }

        if (strcmp(arg, "DX") == 0)
        {
          instructions[pc++] = 3;
          continue;
        }

        if (strcmp(arg, "EX") == 0)
        {
          instructions[pc++] = 4;
          continue;
        }

        if (strcmp(arg, "FX") == 0)
        {
          instructions[pc++] = 5;
          continue;
        }

        if (strcmp(arg, "GX") == 0)
        {
          instructions[pc++] = 6;
          continue;
        }

        continue;
      }

      if (strcmp(cmd, "in") == 0)
      {
        instructions[pc] = CMD_INPUT; pc++; 
        continue;
      }

      if (strcmp(cmd, "out") == 0)
      {
        instructions[pc] = CMD_OUTPUT; pc++; 
        continue;       
      }
      
      if (strcmp(cmd, "hlt") == 0)
      {
        instructions[pc] = CMD_HAULT;  pc++; 
        continue;
      }

      if (strcmp(cmd, "draw") == 0)
      {
        instructions[pc] = CMD_DRAW;  pc++; 
        continue;
      }
      ////////////////////////////////
      if (strcmp(cmd, "ja") == 0)
      {
        int arg = 0;
        fscanf(processor->input_file, "%d", &arg);
        instructions[pc] = CMD_JA; pc++;
        instructions[pc] = arg;    pc++;
        continue;
      }

      if (strcmp(cmd, "jae") == 0)
      {
        int arg = 0;
        fscanf(processor->input_file, "%d", &arg);
        instructions[pc] = CMD_JAE; pc++;
        instructions[pc] = arg;     pc++;
        continue;
      }

      if (strcmp(cmd, "jb") == 0)
      {
        int arg = 0;
        fscanf(processor->input_file, "%d", &arg);
        instructions[pc] = CMD_JB; pc++;
        instructions[pc] = arg;    pc++;
        continue;
      }

      if (strcmp(cmd, "JBE") == 0)
      { 
        char arg[size_cmd] = {};
        fscanf(processor->input_file, "%s", arg);
        int found_label = find_label(table_labels, arg, size_cmd);
        if (found_label >= 0)
        {
          instructions[pc] = CMD_JBE; pc++;
          instructions[pc] = table_labels[found_label].pc; pc++;
          table_labels[found_label].pc = -1;
        }

        else
        {
          if (n_pass >= 2)
          {
            printf(RED("\nSNTXERROR no match for label: "));
            fputs(arg, stdout); 
            printf("\n");
            instructions[0] = CMD_HAULT; run = 0;
          }
        }
        continue;
        
      }

      if (strcmp(cmd, "jbe") == 0)
      { 
        int arg = 0;
        fscanf(processor->input_file, "%d", &arg);
        instructions[pc] = CMD_JBE; pc++;
        instructions[pc] = arg;     pc++;
        continue;
      }

      if (strcmp(cmd, "JE") == 0)
      { 
        char arg[size_cmd] = {};
        fscanf(processor->input_file, "%s", arg);
        int found_label = find_label(table_labels, arg, size_cmd);
        if (found_label >= 0)
        {
          instructions[pc] = CMD_JBE; pc++;
          instructions[pc] = table_labels[found_label].pc; pc++;
          table_labels[found_label].pc = -1;
        }

        else
        {
          if (n_pass >= 2)
          {
            printf(RED("\nSNTXERROR no match for label: "));
            fputs(arg, stdout); 
            printf("\n");
            instructions[0] = CMD_HAULT; run = 0;
          }
        }
        continue;
        
      }

      if (strcmp(cmd, "je") == 0)
      {
        int arg = 0;
        fscanf(processor->input_file, "%d", &arg);
        instructions[pc] = CMD_JE; pc++;
        instructions[pc] = arg;    pc++;
        continue;
      }

      if (strcmp(cmd, "jne") == 0)
      {
        int arg = 0;
        fscanf(processor->input_file, "%d", &arg);
        instructions[pc] = CMD_JNE; pc++;
        instructions[pc] = arg;     pc++;
        continue;
      }

      if (strcmp(cmd, "jmp") == 0)
      {
        int arg = 0;
        fscanf(processor->input_file, "%d", &arg);
        instructions[pc] = CMD_JMP; pc++;
        instructions[pc] = arg;     pc++;
        continue;
      }

      ////////////////////////
      //printf(RED("SNTXERR_ASSEMBLER: %s\n"), cmd);
      //run = 0;

      } while (eof != EOF && run == 1);

    // for(int i = 0; i < pc; i++)
    //   printf("instructions[%d] = %d\n", i, instructions[i]);
    // printf("===================================\n");
    //processor->instructions.script = instructions;
    processor->instructions.size = pc;
    rewind(processor->input_file);
    // for(int i = 0; i < 10; i++)
    // {
    //   for (int j = 0; j < 10; j++)
    //   {
    //     printf("table_labels[%d].label[%d] = %c\n", i, j, table_labels[i].label[j]);
    //   }
    //   printf("table_labels[%d].pc = %d\n", i, table_labels[i].pc);
    //   printf("======================================\n");
    // }
  }

  //labels_dtor(table_labels);
  
  // printf("=========================================\n");
  // printf("processor->name_file = %p\n", processor->name_file);
  // printf("processor->output_file = %p\n", processor->output_file);
  // printf("processor->input_file = %p\n", processor->input_file);
  // printf("processor->input_bin = %p\n", processor->output_bin);
  // printf("processor->instructions = %p\n", processor->instructions);
  // printf("processor->ip = %d\n", processor->ip);
  // printf("processor->stk = %p\n", processor->stk);
  // printf("processor->registers = %p\n", processor->registers);
  // printf("=========================================\n");
  //-------------------------------------------------------------------------------------------------------------------------------
                                          //Printing to code_instruct.asm
  //-------------------------------------------------------------------------------------------------------------------------------
  fprintf(processor->output_file, "MOV\nversion: 1\n");
  struct stat file_data = {};
  stat(processor->name_file, &file_data);
  fprintf(processor->output_file, "Size of input file: %ld\n\n", file_data.st_size);

  fwrite(instructions, sizeof (instructions[0]), (size_t)processor->instructions.size, processor->output_bin);

  for (int i = 0; i < processor->instructions.size; i++)
  {
    switch(instructions[i])
    {
      case CMD_PUSH:
        fprintf(processor->output_file, "%d ", instructions[i]);
       
        fprintf(processor->output_file, "%d ", instructions[i+1]);

        fprintf(processor->output_file, "%d\n", instructions[i+2]);
        
        i+=2;
        break;

      case CMD_JA:
        fprintf(processor->output_file, "%d %d\n", instructions[i],  instructions[i+1]);
            i++;
        break;
    
      case CMD_JAE:
        fprintf(processor->output_file, "%d %d\n", instructions[i],  instructions[i+1]);
            i++;
        break;
    
      case CMD_JB:
        fprintf(processor->output_file, "%d %d\n", instructions[i],  instructions[i+1]);
            i++;
        break;

      case CMD_JBE:
        fprintf(processor->output_file, "%d %d\n", instructions[i],  instructions[i+1]);
            i++;
        break;

      case CMD_JE:
        fprintf(processor->output_file, "%d %d\n", instructions[i],  instructions[i+1]);
            i++;
        break;

      case CMD_JNE:
        fprintf(processor->output_file, "%d %d\n", instructions[i],  instructions[i+1]);
            i++;
        break;

      case CMD_JMP:
        fprintf(processor->output_file, "%d %d\n", instructions[i],  instructions[i+1]);
            i++;
        break;

      case CMD_POP:
        fprintf(processor->output_file, "%d %d\n", instructions[i],  instructions[i+1]);
            i++;
        break;

      case CMD_CALL:
        fprintf(processor->output_file, "%d %d %d\n", instructions[i],  instructions[i+1], instructions[i+2]);
            i+=2;
        break;

      default:
        fprintf(processor->output_file, "%d\n", instructions[i]);
        break;
    }
  }
  free(instructions); instructions = NULL; 
  return 0; 
}