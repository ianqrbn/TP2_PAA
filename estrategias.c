#include <stdio.h>
#include <stdlib.h>

#include "estrategias.h"

Sequencia *preencheSequencia(FILE *nomearq)
{
    Sequencia *sequencia;

    if (nomearq == NULL)
    {
        fprintf(stderr, "ERRO: falha ao abrir arquivo.\n");
        return (NULL);
    }

    fscanf(nomearq, "%d", &sequencia->tamanho);

    sequencia->conteudo = malloc(sequencia->tamanho * sizeof(Pontuacao));

    for (int i = 0; i < sequencia->tamanho; i++)
    {
        fscanf(nomearq, "%d", &sequencia->conteudo[i]);
    }

    return sequencia;
}

void destroiSequencia(Sequencia *sequencia)
{
    free(sequencia->conteudo);
}

Pontuacao maior(Pontuacao a, Pontuacao b)
{
    if (a > b)
    {
        return a;
    }

    return b;
}

Pontuacao tabulation(Sequencia *sequencia)
{
    int tamSequencia = sequencia->tamanho;
    Pontuacao pontuacaoMaxima;
    Pontuacao *pontuacoesMaximas = malloc(tamSequencia * sizeof(Pontuacao));

    pontuacoesMaximas[0] = sequencia->conteudo[0];

    if (sequencia->conteudo[0] > sequencia->conteudo[1])
    {
        pontuacoesMaximas[1] = sequencia->conteudo[0];
    }

    else
    {
        pontuacoesMaximas[1] = sequencia->conteudo[1];
    }

    for (int i = 2; i < tamSequencia; i++)
    {
        pontuacoesMaximas[i] = maior(sequencia->conteudo[i] + pontuacoesMaximas[i - 2], pontuacoesMaximas[i - 1]);
    }

    pontuacaoMaxima = pontuacoesMaximas[tamSequencia - 1];

    free(pontuacoesMaximas);

    return pontuacaoMaxima;
}

Pontuacao maiorPontuacao(int indice, Sequencia *sequencia, Pontuacao pontuacaoMaxima, Pontuacao *pontuacoesMaximas)
{
    if (indice >= sequencia->tamanho)
    {
        return 0;
    }

    if (pontuacoesMaximas[indice] != 0)
    {
        return pontuacoesMaximas[indice];
    }

    pontuacaoMaxima = maior(maiorPontuacao(indice + 2, sequencia, pontuacaoMaxima, pontuacoesMaximas), maiorPontuacao(indice + 3, sequencia, pontuacaoMaxima, pontuacoesMaximas));

    pontuacoesMaximas[indice] = pontuacaoMaxima + sequencia->conteudo[indice];

    return pontuacoesMaximas[indice];
}

Pontuacao memoization(Sequencia *sequencia)
{

    Pontuacao *pontuacoesMaximas = calloc(sequencia->tamanho, sizeof(Pontuacao));
    Pontuacao pontuacaoMaxima;

    pontuacaoMaxima = maior(maiorPontuacao(0, sequencia, 0, pontuacoesMaximas), maiorPontuacao(1, sequencia, 0, pontuacoesMaximas));

    free(pontuacoesMaximas);

    return pontuacaoMaxima;
}