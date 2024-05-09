#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <bits/getopt_core.h>

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

    for (int i = 0; i < sequencia->tamanho; i++)
    {
        fscanf(nomearq, "%d", &sequencia->elementosSeq[i]);
    }

    return sequencia;
}

Pontuacao maior(Pontuacao a, Pontuacao b)
{
    if (a > b)
    {
        return a;
    }

    return b;
}

Pontuacao maiorPontuacao(int indice, Sequencia *sequencia, Pontuacao maiorPon)
{
    if (indice >= sequencia->tamanho)
    {
        return 0;
    }

    maiorPon = maior(maiorPontuacao(indice + 2, sequencia, maiorPon), maiorPontuacao(indice + 3, sequencia, maiorPon));

    return maiorPon + sequencia->elementosSeq[indice];
}

int main(int argc, char *argv[2])
{

    FILE *input_file = NULL;
    FILE *output_file = stderr;
    char c;

    while ((c = getopt(argc, argv, "i:o:")) != -1)
    {
        switch (c)
        {
        case 'i':
            input_file = fopen(optarg, "r");
            if (!input_file)
                printf("Falha ao abrir arquivo %s\n", optarg);
            break;
        case 'o':
            output_file = fopen(optarg, "w");
            if (!output_file)
                printf("Falha ao abrir arquivo %s\n", optarg);
            break;
        default:;
            ;
        }
    }

    Sequencia *sequencia = preencheSequencia(input_file);
    for (int i = 0; i < sequencia->tamanho; i++)
    {
        printf("%d ", sequencia->elementosSeq[i]);
    }
    printf("\n");

    printf("%d\n", dinamica(sequencia));

    printf("%d\n", maior(maiorPontuacao(0, sequencia, 0), maiorPontuacao(1, sequencia, 0)));
}