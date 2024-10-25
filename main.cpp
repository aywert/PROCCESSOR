#include"processor.h"

int main(int argc, char *argv[])
{
    if(argc < 4)
        return STOP;
        
    struct SPU processor = {};
    struct my_stack stk  = {};
    struct my_stack adr_stk  = {};

    processor_init(&processor, &stk, &adr_stk, argc, argv);

    run_processor(&processor);
    //printf(YELLOW("processor.registers[6] = %lg\n"), processor.registers[6]);

    processor_dtor(&processor); 
    
    return 0;
}

