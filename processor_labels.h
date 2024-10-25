#ifndef STACK_FUNC
#define STACK_FUNC
    #include"STACK\stack_functions.h"
#endif

#ifndef PROCESSOR_LABELS
#define PROCESSOR_LABELS

struct label
{
    int pc;
    char label[100];
};

label* labels_init(int size);
int is_label(char* cmd, int label_size);
int free_label(label* table_labels, int label_size);
int find_label(label* table_labels, char* label, int label_size);
int labels_dtor(label* processor_labels);

#endif