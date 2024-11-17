#include "bin/bin.c"
#include "stdio.h"

int main(int argc, char** args) {
    if (argc <= 1)
    {
        printf("No file path given.\n");
        return 1;
    }

    BinProblemStruct bin_problem;
    bin_problem.file_path = args[1];

    run_bin_algorithm(&bin_problem);

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
