#include"assembler.h"
#include"run_processor.h"

int main(int argc, char *argv[])
{
    if(argc < 3)
        return STOP;
    
    FILE* input_file  = fopen(argv[argc-2], "r");
    FILE* output_file = fopen(argv[argc-1], "w+");

    int* instructions = assembler(input_file, output_file);

    /*for (int i = 0; i <= 12; i++)
    {
        if (instructions[i] == CMD_PUSH)
            printf("%d ", instructions[i]);
        else
            printf("%d\n", instructions[i]);
    }
    printf("___________________\n");*/

    run_processor(instructions); 
    free(instructions); instructions = NULL;
    return 0;
}

