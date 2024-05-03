#include <stdio.h>
#include <stdlib.h>

#include "dinamica.h"

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

    fscanf(nomearq, "%d", sequencia->tamanho);

    sequencia->elementosSeq = malloc(sequencia->tamanho * sizeof(Pontuacao));

    for (int i = 0; i < sequencia->tamanho; i++)
    {
        fscanf(nomearq, "%d", &sequencia->elementosSeq[i]);
    }

    return sequencia;
}