#include"assembler.h"

int* assembler(FILE* input_file, FILE* output_file)  //, const char* name) // для считывадьчика инфы
{
    //Рабочий считывальщик инфы из файла по байтого
    /*struct stat text_data = {};
    stat(name, &text_data);

    char* buffer = (char*) calloc(text_data.st_size, sizeof(char));
    
    fread(buffer, text_data.st_size , sizeof(char), file);
    //return buffer;
    for (int i = 0; i < text_data.st_size; i++)
        printf("%c", buffer[i]);*/
    
    int* instructions = (int*)calloc(instruct_size, sizeof(int));
    int pc = -1; 
    char cmd[50] = ""; 
    do 
    {
        fscanf(input_file, "%s", cmd);
        if (strcmp(cmd, "push") == 0)
        {
            int arg = 0;
            fscanf(input_file, "%d", &arg);
            pc++; instructions[pc] = CMD_PUSH;
            pc++; instructions[pc] = arg;
            continue;
        }

        if (strcmp(cmd, "add") == 0)
        {
            pc++; instructions[pc] = CMD_ADD;
            continue;
        }

        if (strcmp(cmd, "sub") == 0)
        {
            pc++; instructions[pc] = CMD_SUBTRACT;
            continue;
        }

        if (strcmp(cmd, "div") == 0)
        {
            pc++; instructions[pc] = CMD_DIVIDE;
            continue;
        }

        if (strcmp(cmd, "mul") == 0)
        {
            pc++; instructions[pc] = CMD_MULTIPLY;
            continue;
        }

        
        if (strcmp(cmd, "sin") == 0)
        {
            pc++; instructions[pc] = CMD_SIN;
            continue;
        }
        
        if (strcmp(cmd, "cos") == 0)
        {
            pc++; instructions[pc] = CMD_COS;
            continue;
        }
        
        if (strcmp(cmd, "sqrt") == 0)
        {
            pc++; instructions[pc] = CMD_SQRT;
            continue;
        }

        if (strcmp(cmd, "in") == 0)
        {
            pc++; instructions[pc] = CMD_INPUT;
            continue;
        }

        if (strcmp(cmd, "out") == 0)
        {
            pc++; instructions[pc] = CMD_OUTPUT;
            continue;       
        }

        if (strcmp(cmd, "hlt") == 0)
        {
            pc++; instructions[pc] = CMD_HAULT;
            continue;
        }

        else{printf(RED("SNTXERR: %s"), cmd);}
    
    }while (strcmp(cmd, "hlt") != 0);

    for (int i = 0; i <= pc; i++)
    {
        if (instructions[i] == CMD_PUSH)
            fprintf(output_file, "%d ", instructions[i]);
        else
            fprintf(output_file, "%d\n", instructions[i]);
    }
    return instructions; 
}