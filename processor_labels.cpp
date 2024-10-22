#include"processor.h"

label* labels_init(void)
{
    label* table_labels = (label*)calloc(sizeof(label), instruct_size);

    if (table_labels == NULL)
    {
        printf(RED("Error in callocing in labels\n"));
        return 0;
    }

    for (int i = 0; i < instruct_size; i++)
    {
        table_labels[i].pc = -1;
    }

    return  table_labels;
}

int labels_dtor(label* table_labels)
{
    free(table_labels); table_labels = NULL;
    return 0;
}

int is_label(char* cmd)
{
    for (int i = 0; i < size_cmd; i++)
    {
        if (cmd[i] == ':')
            return 1;
    }
    return 0;
}

int free_label(label* table_labels)
{
    for (int i = 0; i < size_label; i++)
    {
        if (table_labels[i].pc == -1)
            return i;
        else 
            printf(RED("Not enough space in labels"));
    }
    return 0;
}

int find_label(label* table_labels, char* label)
{
    int flag = 1;
    for (int i = 0; i < size_label; i++)
    {
        int j = 0;
        while ((table_labels[i].label[j] != ':') && (j < 10))
        {
            if (table_labels[i].label[j] != label[j])
                flag = -1;
            j++;
        }
        if (flag >= 0)
            return i;
    }
    printf(RED("Labels is incorrect please mind its value\nYour label have been ignored\n"));
    return -1;
}