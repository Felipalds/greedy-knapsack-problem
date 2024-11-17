#include "bin/bin.c"
#include "stdio.h"
#include "dirent.h"
#include "stdlib.h"
#include "string.h"

char* concatenate(const char* str1, const char* str2) {
    size_t len1 = strlen(str1), len2 = strlen(str2);

    char* result = malloc(len1 + len2 + 1);
    if (result == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    strcpy(result, str1);
    strcat(result, str2);

    return result;
}

int main(int argc, char** args)
{
    if (argc <= 1)
    {
        printf("No folder specified.\n");
    }

    char *files_path = args[1];

    DIR *directory = opendir(files_path);

    if (directory == NULL)
    {
        printf("Unable to open directory");
        return 1;
    }

    struct dirent *entry;

    int problems_size = 0;

    char *files_path_with_slash = concatenate(files_path, "/");

    FILE *csv_file = fopen("bin-results.csv", "w+");
    // Columns: file_name, time_taken, items_amount, max_capacity, total_profit, total_weight
    fprintf(csv_file, "file_name, time_taken, items_amount, max_capacity, total_profit, total_weight\n");

    while ((entry = readdir(directory)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            BinProblemStruct problem;
            char *final_path = concatenate(files_path_with_slash, entry->d_name);
            problem.file_path = final_path;
            printf("Processing %s\n", final_path);
            run_bin_algorithm(&problem);
            int sum_profit = 0, sum_weight = 0;
            for (int i = 0; i < problem.solution_size; i++)
            {
                sum_profit += problem.items[problem.solution[i]].profit;
                sum_weight += problem.items[problem.solution[i]].weight;
            }
            fprintf(csv_file, "%s, %lf, %i, %i, %i, %i\n", final_path, problem.time_taken, problem.items_amount, problem.capacity, sum_profit, sum_weight);
            free_bin_problem_struct(&problem);
            free(final_path);
        }
    }

    free(files_path_with_slash);
    fclose(csv_file);
    closedir(directory);
    return 0;
}
