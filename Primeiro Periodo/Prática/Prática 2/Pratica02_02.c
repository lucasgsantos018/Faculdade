/*Pratica 4 questao 2
/ Lucas Gomes dos Santos
/ Matricula 20.1.4108
/ Turma 43
*/

#include <stdio.h>

int main(){
    int idade;
    printf("Digite a idade:\n");
    scanf("%d", &idade);
    if (idade <= 10){
        printf("O valor a ser pago eh R$90.00\n");
    }
    else if ((idade > 10 ) && ( idade <= 29 )){
        printf("O valor a ser pago eh R$170.00\n");
    }
    else if ((idade > 29) && ( idade <= 45 )){
        printf("O valor a ser pago eh R$290.00\n");
    }
    else if ((idade > 45 ) && ( idade <= 59 )){
        printf("O valor a ser pago eh R$400.00\n");
    }
    else if ((idade > 59 ) && ( idade <= 65)){
        printf("O valor a ser cobrado eh R$515.00\n");
    }
    else {
        printf("O valor a ser cobrado eh R$695.00\n");
    }
    return 0;
        
}