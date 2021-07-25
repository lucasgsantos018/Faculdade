/*Pratica 4 questao 3
/ Lucas Gomes dos Santos
/ Matricula 20.1.4108
/ Turma 43
*/

#include <stdio.h>

int main (){
    float salario , novo , diferenca ;
    int cod ;
    printf("Digite o valor do salario:\n"); scanf ("%f", &salario);
    printf("Digite o codigo:\n"); scanf ("%d", &cod);

    switch (cod) {
        case 100:
        novo = salario + (salario * 0.03);
        printf ("Salario antigo:%.2f\n", salario );
        printf ("Salario novo:%.2f\n", novo );
        diferenca = novo - salario ;
        printf ("Diferenca:%.2f\n", diferenca );
        break;

        case 101:
        novo = salario + ( salario * 0.05 );
        printf ("Salario antigo:%.2f\n", salario );
        printf ("Salario novo:%.2f\n", novo );
        diferenca = novo - salario ;
        printf ("Diferenca:%.2f\n", diferenca );
        break;

        case 102:
        novo = salario + (salario * (7.5/100));
        printf ("Salario antigo:%.2f\n", salario );
        printf ("Salario novo:%.2f\n", novo );
        diferenca = novo - salario ;
        printf ("Diferenca:%.2f\n", diferenca );
        break;

        case 201:
        novo = salario + (salario * 0.1 );
        printf ("Salario antigo:%.2f\n", salario );
        printf ("Salario novo:%.2f\n", novo );
        diferenca = novo - salario ;
        printf ("Diferenca:%.2f\n", diferenca );
        break;

        default:
        novo = salario + (salario * 0.15);
        printf ("Salario antigo:%.2f\n", salario );
        printf ("Salario novo:%.2f\n", novo );
        diferenca = novo - salario ;
        printf ("Diferenca:%.2f\n", diferenca );

    }
    return 0;
}
