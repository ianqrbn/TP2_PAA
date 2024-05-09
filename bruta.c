#include <stdio.h>
#include <stdlib.h>

#include "bruta.h"

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