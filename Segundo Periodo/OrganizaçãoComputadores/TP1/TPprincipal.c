#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 1000

void menu();

//Função para alocar e desalocar a memoria das instruções
int **alocaMemoriaInstrucoes(void);
int *liberaMemoriaInstrucoes(int **memoriaInstrucoes);

//Função para alocar e desalocar a memória dos dados
int *alocaMemoriaDados(void);
int *liberaMemoriaDados(int *memoriaDados);

// Funções relacionadas a construção da máquina
void montarRam(int *memoriaDados);
void montarInstrucoesProgramaAleatorio(int **memoriaInstrucoes, int *memoriaDados);
void maquinaInterpretada(int **memoriaInstrucoes, int *memoriaDados);

// Função principal
void lerComando(int **memoriaInstrucoes, int *memoriaDados);

// Funções de equação
void montarSoma(int **memoriaInstrucoes, int *memoriaDados, int aux1 , int aux2);
void montarSubtracao(int **memoriaInstrucoes, int *memoriaDados, int aux1 , int aux2);
void montarMultiplicacao(int **memoriaInstrucoes, int *memoriaDados, int multiplicando , int multiplicador);
void montarDivisao(int **memoriaInstrucoes, int *memoriaDados, int dividendo , int divisor);
void montarRaiz(int **memoriaInstrucoes, int *memoriaDados, int radicando);
void montarPotenciacao(int **memoriaInstrucoes, int *memoriaDados, int base , int expoente);
void montarSomaCubos(int **memoriaInstrucoes, int *memoriaDados, int aux1 , int aux2);
void montarPitagoras(int **memoriaInstrucoes, int *memoriaDados, int lado1 , int lado2);
void montarAreaQuadrado(int **memoriaInstrucoes, int *memoriaDados, int lado);
void montarAreaRetangulo(int **memoriaInstrucoes, int *memoriaDados, int lado1 , int lado2);
void montarAreaTriangulo(int **memoriaInstrucoes, int *memoriaDados, int base , int altura);
void montarAreaLosango(int **memoriaInstrucoes, int *memoriaDados, int diagM , int diagm);

// Função de retorno
int* trazerRam(int **memoriaInstrucoes, int *memoriaDados);



int main()
{

    int **memoriaInstrucoes;
    int *memoriaDados;

    memoriaInstrucoes = alocaMemoriaInstrucoes();
    memoriaDados = alocaMemoriaDados();

    montarRam(memoriaDados);

    menu();

    lerComando(memoriaInstrucoes,memoriaDados);

    liberaMemoriaInstrucoes(memoriaInstrucoes);
    liberaMemoriaDados(memoriaDados);

    return 0;

}


int **alocaMemoriaInstrucoes(void)
{
    int **aux1 = (int**) malloc (M * sizeof(int*));

    for(int i = 0; i < M ; i++)
    {
        aux1[i] = (int*) malloc (4 * sizeof(int));
    }

    if(aux1 == NULL)
    {
        printf("Memória insuficiente\n");
        exit(1);
    }
    
    return aux1;
}

int *liberaMemoriaInstrucoes(int **memoriaInstrucoes)
{
    for(int i = 0; i < M ; i++)
    {
        free(memoriaInstrucoes[i]);
    }
    free(memoriaInstrucoes);
    return NULL;
}

int *alocaMemoriaDados(void)
{
    int *aux2 = (int*) malloc (M * sizeof(int));

    if(aux2 == NULL)
    {
        printf("Memória insuficiente\n");
        exit(1);
    }
    
    return aux2;
}

int *liberaMemoriaDados(int *memoriaDados)
{
    free(memoriaDados);
    return NULL;
}

void menu()
{
    printf("\n - Menu -\n\n");
    printf("-1  - Sair\n");
    printf("-2  - Imprimir menu novamente\n");
    printf(" 0  - Soma\n");
    printf(" 1  - Subtração\n");
    printf(" 2  - Multiplicação\n");
    printf(" 3  - Divisão\n");
    printf(" 4  - Raiz\n");
    printf(" 5  - Potenciação\n");
    printf(" 6  - Aleatório\n");
    printf(" 7  - Somar cubos\n");
    printf(" 8  - Pitágoras\n");
    printf(" 9  - Área de quadrado\n");
    printf(" 10 - Área de retangulo\n");
    printf(" 11 - Área de triângulo\n");
    printf(" 12 - Área de losango\n\n");

}

void lerComando(int **memoriaInstrucoes, int *memoriaDados)
{
    int operador = 0, aux1 = 0 , aux2 = 0;
    int* ram0;

    for(;;)
    {
        scanf("%d", &operador);
        
        if (operador >= -2 && operador <= 12 )
        {
            switch(operador)
            {

                case 0:{
                    scanf("%d %d", &aux1, &aux2);

                    montarSoma(memoriaInstrucoes,memoriaDados,aux1,aux2);

                    ram0 = trazerRam(memoriaInstrucoes,memoriaDados);

                    printf("A soma é igual a %d\n\n", ram0[1]);

                    break;
                    
                }

                case 1:{
                    scanf("%d %d", &aux1, &aux2);

                    montarSubtracao(memoriaInstrucoes,memoriaDados,aux1,aux2);

                    ram0 = trazerRam(memoriaInstrucoes,memoriaDados);

                    printf("A subtração é igual a %d\n\n", ram0[1]);

                    break;
                }

                case 2:{
                    scanf("%d %d", &aux1, &aux2);

                    montarMultiplicacao(memoriaInstrucoes,memoriaDados,aux1,aux2);

                    ram0 = trazerRam(memoriaInstrucoes,memoriaDados);

                    printf("A multiplicação é igual a %d\n\n", ram0[1]);

                    break;
                }

                case 3:{
                    scanf("%d %d", &aux1, &aux2);

                    montarDivisao(memoriaInstrucoes,memoriaDados,aux1,aux2);

                    ram0 = trazerRam(memoriaInstrucoes,memoriaDados);

                    printf("A divisão é igual a %d\n\n", ram0[1]);

                    break;
                }

                case 4:{
                    scanf("%d", &aux1);

                    montarRaiz(memoriaInstrucoes,memoriaDados,aux1);

                    ram0 = trazerRam(memoriaInstrucoes,memoriaDados);

                    printf("A raiz é igual a %d\n\n", ram0[1]);

                    break;
                }

                case 5:{
                    scanf("%d %d", &aux1, &aux2);

                    montarPotenciacao(memoriaInstrucoes,memoriaDados,aux1,aux2);

                    ram0 = trazerRam(memoriaInstrucoes,memoriaDados);

                    printf("A potência é igual a %d\n\n", ram0[1]);

                    break;
                }

                case 6:{
                    montarRam(memoriaDados);

                    montarInstrucoesProgramaAleatorio(memoriaInstrucoes, memoriaDados);

                    break;
                }

                case 7:{
                    scanf("%d %d", &aux1 , &aux2);

                    montarSomaCubos(memoriaInstrucoes,memoriaDados,aux1,aux2);

                    ram0 = trazerRam(memoriaInstrucoes,memoriaDados);

                    printf("A soma entre os cubos é igual a %d\n\n", ram0[1]);

                    break;
                }

                case 8:{
                    scanf("%d %d", &aux1 , &aux2);

                    montarPitagoras(memoriaInstrucoes,memoriaDados,aux1,aux2);

                    ram0 = trazerRam(memoriaInstrucoes,memoriaDados);

                    printf("A hipoternusa é igual a %d\n\n", ram0[1]);

                    break;
                }

                case 9:{
                    scanf("%d", &aux1);

                    montarAreaQuadrado(memoriaInstrucoes,memoriaDados,aux1);

                    ram0 = trazerRam(memoriaInstrucoes,memoriaDados);

                    printf("A área do quadrado é igual a %d\n\n", ram0[1]);

                    break;
                }

                case 10:{
                    scanf("%d %d", &aux1 , &aux2);

                    montarAreaRetangulo(memoriaInstrucoes,memoriaDados,aux1,aux2);

                    ram0 = trazerRam(memoriaInstrucoes,memoriaDados);

                    printf("A área do retangulo é igual a %d\n\n", ram0[1]);

                    break;
                }

                case 11:{
                    scanf("%d %d", &aux1 , &aux2);

                    montarAreaTriangulo(memoriaInstrucoes,memoriaDados,aux1,aux2);

                    ram0 = trazerRam(memoriaInstrucoes,memoriaDados);

                    printf("A área do triângulo é igual a %d\n\n", ram0[1] / 2);

                    break;
                }

                case 12:{
                    scanf("%d %d", &aux1 , &aux2);

                    montarAreaLosango(memoriaInstrucoes,memoriaDados,aux1,aux2);

                    ram0 = trazerRam(memoriaInstrucoes,memoriaDados);

                    printf("A área do losango é igual a %d\n\n", ram0[1]);

                    break;
                }

                case -2:{
                    menu();
                    break;
                }

                case -1:{
                    liberaMemoriaDados(memoriaDados);

                    liberaMemoriaInstrucoes(memoriaInstrucoes);

                    printf("\nVocê saiu!\n\n");

                    exit(1);
                }

            }
        }
        else
        {
            printf("Operador inválido, digite novamente:\n\n");
        }
        
    }


}

void montarRam(int *memoriaDados)
{
    // A ram é preenchida com números aleatórios

    srand(time(NULL));

    for(int i = 0; i < M ; i++)
    {
        memoriaDados[i] = rand() % M;
    }

}


void montarInstrucoesProgramaAleatorio(int **memoriaInstrucoes, int *memoriaDados)
{
    // Programa montado de forma aleatória

    for(int i = 0; i < M ; i++)
    {
        memoriaInstrucoes[i][0] = rand() % 3 - 1 ;
        for(int j = 1; j < 4 ; j++)
        {
            memoriaInstrucoes[i][j] = rand() % M ;
        }
        
    }

    for(int k = 0 ; k < 4 ; k++)
    {
        memoriaInstrucoes[M - 1][k] = -1 ;
    }

    maquinaInterpretada(memoriaInstrucoes, memoriaDados);

}

void maquinaInterpretada(int **memoriaInstrucoes, int *memoriaDados)
{

    int opcode = 0 ;
    int control = 0 ;

    int content1 = 0;
    int content2 = 0;

    for(;;)
    {
        opcode = memoriaInstrucoes[control][0];

        if(opcode != -1)
        {

            switch(opcode)
            {
                // a RAM esta recebendo as instruções nesse momento
                
                
                case 0: {// Somar

                    int end1 = memoriaInstrucoes[control][1] ;
                    int end2 = memoriaInstrucoes[control][2] ;

                    content1 = memoriaDados[end1];
                    content2 = memoriaDados[end2];

                    int end3 = memoriaInstrucoes[control][3] ;
                    
                    int soma = content1 + content2; // Buscar na RAM

                    printf("Somando %d com %d e gerando %d\n\n",content1, content2, soma);
                    
                    memoriaDados[end3] = soma; // Salvando resultado na RAM

                    break;
                }

                case 1: { // Subtrair

                    int end1 = memoriaInstrucoes[control][1];
                    int end2 = memoriaInstrucoes[control][2];

                    content1 = memoriaDados[end1];
                    content2 = memoriaDados[end2];

                    int end3 = memoriaInstrucoes[control][3];
                    
                    int subtracao = content1 - content2; // Buscar na RAM
                    
                    printf("Subtração %d com %d e gerando %d\n\n",content1, content2, subtracao);
                    
                    memoriaDados[end3] = subtracao; // Salvando resultado na RAM

                    break;
                }

                case 2: { // levar para RAM

                    // O conteudo de memoriaInstruções[control][1], está sendo levado para a RAM , no endereço memoriaInstruções[control][2]
                    int content  = memoriaInstrucoes[control][1];
                    int endereco = memoriaInstrucoes[control][2];

                    memoriaDados[endereco] = content ;


                    break;
                }

                case 3: { // trazer da RAM
                    
                    memoriaInstrucoes[control][1] = memoriaDados[memoriaInstrucoes[control][2]]; // pega da RAM um conteúdo que você guardou com OP CODE 2

                    break;
                }
                
            }

        } 
        
        else
        {
            break;
        }

        control++;
        
    }

    

}

int* trazerRam(int **memoriaInstrucoes, int *memoriaDados)
{
    return memoriaDados;
}

void montarSoma(int **memoriaInstrucoes, int *memoriaDados, int aux1 , int aux2)
{
    // Levar para RAM
    memoriaInstrucoes[0][0] =  2; 
    memoriaInstrucoes[0][1] = aux1;
    memoriaInstrucoes[0][2] =  0;
    memoriaInstrucoes[0][3] = -1;

    memoriaInstrucoes[1][0] =  2;
    memoriaInstrucoes[1][1] = aux2;
    memoriaInstrucoes[1][2] =  1;
    memoriaInstrucoes[1][3] = -1;
    // Soma
    memoriaInstrucoes[2][0] = 0;
    memoriaInstrucoes[2][1] = 0; 
    memoriaInstrucoes[2][2] = 1;
    memoriaInstrucoes[2][3] = 1;
    
    memoriaInstrucoes[3][0] = -1;
    memoriaInstrucoes[3][1] = -1;
    memoriaInstrucoes[3][2] = -1;
    memoriaInstrucoes[3][3] = -1;

    maquinaInterpretada(memoriaInstrucoes,memoriaDados);

}


void montarSubtracao(int **memoriaInstrucoes, int *memoriaDados, int aux1 , int aux2)
{

    memoriaInstrucoes[0][0] = 2;
    memoriaInstrucoes[0][1] = aux1;
    memoriaInstrucoes[0][2] = 0;
    memoriaInstrucoes[0][3] = -1;

    memoriaInstrucoes[1][0] = 2;
    memoriaInstrucoes[1][1] = aux2;
    memoriaInstrucoes[1][2] = 1;
    memoriaInstrucoes[1][3] = -1;
    // Subtrai
    memoriaInstrucoes[2][0] = 1;
    memoriaInstrucoes[2][1] = 0;
    memoriaInstrucoes[2][2] = 1;
    memoriaInstrucoes[2][3] = 1;

    memoriaInstrucoes[3][0] = -1;
    memoriaInstrucoes[3][1] = -1; 
    memoriaInstrucoes[3][2] = -1;
    memoriaInstrucoes[3][3] = -1;

    maquinaInterpretada(memoriaInstrucoes,memoriaDados);

}

void montarMultiplicacao(int **memoriaInstrucoes, int *memoriaDados, int multiplicando , int multiplicador)
{

    memoriaInstrucoes[0][0] = 2;  // Levando para a RAM
    memoriaInstrucoes[0][1] = multiplicando;
    memoriaInstrucoes[0][2] = 0; 
    memoriaInstrucoes[0][3] = -1;
    
    memoriaInstrucoes[1][0] = 2;
    memoriaInstrucoes[1][1] = 0;
    memoriaInstrucoes[1][2] = 1;
    memoriaInstrucoes[1][3] = -1;
    
    for(int i = 0; i < multiplicador ; i++)
    {
        memoriaInstrucoes[i+2][0] = 0;
        memoriaInstrucoes[i+2][1] = 0;
        memoriaInstrucoes[i+2][2] = 1;
        memoriaInstrucoes[i+2][3] = 1;
    }
    
    memoriaInstrucoes[multiplicador+2][0] = -1;
    memoriaInstrucoes[multiplicador+2][1] = -1;
    memoriaInstrucoes[multiplicador+2][2] = -1;
    memoriaInstrucoes[multiplicador+2][3] = -1;
    
    maquinaInterpretada(memoriaInstrucoes,memoriaDados);

}


void montarDivisao(int **memoriaInstrucoes, int *memoriaDados, int dividendo , int divisor)
{

    int i = 0;

    memoriaInstrucoes[0][0] = 2;   
    memoriaInstrucoes[0][1] = dividendo;
    memoriaInstrucoes[0][2] = 0;
    memoriaInstrucoes[0][3] = -1;

    memoriaInstrucoes[1][0] = 2;   
    memoriaInstrucoes[1][1] = divisor;
    memoriaInstrucoes[1][2] = 1;
    memoriaInstrucoes[1][3] = -1;

    memoriaInstrucoes[2][0] = -1;   
    memoriaInstrucoes[2][1] = -1;
    memoriaInstrucoes[2][2] = -1;
    memoriaInstrucoes[2][3] = -1;

    maquinaInterpretada(memoriaInstrucoes,memoriaDados);
    
    while(memoriaDados[0] >= memoriaDados[1])
    {
        memoriaInstrucoes[0][0] = 1;
        memoriaInstrucoes[0][1] = 0;
        memoriaInstrucoes[0][2] = 1;
        memoriaInstrucoes[0][3] = 0;

        memoriaInstrucoes[1][0] = -1;   
        memoriaInstrucoes[1][1] = -1;
        memoriaInstrucoes[1][2] = -1;
        memoriaInstrucoes[1][3] = -1;

        maquinaInterpretada(memoriaInstrucoes,memoriaDados);

        i++;

    }
    
    memoriaDados[1] = i ;
    
}


void montarRaiz(int **memoriaInstrucoes, int *memoriaDados, int radicando)
{   
    int i = 0;

    memoriaInstrucoes[0][0] =  2;
    memoriaInstrucoes[0][1] = radicando;
    memoriaInstrucoes[0][2] =  0;
    memoriaInstrucoes[0][3] = -1;

    memoriaInstrucoes[1][0] = -1;
    memoriaInstrucoes[1][1] = -1;
    memoriaInstrucoes[1][2] = -1;
    memoriaInstrucoes[1][3] = -1;
    for(i = 0; radicando > i * i ; i++)
    {

        montarMultiplicacao(memoriaInstrucoes,memoriaDados,i,i);

    }

    memoriaDados[1] = i ;


}


void montarPotenciacao(int **memoriaInstrucoes, int *memoriaDados, int base , int expoente)
{
    int auxiliar = base;

    memoriaInstrucoes[0][0] = 2;
    memoriaInstrucoes[0][1] = base;
    memoriaInstrucoes[0][2] = 0;
    memoriaInstrucoes[0][3] = -1;

    memoriaInstrucoes[1][0] = 2;
    memoriaInstrucoes[1][1] = expoente;
    memoriaInstrucoes[1][2] = 1;
    memoriaInstrucoes[1][3] = -1;

    memoriaInstrucoes[2][0] = -1;
    memoriaInstrucoes[2][1] = -1;
    memoriaInstrucoes[2][2] = -1;
    memoriaInstrucoes[2][3] = -1;


    for(int i = 0; i < expoente - 1; i++)
    {
        montarMultiplicacao(memoriaInstrucoes,memoriaDados,auxiliar,base);
        auxiliar = memoriaDados[1];
    }
}

void montarSomaCubos(int **memoriaInstrucoes, int *memoriaDados, int aux1 , int aux2)
{

    memoriaInstrucoes[0][0] = 2;
    memoriaInstrucoes[0][1] = aux1;
    memoriaInstrucoes[0][2] = 0;
    memoriaInstrucoes[0][3] = -1;

    memoriaInstrucoes[1][0] = 2;
    memoriaInstrucoes[1][1] = aux2;
    memoriaInstrucoes[1][2] = 1;
    memoriaInstrucoes[1][3] = -1;

    memoriaInstrucoes[2][0] = -1;
    memoriaInstrucoes[2][1] = -1;
    memoriaInstrucoes[2][2] = -1;
    memoriaInstrucoes[2][3] = -1;


    int aux3 = 0 , aux4 = 0 ;

    montarPotenciacao(memoriaInstrucoes,memoriaDados, aux1 , 3);
    aux3 = memoriaDados[1];

    montarPotenciacao(memoriaInstrucoes,memoriaDados, aux2 , 3);
    aux4 = memoriaDados[1];

    montarSoma(memoriaInstrucoes,memoriaDados,aux3, aux4);

}

void montarPitagoras(int **memoriaInstrucoes, int *memoriaDados, int lado1 , int lado2)
{
    int aux1 = 0 , aux2 = 0 , aux3 = 0 ;

    memoriaInstrucoes[0][0] = 2;
    memoriaInstrucoes[0][1] = lado1;
    memoriaInstrucoes[0][2] = 0;
    memoriaInstrucoes[0][3] = -1;

    memoriaInstrucoes[1][0] = 2;
    memoriaInstrucoes[1][1] = lado2;
    memoriaInstrucoes[1][2] = 1;
    memoriaInstrucoes[1][3] = -1;

    memoriaInstrucoes[2][0] = -1;
    memoriaInstrucoes[2][1] = -1;
    memoriaInstrucoes[2][2] = -1;
    memoriaInstrucoes[2][3] = -1;

    montarPotenciacao(memoriaInstrucoes,memoriaDados,lado1, 2);
    aux1 = memoriaDados[1];

    montarPotenciacao(memoriaInstrucoes,memoriaDados,lado2, 2);
    aux2 = memoriaDados[1];
    montarSoma(memoriaInstrucoes,memoriaDados,aux1,aux2);

    aux3 = memoriaDados[1];
    montarRaiz(memoriaInstrucoes,memoriaDados,aux3);


}

void montarAreaQuadrado(int **memoriaInstrucoes, int *memoriaDados, int lado)
{

    memoriaInstrucoes[0][0] = 2;
    memoriaInstrucoes[0][1] = lado;
    memoriaInstrucoes[0][2] = 0;
    memoriaInstrucoes[0][3] = -1;

    memoriaInstrucoes[1][0] = -1;
    memoriaInstrucoes[1][1] = -1;
    memoriaInstrucoes[1][2] = -1;
    memoriaInstrucoes[1][3] = -1;

    montarPotenciacao(memoriaInstrucoes,memoriaDados,lado, 2);

}

void montarAreaRetangulo(int **memoriaInstrucoes, int *memoriaDados, int lado1 , int lado2)
{
    memoriaInstrucoes[0][0] = 2;
    memoriaInstrucoes[0][1] = lado1;
    memoriaInstrucoes[0][2] = 0;
    memoriaInstrucoes[0][3] = -1;

    memoriaInstrucoes[1][0] = 2;
    memoriaInstrucoes[1][1] = lado2;
    memoriaInstrucoes[1][2] = 1;
    memoriaInstrucoes[1][3] = -1;

    memoriaInstrucoes[2][0] = -1;
    memoriaInstrucoes[2][1] = -1;
    memoriaInstrucoes[2][2] = -1;
    memoriaInstrucoes[2][3] = -1;

    montarMultiplicacao(memoriaInstrucoes,memoriaDados,lado1,lado2);

}

void montarAreaTriangulo(int **memoriaInstrucoes, int *memoriaDados, int base , int altura)
{

    montarAreaRetangulo(memoriaInstrucoes,memoriaDados,base,altura);

}

void montarAreaLosango(int **memoriaInstrucoes, int *memoriaDados, int diagM , int diagm)
{
    int aux = 0;

    memoriaInstrucoes[0][0] = 2;
    memoriaInstrucoes[0][1] = diagM;
    memoriaInstrucoes[0][2] = 0;
    memoriaInstrucoes[0][3] = -1;

    memoriaInstrucoes[1][0] = 2;
    memoriaInstrucoes[1][1] = diagm;
    memoriaInstrucoes[1][2] = 1;
    memoriaInstrucoes[1][3] = -1;

    memoriaInstrucoes[2][0] = -1;
    memoriaInstrucoes[2][1] = -1;
    memoriaInstrucoes[2][2] = -1;
    memoriaInstrucoes[2][3] = -1;

    montarMultiplicacao(memoriaInstrucoes,memoriaDados,diagM,diagm);

    aux = memoriaDados[1];

    montarDivisao(memoriaInstrucoes,memoriaDados,aux,2);


}