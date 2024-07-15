#include <stdio.h>
#include <stdlib.h>

#include "estrategias.h"

Sequencia *preencheSequencia(FILE *nomearq)
{   

    // Commeca a contar o tempo
    tempo tempoInicio = tempoAtual();

    Sequencia *sequencia = malloc(sizeof(Sequencia));

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

    // Para de contar o tempo
    tempo tempoFinal = tempoAtual();

    printf("Tempo de leitura:\n");
    imprimeTempos(tempoInicio, tempoFinal);

    return sequencia;
}

void destroiSequencia(Sequencia *sequencia)
{
    free(sequencia->conteudo);
    free(sequencia);
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

    // Comeca a contar o tempo
    tempo tempoInicio = tempoAtual();

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
    
    // Termina de contar o tempo
    tempo tempoFinal = tempoAtual();
    
    double tempoTotal = tempoDecorrido(tempoInicio.tv, tempoFinal.tv);

    printf("Tempo de execucao:\n");
    imprimeTempos(tempoInicio, tempoFinal);

    free(pontuacoesMaximas);

    return pontuacaoMaxima;
}

Pontuacao maiorPontuacao(int indice, Sequencia *sequencia, Pontuacao pontuacaoMaxima, Pontuacao **pontuacoesMaximas)
{
    if (indice >= sequencia->tamanho)
    {
        return 0;
    }

    if (pontuacoesMaximas[1][indice] != 0)
    {
        return pontuacoesMaximas[0][indice];
    }

    pontuacaoMaxima = maior(maiorPontuacao(indice + 2, sequencia, pontuacaoMaxima, pontuacoesMaximas), maiorPontuacao(indice + 3, sequencia, pontuacaoMaxima, pontuacoesMaximas));

    pontuacoesMaximas[0][indice] = pontuacaoMaxima + sequencia->conteudo[indice];

    pontuacoesMaximas[1][indice] = 1;

    return pontuacoesMaximas[0][indice];
}

Pontuacao memoization(Sequencia *sequencia)
{
    // Comeca a contar o tempo
    tempo tempoInicio = tempoAtual();

    Pontuacao pontuacaoMaxima;

    Pontuacao **pontuacoesMaximas = calloc(2, sizeof(Pontuacao *));
    for (int i = 0; i < 2; i++)
    {
        pontuacoesMaximas[i] = calloc(sequencia->tamanho, sizeof(Pontuacao));
    }

    pontuacaoMaxima = maior(maiorPontuacao(0, sequencia, 0, pontuacoesMaximas), maiorPontuacao(1, sequencia, 0, pontuacoesMaximas));

    for (int i = 0; i < 2; i++)
    {
        free(pontuacoesMaximas[i]);
    }

    // Termina de contar o tempo
    tempo tempoFinal = tempoAtual();
    
    double tempoTotal = tempoDecorrido(tempoInicio.tv, tempoFinal.tv);

    printf("Tempo de execucao:\n");
    imprimeTempos(tempoInicio, tempoFinal);

    free(pontuacoesMaximas);

    return pontuacaoMaxima;
}