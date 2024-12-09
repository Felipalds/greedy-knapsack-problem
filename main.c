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
    char *output = "";

    if(args[1][0] == 'f'){
        bin_problem.algorithm_type = FRACTIONARY;
        output = "frac_result.csv";
    } else if(args[1][0] == 'b') {
        bin_problem.algorithm_type = BINARY;
    } else {
        printf("Invalid algorithm type");
        output = "bin_result.csv";
        return 1;
    }

    FILE *csv_file = fopen(output, "a+");
    run_bin_algorithm(&bin_problem, file);

    int sum_profit = 0, sum_weight = 0;
    for (int i = 0; i < bin_problem.solution_size; i++)
    {
        int new_weight = sum_weight + bin_problem.items[bin_problem.solution[i]].weight;
        if (new_weight > bin_problem.capacity)
        {
            int espaco = bin_problem.capacity - sum_weight;
            int proportional_profit = (bin_problem.items[bin_problem.solution[i]].profit * espaco) / bin_problem.items[bin_problem.solution[i]].weight;
            sum_profit += proportional_profit;
            sum_weight = bin_problem.capacity;
        } else
        {
            sum_weight = new_weight;
            sum_profit += bin_problem.items[bin_problem.solution[i]].profit;
        }
    }

    fprintf(csv_file, "%s, %lf, %i, %i, %i, %i\n", args[2], bin_problem.time_taken, bin_problem.items_amount, bin_problem.capacity, sum_profit, sum_weight);

    free_bin_problem_struct(&bin_problem);
}
