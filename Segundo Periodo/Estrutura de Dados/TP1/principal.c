#include "corretor.h"
#include <stdio.h>

int main()
{
    int n;
    TADsubmissao *S;
    int s;
    int p;

    lerSubmissao(&n);
    S = alocaSubmissao(S,n);
    povoarSubmissao(S,n);
    s = nCorretos(S,n);
    p = nTempo(S,n);
    printSaida(s , p);
    S = desalocaSubmissao(S);

    return 0;

}