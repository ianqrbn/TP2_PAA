#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <bits/getopt_core.h>

#include "tempo.h"

typedef int Pontuacao;

typedef struct
{

    Pontuacao *elementosSeq;
    int tamanho;

} Sequencia;

Pontuacao max(int indice, Pontuacao *sequencia, Pontuacao *maxPontuacao)
{
    if (sequencia[indice] + maxPontuacao[indice - 2] > maxPontuacao[indice - 1])
    {
        return sequencia[indice] + maxPontuacao[indice - 2];
    }

    return maxPontuacao[indice - 1];
}

Pontuacao dinamica(Sequencia *sequencia)
{
    int tamSequencia = sequencia->tamanho;
    Pontuacao *maxPontuacao = malloc(tamSequencia * sizeof(Pontuacao));

    maxPontuacao[0] = sequencia->elementosSeq[0];

    // Comeca a contar o tempo
    tempo tempoInicio = tempoAtual();

    if (sequencia->elementosSeq[0] > sequencia->elementosSeq[1])
    {
        maxPontuacao[1] = sequencia->elementosSeq[0];
    }

    else
    {
        maxPontuacao[1] = sequencia->elementosSeq[1];
    }

    for (int i = 2; i < tamSequencia; i++)
    {
        maxPontuacao[i] = max(i, sequencia->elementosSeq, maxPontuacao);
    }

    tempo tempoFinal = tempoAtual();
    // Termina de contar o tempo

    double tempoTotal = tempoDecorrido(tempoInicio.tv, tempoFinal.tv);

    printf("Tempo de execucao:\n");
    imprimeTempos(tempoInicio, tempoFinal);

    return maxPontuacao[tamSequencia - 1];
}

Sequencia *preencheSequencia(FILE *nomearq)
{
    Sequencia *sequencia;

    if (nomearq == NULL)
    {
        fprintf(stderr, "ERRO: falha ao abrir arquivo.\n");
        return (NULL);
    }

    fscanf(nomearq, "%d", &sequencia->tamanho);

    sequencia->elementosSeq = malloc(sequencia->tamanho * sizeof(Pontuacao));

    tempo tempoInicio = tempoAtual();

    for (int i = 0; i < sequencia->tamanho; i++)
    {
        fscanf(nomearq, "%d", &sequencia->elementosSeq[i]);
    }

    tempo tempoFinal = tempoAtual();
    printf("Tempo de leitura:\n");
    imprimeTempos(tempoInicio, tempoFinal);

    return sequencia;
}

// int main(int argc, char *argv[2])
// {

//     FILE *input_file = NULL;
//     FILE *output_file = stderr;
//     char c;

//     while ((c = getopt(argc, argv, "i:o:")) != -1)
//     {
//         switch (c)
//         {
//         case 'i':
//             input_file = fopen(optarg, "r");
//             if (!input_file)
//                 printf("Falha ao abrir arquivo %s\n", optarg);
//             break;
//         case 'o':
//             output_file = fopen(optarg, "w");
//             if (!output_file)
//                 printf("Falha ao abrir arquivo %s\n", optarg);
//             break;
//         default:;
//             ;
//         }
//     }

//     Sequencia *sequencia = preencheSequencia(input_file);

//     Pontuacao *guardaMaiorPon = calloc(sequencia->tamanho, sizeof(Pontuacao));

//     for (int i = 0; i < sequencia->tamanho; i++)
//     {
//         printf("%d ", sequencia->elementosSeq[i]);
//     }
//     printf("\n");

//     printf("%d\n", dinamica(sequencia));

//     printf("%d\n", maior(maiorPontuacao(0, sequencia, 0, guardaMaiorPon), maiorPontuacao(1, sequencia, 0, guardaMaiorPon)));
// }

int main(int arc, char* argv[1]){

    FILE *input_file = fopen(argv[0], "r");
    char estrategia = argv[1];

    Sequencia *sequencia = preencheSequencia(input_file);
    Pontuacao *guardaMaiorPon = calloc(sequencia->tamanho, sizeof(Pontuacao));

    for (int i = 0; i < sequencia->tamanho; i++)
    {
        printf("%d ", sequencia->elementosSeq[i]);
    }
    printf("\n");

    if(estrategia == 'D') {
        printf("%d\n", dinamica(sequencia));
        return 0;
    }
    
    printf("%d\n", maior(maiorPontuacao(0, sequencia, 0, guardaMaiorPon), maiorPontuacao(1, sequencia, 0, guardaMaiorPon)));
    //

}