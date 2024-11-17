#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int randomrange(int range)
{
    return (float)rand()/(float)(RAND_MAX/(float)range);
}

int main(int argc, char** args)
{
    // ARGS: ITEMS_AMOUNT, MAX_CAPACITY
    if (argc < 3)
    {
        printf("Not all arguments specified.\n");
        return 1;
    }

    int items_amount = atoi(args[1]), max_capacity = atoi(args[2]);

    char *file_start_name = "random-data/Mochila";

    int file_name_len = strlen(file_start_name)+strlen(args[1]);

    char *file_name = malloc(file_name_len+5);

    printf("Here1\n");
    for (int i = 0; i < strlen(file_start_name); i++)
    {
        file_name[i] = file_start_name[i];
    }
    for (int i = strlen(file_start_name); i < file_name_len; i++)
    {
        file_name[i] = args[1][i - strlen(file_start_name)];
    }

    file_name[file_name_len + 4] = '\0';
    file_name[file_name_len + 3] = 't';
    file_name[file_name_len + 2] = 'x';
    file_name[file_name_len + 1] = 't';
    file_name[file_name_len] = '.';

    FILE* file = fopen(file_name, "w+");

    fprintf(file, "%i", max_capacity);
    fputc('\n', file);

    for (int i = 0; i < items_amount; i++)
    {
        fprintf(file, "%i", randomrange(max_capacity / 2));
        fputc('\t', file);
    }
    fputc('\n', file);

    for (int i = 0; i < items_amount; i++)
    {
        fprintf(file, "%i", randomrange(max_capacity / 2));
        fputc('\t', file);
    }

    free(file_name);
    fclose(file);
    return 0;
}
