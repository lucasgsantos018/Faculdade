/*Pratica 4 questao 1
/ Lucas Gomes dos Santos
/ Matricula 20.1.4108
/ Turma 43
*/

#include <stdio.h>
#include <math.h>

int main(){
    float peso , altura , IMC ;
    printf("Digite o peso em kg:\n"); scanf("%f", &peso);
    printf("Digite a altura em metros:\n"); scanf("%f", &altura);
    IMC = peso / (pow(altura , 2));
    if (IMC < 18.5){
        printf("Abaixo do peso\n");
    }
    else if ((IMC >= 18.5) && (IMC < 25)) {
        printf("Peso Normal\n");
    }
    else if (IMC >= 25 && IMC < 30) {
        printf("Acima do peso.\n");
    }
    else {
        printf("Obeso\n");
    }
        return 0;
}