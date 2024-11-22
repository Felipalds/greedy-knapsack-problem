#include "bin/bin.c"
#include "stdio.h"
#include <string.h>

int main(int argc, char** args) {
    if (argc <= 2)
    {
        printf("Invalid arguments passed");
        return 1;
    }

    BinProblemStruct bin_problem;

    // READING AND PRE PROCESSING
    FILE* file = fopen(args[2], "r");
    if (file == NULL)
    {
        printf("File not found");
        return 1;
    }

    if(args[1][0] == 'f'){
        bin_problem.algorithm_type = FRACTIONARY;
    } else if(args[1][0] == 'b') {
        bin_problem.algorithm_type = BINARY;
    } else {
        printf("Invalid algorithm type");
        return 1;
    }

    run_bin_algorithm(&bin_problem, file);

    printf("Solution: ");
    for (int i = 0; i < bin_problem.solution_size; i++)
    {
        printf("%i ", bin_problem.solution[i]);
    }
    printf("\n");

    int sum_profit = 0, sum_weight = 0;
    for (int i = 0; i < bin_problem.solution_size; i++)
    {
        sum_profit += bin_problem.items[bin_problem.solution[i]].profit;
        sum_weight += bin_problem.items[bin_problem.solution[i]].weight;
    }

    printf("Bag capacity: %i\n", bin_problem.capacity);
    printf("Total profit: %i\n", sum_profit);
    printf("Total weight: %i\n", sum_weight);
    printf("Time taken: %lf seconds\n", bin_problem.time_taken);
    printf("Items amount: %i\n", bin_problem.items_amount);
    printf("Items taken: %i\n", bin_problem.solution_size);

    free_bin_problem_struct(&bin_problem);
}
