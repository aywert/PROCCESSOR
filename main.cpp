#include"processor.h"

int main(int argc, char *argv[])
{
    if(argc < 4)
        return STOP;
        
    struct SPU processor = {};
    struct my_stack stk  = {};

    processor_init(&processor, &stk, argc, argv);

    run_processor(&processor);

    processor_dtor(&processor); 
    
    return 0;
}

