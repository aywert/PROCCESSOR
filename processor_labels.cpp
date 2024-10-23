#ifndef STACK_FUNC
#define STACK_FUNC
    #include"STACK\stack_functions.h"
#endif

#include"processor.h"
#include"processor_labels.h"
#include"assert.h"

label* labels_init(int size)
{
    label* table_labels = (label*)calloc(sizeof(label), size);
    assert(table_labels);

    if (table_labels == NULL)
    {
        printf(RED("Error in callocing in labels\n"));
        return 0;
    }

    for (int i = 0; i < size; i++)
    {
        table_labels[i].pc = -1;
    }

    return  table_labels;
}

int labels_dtor(label* table_labels)
{
    assert(table_labels);
    free(table_labels); table_labels = NULL;
    return 0;
}

int is_label(char* cmd, int label_size)
{
    assert(cmd);
    //printf("printing grom label is\n");
    for (int i = 0; i < label_size; i++)
    {
        if (cmd[i] == ':')
        {
            return 1;
        }
    }
    
    return 0;
}

int free_label(label* table_labels, int label_size)
{
    assert(table_labels);

    // for (int i = 0; i < label_size; i++)
    // {
    //     //printf("1");
    //     printf("table_labels[%d].pc = %d\n", i, table_labels[i].pc);
    // }
    // printf("=========================================\n");

    for (int i = 0; i < label_size; i++)
    {
        //printf("table_labels[i] = %d", table_labels[i].pc);
        if (table_labels[i].pc == -1)
            return i;
    }
    //printf("=========================================\n");

    printf(RED("Not enough space in labels"));
    return 0;
}

int find_label(label* table_labels, char* label, int label_size)
{
    assert(table_labels);
    assert(label);

    for (int i = 0; i < label_size; i++)
    {
        int j = 0;
        int flag = 1;
        while (j < label_size)
        {
            //printf("%c ", table_labels[i].label[j]);
            if (table_labels[i].label[j] != label[j] /*|| (label[j+1] == '0')*/)
            {
                flag = -1;
            }
            j++;
        } 
        if (flag == 1)
            return i;
    }
    printf(RED("Labels is incorrect please mind its value\nYour label have been ignored\n"));
    return -1;
}