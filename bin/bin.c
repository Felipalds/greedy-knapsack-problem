#ifndef BIN_CPP
#define BIN_CPP

#include "time.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct
{
    int index;
    int profit;
    int weight;
    float profit_weight_ratio;
} BinItemStruct;

typedef struct
{
    char* file_path;
    int* solution;
    int solution_size;
    double time_taken;
    int items_amount;
    int capacity;
    BinItemStruct *items;
} BinProblemStruct;

void free_bin_problem_struct(BinProblemStruct *problem)
{
    free(problem->solution);
    free(problem->items);
}

// MERGE SORT

void merge(BinItemStruct *arr, int l, int m, int r)
{
    int left = m - l + 1, right = r - m;

    BinItemStruct *left_arr = malloc(left*sizeof(BinItemStruct)), *right_arr = malloc(right*sizeof(BinItemStruct));

    for (int i = 0; i < left; i++)
    {
        left_arr[i] = arr[l + i];
    }

    for (int i = 0; i < right; i++)
    {
        right_arr[i] = arr[m + 1 + i];
    }

    int i = 0, j = 0, k = l;
    while (i < left && j < right)
    {
        if (left_arr[i].profit_weight_ratio >= right_arr[j].profit_weight_ratio)
        {
            arr[k] = left_arr[i];
            i++;
        }
        else
        {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }

    while (i < left)
    {
        arr[k] = left_arr[i];
        i++;
        k++;
    }

    while (j < right)
    {
        arr[k] = right_arr[j];
        j++;
        k++;
    }
    free(left_arr);
    free(right_arr);
}

void merge_sort(BinItemStruct *items, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        merge_sort(items, l, m);
        merge_sort(items, m + 1, r);
        merge(items, l, m, r);
    }
}

int* bin_algorithm(BinItemStruct *items, int items_count, int *solution_size, int max_capacity)
{
    int *solution = malloc(0);
    for (int i = 0; i < items_count; i++)
    {
        items[i].profit_weight_ratio = ((float) items[i].profit) / ((float) items[i].weight);
    }

    merge_sort(items, 0, items_count - 1);

    for (int i = 0; i < items_count; i++)
    {
        printf("Profit/Weight: %f\n", items[i].profit_weight_ratio);
    }

    int capacity = 0;
    int i = 0;

    while (capacity < max_capacity && i < items_count)
    {
        if ((capacity + items[i].weight) < max_capacity)
        {
            solution = realloc(solution, (++(*solution_size) + 1)*sizeof(int));
            solution[(*solution_size) - 1] = items[i].index;
            capacity += items[i].weight;
        }
        i++;
    }
    return solution;
}

void run_bin_algorithm(BinProblemStruct *problem)
{
    // READING AND PRE PROCESSING
    FILE* file = fopen(problem->file_path, "r");

    int capacity;

    fscanf(file, "%i", &capacity);
    while (getc(file) != '\n');

    printf("Bag capacity: %i\n", capacity);

    int items_count = 0;
    int number_buffer;
    char read_buffer;
    int post_capacity_offset = ftell(file);

    while ((read_buffer = getc(file)) != '\n' && read_buffer != EOF)
    {
        if (read_buffer == '\t' || read_buffer == ' ') items_count++;
    }

    BinItemStruct *items = malloc(items_count*sizeof(BinItemStruct));
    fseek(file, post_capacity_offset, SEEK_SET);

    for (int i = 0; i < items_count; i++)
    {
        fscanf(file, "%i", &number_buffer);
        items[i].index = i;
        items[i].profit = number_buffer;
    }

    for (int i = 0; i < items_count; i++)
    {
        fscanf(file, "%i", &number_buffer);
        items[i].weight = number_buffer;
    }

    problem->items_amount = items_count;
    problem->capacity = capacity;

    BinItemStruct *items_copy = malloc(items_count*sizeof(BinItemStruct));

    for (int i = 0; i < items_count; i++)
    {
        items_copy[i] = items[i];
    }

    // PROPER ALGORITHM EXECUTION





    clock_t begin = clock();
    problem->solution = bin_algorithm(items_copy, items_count, &(problem->solution_size), capacity);
    clock_t end = clock();

    problem->time_taken = ((double)end - (double)begin) / CLOCKS_PER_SEC;

    problem->items = items;

    free(items_copy);
    fclose(file);
    return;
}

#endif
