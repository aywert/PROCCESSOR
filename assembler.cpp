#include"assembler.h"

int* assembler(FILE* input_file, FILE* output_file)  //, const char* name) // для считывальчика инфы
{
    //
    //Рабочий считывальщик инфы из файла по байтого
    /*struct stat text_data = {};
    stat(name, &text_data);

    char* buffer = (char*) calloc(text_data.st_size, sizeof(char));
    
    fread(buffer, text_data.st_size , sizeof(char), file);
    //return buffer;
    for (int i = 0; i < text_data.st_size; i++)
        printf("%c", buffer[i]);*/
    
    int* instructions = (int*)calloc(instruct_size, sizeof(int)); 
    int pc = 0;
    int run = 1;
    char cmd[50] = ""; 
    do 
    {
        fscanf(input_file, "%s", cmd);
        if (strcmp(cmd, "push") == 0)
        {
            int arg = 0;
            fscanf(input_file, "%d", &arg);
            instructions[pc] = CMD_PUSH; pc++;
            instructions[pc] = arg;      pc++;
            continue;
        }

        if (strcmp(cmd, "pushr") == 0)
        {
            char arg[5] = {};
            fscanf(input_file, "%s", &arg);
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

            char arg[5] = {};
            fscanf(input_file, "%s", &arg);
            
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
            fscanf(input_file, "%d", &arg);
            instructions[pc] = CMD_JA; pc++;
            instructions[pc] = arg;    pc++;
            continue;
        }
        if (strcmp(cmd, "jae") == 0)
        {
            int arg = 0;
            fscanf(input_file, "%d", &arg);
            instructions[pc] = CMD_JAE; pc++;
            instructions[pc] = arg;     pc++;
            continue;
        }
        if (strcmp(cmd, "jb") == 0)
        {
            int arg = 0;
            fscanf(input_file, "%d", &arg);
            instructions[pc] = CMD_JB; pc++;
            instructions[pc] = arg;    pc++;
            continue;
        }
        if (strcmp(cmd, "jbe") == 0)
        { 
            int arg = 0;
            fscanf(input_file, "%d", &arg);
            instructions[pc] = CMD_JBE; pc++;
            instructions[pc] = arg;     pc++;
            continue;
        }
        if (strcmp(cmd, "je") == 0)
        {
            int arg = 0;
            fscanf(input_file, "%d", &arg);
            instructions[pc] = CMD_JE; pc++;
            instructions[pc] = arg;    pc++;
            continue;
        }
        if (strcmp(cmd, "jne") == 0)
        {
            int arg = 0;
            fscanf(input_file, "%d", &arg);
            instructions[pc] = CMD_JNE; pc++;
            instructions[pc] = arg;     pc++;
            continue;
        }

        if (strcmp(cmd, "jmp") == 0)
        {
            int arg = 0;
            fscanf(input_file, "%d", &arg);
            instructions[pc] = CMD_JMP; pc++;
            instructions[pc] = arg;     pc++;
            continue;
        }
        ////////////////////////
        else 
        {
            printf(RED("SNTXERR_ASSEMBLER: %s\n"), cmd);
            run = 0;
        }
    
    }while (strcmp(cmd, "hlt") != 0 && (run == 1));

//-------------------------------------------------------------------------------------------------------------------------------
                                            //Printing to code_instruct.asm
//-------------------------------------------------------------------------------------------------------------------------------

    fprintf(output_file, "It's a place where requared information with be transfered\n\n");
    for (int i = 0; i < pc; i++)
    {
        switch(instructions[i])
        {
          case CMD_PUSH:
            fprintf(output_file, "%d %d\n", instructions[i],  instructions[i+1]);
                i++;
            break;

          case CMD_PUSHR:
            fprintf(output_file, "%d %d\n", instructions[i],  instructions[i+1]);
                i++;
            break;

          case CMD_JA:
            fprintf(output_file, "%d %d\n", instructions[i],  instructions[i+1]);
                i++;
            break;
        
          case CMD_JAE:
            fprintf(output_file, "%d %d\n", instructions[i],  instructions[i+1]);
                i++;
            break;
        
          case CMD_JB:
            fprintf(output_file, "%d %d\n", instructions[i],  instructions[i+1]);
                i++;
            break;

          case CMD_JBE:
            fprintf(output_file, "%d %d\n", instructions[i],  instructions[i+1]);
                i++;
            break;

          case CMD_JE:
            fprintf(output_file, "%d %d\n", instructions[i],  instructions[i+1]);
                i++;
            break;

          case CMD_JNE:
            fprintf(output_file, "%d %d\n", instructions[i],  instructions[i+1]);
                i++;
            break;

          case CMD_JMP:
            fprintf(output_file, "%d %d\n", instructions[i],  instructions[i+1]);
                i++;
            break;

          case CMD_POP:
            fprintf(output_file, "%d %d\n", instructions[i],  instructions[i+1]);
                i++;
            break;

          default:
            fprintf(output_file, "%d\n", instructions[i]);
            break;
        }
    }

    return instructions; 
}