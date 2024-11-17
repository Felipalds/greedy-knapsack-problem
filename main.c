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
}
