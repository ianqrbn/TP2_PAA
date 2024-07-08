#ifndef ESTRATEGIAS_H
#define ESTRATEGIAS_H

#include <stdio.h>
#include <stdlib.h>

typedef int Pontuacao;

typedef struct
{

    Pontuacao *conteudo;
    int tamanho;

} Sequencia;

Sequencia *preencheSequencia(FILE *nomearq);

void destroiSequencia(Sequencia *sequencia);

Pontuacao tabulation(Sequencia *sequencia);

Pontuacao memoization(Sequencia *sequencia);

#endif