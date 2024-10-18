#include"assembler.h"
#include"run_processor.h"

int main(int argc, char *argv[])
{
    if(argc < 3)
        return STOP;
    /*for (int i = 0; i <= 12; i++)
    {
        if (instructions[i] == CMD_PUSH)
            printf("%d ", instructions[i]);
        else
            printf("%d\n", instructions[i]);
    }
    printf("___________________\n");*/
    struct SPU processor = {};
    struct my_stack stk  = {};

    processor_init(&processor, &stk, argc, argv);

    run_processor(&processor); 
    
    return 0;
}

