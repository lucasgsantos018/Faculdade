#include "corretor.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct submissao
{
    char identificador;
    int tempo;
    char julgamento[11];
};

void lerSubmissao (int *n)
{
    scanf("%d", n);
}

TADsubmissao *alocaSubmissao(TADsubmissao *S,int n)
{
    S = (TADsubmissao*) malloc (n * sizeof(TADsubmissao));

    if (S == NULL)
    {
        printf("Memoria insuficiente\n");
        exit(1);
    }

    return S;
}

TADsubmissao *desalocaSubmissao(TADsubmissao *S)
{
    free(S);

    return NULL;
}

void povoarSubmissao(TADsubmissao *S, int n)
{
    for(int i = 0; i < n; i++)
    {

        scanf(" %c", &S[i].identificador);
        scanf("%d", &S[i].tempo);
        scanf(" %s", S[i].julgamento);

    }

}

int nCorretos(TADsubmissao *S, int n)
{

    int aux = 0;
    
    for(int i = 0; i < n ; i++)
    {
        if(strcmp(S[i].julgamento, "correto") == 0)
        { 
            aux++;
        }
        
    }
    
    return aux;

}

int nTempo(TADsubmissao *S, int n)
{ 

    int aux1 = 0, aux2 = 0, tempo = 0;
    char ident[26];

    for(int i = 0; i < n; i++)
    {
        if(strcmp(S[i].julgamento, "correto") == 0)
        {
            ident[aux1] = S[i].identificador;
            aux1++;
        }
    }


    for(int i = 0; i < n || aux2 != aux1 ; i++)
    {

        if(ident[aux2] == S[i].identificador)
        {
            
            if(strcmp(S[i].julgamento, "incompleto") == 0)
            {
                tempo += 20;
            }
            else if(strcmp(S[i].julgamento, "correto") == 0)
            {
                tempo += S[i].tempo;
                aux2++;
                i = 0 ;
            }


        }


    }
    
    return tempo;

}

void printSaida(int s, int p)
{

    printf("%d %d\n", s , p);

}