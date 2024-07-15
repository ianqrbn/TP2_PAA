#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <bits/getopt_core.h>

#include "tempo.h"

#include "estrategias.h"

int main(int argc, char *argv[2])
{

    FILE *input_file = fopen(argv[2], "r");
    char *estrategia = argv[1];

    Sequencia *sequencia = preencheSequencia(input_file);

    if (estrategia == "D")
    {
        printf("%d\n", tabulation(sequencia));

        destroiSequencia(sequencia);
        return 0;
    }

    printf("%d\n", memoization(sequencia));

    fclose(input_file);
    destroiSequencia(sequencia);
    return 0;
}