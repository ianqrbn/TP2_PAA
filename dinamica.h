#ifndef DINAMICA_H
#define DINAMICA_H

#include <stdlib.h>
#include <stdio.h>

typedef int Pontuacao;

typedef struct
{

    Pontuacao *elementosSeq;
    int tamanho;

} Sequencia;

Pontuacao max(int indice, Pontuacao *elementosSeq, Pontuacao *maxPontuacao);

Pontuacao dinamica(Sequencia *sequencia);

Sequencia *preencheSequencia(FILE *nomearq);

#endif