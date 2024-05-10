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

Pontuacao maiorPontuacao(int indice, Sequencia *sequencia, Pontuacao maiorPon, Pontuacao *guardaMaiorPon)
{
    if (indice >= sequencia->tamanho)
    {
        return 0;
    }

    if (guardaMaiorPon[indice] != 0)
    {
        return guardaMaiorPon[indice];
    }

    maiorPon = maior(maiorPontuacao(indice + 2, sequencia, maiorPon, guardaMaiorPon), maiorPontuacao(indice + 3, sequencia, maiorPon, guardaMaiorPon));

    guardaMaiorPon[indice] = maiorPon + sequencia->elementosSeq[indice];

    return guardaMaiorPon[indice];
}