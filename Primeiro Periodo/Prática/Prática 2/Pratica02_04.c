/*Pratica 4 questao 4
/ Lucas Gomes dos Santos
/ Matricula 20.1.4108
/ Turma 43
*/

#include <stdio.h>

int main()
{
    char sexo, estado, x;
    printf("\nDigite a inicial do sexo:\n");
    scanf(" %c", &sexo);
    printf("\nDigite a inicial do estado civil:\n");
        scanf(" %c", &estado);

    if ((sexo == 'f') || (sexo == 'F'))
    {
        x = 'a';
    }
    else if ((sexo == 'M') || (sexo == 'm'))
    {
        x = 'o';
    }
    else
    {
        printf("\nSexo invalido\n");
    }

    switch (estado)
    {
    case 'C':
    case 'c':
        printf("\nCasad%c\n", x);
        break;

    case 'S':
    case 's':
        printf("\nSolteir%c\n", x);
        break;

    case 'V':
    case 'v':
        printf("\nViuv%c\n", x);
        break;

    case 'D':
    case 'd':
        printf("\nDivorciad%c\n", x);
        break;

    default:
        printf("\nEstado Civil invalido\n");
    }
    return 0;
}