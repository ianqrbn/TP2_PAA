#ifndef BRUTA_H
#define BRUTA_H

#include <stdlib.h>
#include <stdio.h>

typedef int Pontuacao;

typedef struct
{

    Pontuacao *elementosSeq;
    int tamanho;

} Sequencia;

Pontuacao maior(Pontuacao a, Pontuacao b);

Pontuacao maiorPontuacao(int indice, Sequencia *sequencia, Pontuacao maiorPon);

#endif