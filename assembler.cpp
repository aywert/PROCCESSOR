#include"processor.h"

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
    
    int* instructions = (int*)calloc(sizeof(int), instruct_size); 
    label* table_labels = labels_init();

    int pc  = 0;
    int run = 1;
    char cmd[size_cmd] = ""; 
    do 
    {
      fscanf(processor->input_file, "%s", cmd);
      if (is_label(cmd))
      {
        int free_lab = free_label(table_labels);
        for (int i = 0; i < size_cmd; i++)
        {
          table_labels[free_lab].label[i] = cmd[i];
        }
      
        table_labels[free_lab].pc = pc;
        continue;
      }

      if (strcmp(cmd, "push") == 0)
      {
        int arg = 0;
        fscanf(processor->input_file, "%d", &arg);
        instructions[pc] = CMD_PUSH; pc++;
        instructions[pc] = arg;      pc++;
        continue;
      }

      if (strcmp(cmd, "pushr") == 0)
      {
        char arg[size_cmd] = "";
        fscanf(processor->input_file, "%s", &arg[0]);
        instructions[pc++] = CMD_PUSHR; 
          
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

      if (strcmp(cmd, "add") == 0)
      {
        instructions[pc] = CMD_ADD; pc++; 
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
        int found_label = find_label(table_labels, arg);
        if (found_label >= 0)
        {
          instructions[pc] = CMD_JBE; pc++;
          instructions[pc] = table_labels[found_label].pc; pc++;
        }

        else
        {
          printf(RED("SNTXERROR no match for label:\n"));
          fputs(arg, stdout); 
          printf("\n");
          instructions[0] = CMD_HAULT; run = 0;
          // instructions[pc++] = CMD_HAULT;
          // instructions[pc++] = CMD_HAULT;
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
      printf(RED("SNTXERR_ASSEMBLER: %s\n"), cmd);
      run = 0;
    
    }while (strcmp(cmd, "hlt") != 0 && (run == 1));

    //processor->instructions.script = instructions;
    processor->instructions.size   = pc;
    labels_dtor(table_labels);
    // printf("=========================================\n");
    // printf("processor->name_file = %p\n", processor->name_file);
    // printf("processor->output_file = %p\n", processor->output_file);
    // printf("processor->input_file = %p\n", processor->input_file);
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
    
    fwrite(instructions, sizeof (instructions[0]), (size_t)pc, processor->output_bin);

    for (int i = 0; i < pc; i++)
    {
        switch(instructions[i])
        {
          case CMD_PUSH:
            fprintf(processor->output_file, "%d %d\n", instructions[i],  instructions[i+1]);
                i++;
            break;

          case CMD_PUSHR:
            fprintf(processor->output_file, "%d gerister_n: %d\n", instructions[i],  instructions[i+1]);
                i++;
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

          default:
            fprintf(processor->output_file, "%d\n", instructions[i]);
            break;
        }
    }
    free(instructions); instructions = NULL; 
    return 0; 
}