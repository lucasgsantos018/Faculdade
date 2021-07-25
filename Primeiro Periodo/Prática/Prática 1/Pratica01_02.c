/*Questao 2 pratica 02
/ Lucas Gomes dos Santos
/ Matricula: 20.1.4108
/ Turma 43
*/

#include <stdio.h>

int main()
{
    float peso , altura;
    printf("Para calculo do IMC insira respectivamente o peso(kg) e a altura(m):\n");
    scanf("%f", &peso );
    scanf("%f", &altura );
    float IMC;
    IMC = (peso / (altura * altura));
    printf("IMC = %.2f\n", IMC );
    return 0;
}