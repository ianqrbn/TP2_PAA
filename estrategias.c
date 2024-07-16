#include <stdio.h>
#include <stdlib.h>

#include "estrategias.h"

Sequencia *preencheSequencia(FILE *nomearq)
{

    // Comeca a contar o tempo
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

// ESTRATEGIA D

Pontuacao tabulation(Sequencia *sequencia)
{

    // Comeca a contar o tempo
    tempo tempoInicio = tempoAtual();

    int tamSequencia = sequencia->tamanho;
    Pontuacao pontuacaoMaxima;
    Pontuacao *pontuacoesMaximas = malloc(tamSequencia * sizeof(Pontuacao)); // armazena os resultados dos subproblemas

    pontuacoesMaximas[0] = sequencia->conteudo[0]; // primeiro elemento da sequencia vira a primeira pontuacao maxima

    if (sequencia->conteudo[0] > sequencia->conteudo[1]) // maior entre peimeiro e segundo elemento vira a segunda pontuacao maxima
    {
        pontuacoesMaximas[1] = sequencia->conteudo[0];
    }

    else
    {
        pontuacoesMaximas[1] = sequencia->conteudo[1];
    }

    for (int i = 2; i < tamSequencia; i++)
    // para os n-2 itens da sequencia verificamos se o subresultado 2 posicoes antes somado com ak eh maior que o subresultado uma posicao antes
    {
        pontuacoesMaximas[i] = maior(sequencia->conteudo[i] + pontuacoesMaximas[i - 2], pontuacoesMaximas[i - 1]);
    }

    pontuacaoMaxima = pontuacoesMaximas[tamSequencia - 1]; // resultado fica armazenado na ultima posicao do vetor

    // Termina de contar o tempo
    tempo tempoFinal = tempoAtual();

    double tempoTotal = tempoDecorrido(tempoInicio.tv, tempoFinal.tv);

    printf("Tempo de execucao:\n");
    imprimeTempos(tempoInicio, tempoFinal);

    free(pontuacoesMaximas);

    return pontuacaoMaxima;
}

// ESTRATEGIA A

Pontuacao maiorPontuacao(int indice, Sequencia *sequencia, Pontuacao pontuacaoMaxima, Pontuacao **pontuacoesMaximas)
{
    if (indice >= sequencia->tamanho)
    {
        return 0;
    }

    if (pontuacoesMaximas[1][indice] != 0) // se o subproblema ja tiver sido calculado apenas eh retornado
    {
        return pontuacoesMaximas[0][indice];
    }
    // chamadas recursivas para 2 e 3 posicoes a frente
    pontuacaoMaxima = maior(maiorPontuacao(indice + 2, sequencia, pontuacaoMaxima, pontuacoesMaximas), maiorPontuacao(indice + 3, sequencia, pontuacaoMaxima, pontuacoesMaximas));

    pontuacoesMaximas[0][indice] = pontuacaoMaxima + sequencia->conteudo[indice];

    pontuacoesMaximas[1][indice] = 1; // marca o subproblema como ja calculado

    return pontuacoesMaximas[0][indice];
}

Pontuacao memoization(Sequencia *sequencia)
{
    // Comeca a contar o tempo
    tempo tempoInicio = tempoAtual();

    Pontuacao pontuacaoMaxima;

    // matriz que armazena os resultados dos subproblemas e se eles ja foram calculados
    Pontuacao **pontuacoesMaximas = calloc(2, sizeof(Pontuacao *));
    for (int i = 0; i < 2; i++)
    {
        pontuacoesMaximas[i] = calloc(sequencia->tamanho, sizeof(Pontuacao));
    }

    // inicia as funcoes recursivas com 0 e 1 e pega o maior entre elas
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