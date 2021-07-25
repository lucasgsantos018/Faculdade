/*Questao 3 pratica 02
/ Lucas Gomes dos Santos
/ Matricula: 20.1.4108
/ Turma 43
*/

#include <stdio.h>

int main()
{
    float Celsius , Fahrenheit , Kelvin ;
    printf("Digite o valor em Celsius que sera convertido para Fahrenheit e Kelvin:\n");
    scanf("%f", &Celsius ); 
    Fahrenheit = (9 * Celsius) / 5 + 32 ;
    Kelvin = Celsius + 273.15 ;
    printf("Fahrenheit = %f , Kelvin = %f\n", Fahrenheit , Kelvin );
    return 0;
}