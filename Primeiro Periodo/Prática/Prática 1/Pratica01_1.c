/*Questao 1 pratica 02
/ Lucas Gomes dos Santos
/ Matricula: 20.1.4108
/ Turma 43
*/


#include <stdio.h>

int main()
{
    int x1 , x2 , x3;
    printf("Digite os valores de x1, x2 e x3\n");
    scanf("%d", &x1);
    scanf("%d", &x2);
    scanf("%d", &x3);

    int y;
    y = (x1 + x2 * x2 + x3 * x3) * (x1 + x2 * x2 + x3 * x3)
      + (x1 * x2 * x3) * (x1 * x2 * x3);
    printf("x1 = %d, x2 = %d, x3 = %d\n y = %d\n",x1 , x2 , x3 , y);
    return 0;

}