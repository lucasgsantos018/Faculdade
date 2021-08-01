#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define tamanhoram 1000
#define tamcache1 16
#define tamcache2 32
#define tamcache3 64
#define tamdasinstrucoes 20000  
#define cacheSup3 90
#define cacheSup2 36
#define cacheSup1 12

typedef struct {
    int opcode;
    int end1; 
    int end2; 
    int end3; 
} instrucao;

typedef struct {
    int endereco;
    int conteudo;
    int refresh;

    /*
    //para escolher quem fica caso a cache encha vamos ter que escolher quem fica conforme:
    int prioridadeimportancia; // + importante
    int prioridadeidade; // - importante
    int soma; */ //apanhado do score da posicao da cache
} blocodememoria;

void iniciaram (blocodememoria *ram);
void iniciacache1 (blocodememoria *cache1);
void iniciacache2 (blocodememoria *cache2);
void iniciacache3 (blocodememoria *cache3);
void inicialerinstrucoes (instrucao *instrucao);
void maquinainterpretada (blocodememoria *cache1, blocodememoria *cache2,blocodememoria *cache3, instrucao *instrucao, blocodememoria *ram, int *cacheHit , int *cacheMiss, int *custoTotal);
int retornarovalorbuscado (blocodememoria *cache1, blocodememoria *cache2, blocodememoria *cache3, int endereco, blocodememoria *ram, int *cacheHit , int *cacheMiss , int *custoTotal);
int definen (blocodememoria *cache1, blocodememoria *cache2, blocodememoria *cache3, int n);
void imprimirRelatorio(int cacheHit , int cacheMiss, int custoTotal);



int main() {
    blocodememoria ram [tamanhoram];
    blocodememoria cache1[tamcache1];
    blocodememoria cache2 [tamcache2];
    blocodememoria cache3 [tamcache3];
    int cacheHit = 0 , cacheMiss = 0 , custoTotal = 0 ;

    iniciaram(ram);
    iniciacache1(cache1);
    iniciacache2(cache2);
    iniciacache3(cache3);

    instrucao lerinstrucoes[tamdasinstrucoes];

    inicialerinstrucoes(lerinstrucoes);

    maquinainterpretada (cache1, cache2, cache3, lerinstrucoes, ram , &cacheHit , &cacheMiss , &custoTotal);

    imprimirRelatorio(cacheHit,cacheMiss,custoTotal);

    return 0;
}


//primeira funcao que inicia as memorias:
//no bloco nao usamos identificadores convencionais para nao confundir ram com cache...
//Nas funcoes que iniciam vamos preencher as memorias com valores aleatorizados.
void iniciaram (blocodememoria *ram) {
    srand(time(NULL));
    for (int i = tamcache1 + tamcache2 + tamcache3; i < tamanhoram; i++) {
        ram[i].endereco = i; //ta dando uma tag pro local, tipo identificador
        ram[i].conteudo = rand() % 1000; //aqui dando valores aleatorios pra fazer as contas
        ram[i].refresh = 1; //Serve para manter alinhados os valores da cache1 com a ram, pra nao ter blocos o mesmo com valores diferentes
    }
    
}

void iniciacache1 (blocodememoria *cache1) {
    srand(time(NULL));
    for (int i = 0; i < tamcache1; i++) {
        //cache1[i].endereco = (i + 1) * -1; //nao pode ser igual o i da cache para nao pegar os mesmos identificadores
        cache1[i].endereco = i ;
        cache1[i].conteudo = rand() % 1000;
        cache1[i].refresh = 0; //pra saber que quando inicia a cache nenhum valor ainda foi inputado
    }
}

void iniciacache2 (blocodememoria *cache2) {
    srand(time(NULL));
    for (int i = tamcache1; i < tamcache1 + tamcache2; i++) {
        //cache2[i].endereco = (i + 1) * -1; //nao pode ser igual o i da cache para nao pegar os mesmos identificadores
        cache2[i].endereco = i ;
        cache2[i].conteudo = rand() % 1000;
        cache2[i].refresh = 0;
    }
}

void iniciacache3 (blocodememoria *cache3) {
    srand(time(NULL));
    for (int i = tamcache1 + tamcache2; i < tamcache1 + tamcache2 + tamcache3; i++) {
        //cache3[i].endereco = (i + 1) * -1; //nao pode ser igual o i da cache para nao pegar os mesmos identificadores
        cache3[i].endereco = i ;
        cache3[i].conteudo = rand() % 1000;
        cache3[i].refresh = 0;
    }
}

void inicialerinstrucoes (instrucao *instrucao) {
    srand(time(NULL));
    for (int i = 0; i < tamdasinstrucoes; i++) {
        instrucao[i].opcode = rand() % 2; //estamos gerando instrucoes aleatorias pro opcode processar 
        instrucao[i].end1 = rand() % 1000; //os enderecoes das intrucoes foram passados de acordo com valores aleatorios que foram sorteados no inicia ram
        instrucao[i].end2 = rand() % 1000;
        instrucao[i].end3 = rand() % 1000;
    }
}


void maquinainterpretada (blocodememoria *cache1, blocodememoria *cache2, blocodememoria *cache3, instrucao *instrucao, blocodememoria *ram ,int *cacheHit , int *cacheMiss, int *custoTotal) {
    int n , k ;
    for (int i = 0; i < tamdasinstrucoes; i++) {
        if (instrucao[i].opcode == 0) { //soma
            //Como buscar os valores:
            retornarovalorbuscado(cache1, cache2, cache3, instrucao[i].end1, ram , cacheHit , cacheMiss , custoTotal);
            n = cache1[cacheSup1].conteudo; printf("|Primeiro Valor na cache1 = %d|\n\n" , n);
            retornarovalorbuscado(cache1, cache2, cache3, instrucao[i].end2, ram, cacheHit , cacheMiss , custoTotal);
            k = cache1[cacheSup1].conteudo; printf("|Segundo Valor na cache1 = %d|\n\n" , k);
            ram[instrucao[i].end3].conteudo = n + k;
            printf("Soma: %d + %d = %d\n\n",n , k , ram[instrucao[i].end3].conteudo);

        }
        if (instrucao[i].opcode == 1) { //subtracao
            retornarovalorbuscado(cache1, cache2, cache3, instrucao[i].end1, ram , cacheHit , cacheMiss , custoTotal);
            n = cache1[cacheSup1].conteudo; printf("|Primeiro Valor na cache1 = %d|\n\n" , n);
            retornarovalorbuscado(cache1, cache2, cache3, instrucao[i].end2, ram , cacheHit , cacheMiss , custoTotal);
            k = cache1[cacheSup1].conteudo; printf("|Segundo valor na cache1 = %d|\n\n" , k);
            ram[instrucao[i].end3].conteudo = n - k;
            printf("Subtração: %d - %d = %d\n\n",n , k , ram[instrucao[i].end3].conteudo);

        }
    }
}

int retornarovalorbuscado (blocodememoria *cache1, blocodememoria *cache2, blocodememoria *cache3, int endereco, blocodememoria *ram, int *cacheHit , int *cacheMiss, int *custoTotal) { //endereco que vamos buscar, ele esta

    if(endereco >= 0 && endereco < tamcache1)
    {
        for(int i = 0; i < tamcache1 ; i++)
        {
            if(cache1[i].endereco == endereco)
            {
                *cacheHit = *cacheHit + 1;
                *custoTotal = *custoTotal + 10;
                return cache1[i].conteudo;
            }
        }
    }
    


    /*
    for (int i = 0; i < tamcache1; i++) {
        if (cache1[i].endereco == endereco || cache1[i].refresh == 0) {
            printf("teste3 cache = %d\n", cache1[i].conteudo);
            return cache1[i].conteudo;
            
        }
    }
    */

   else if(endereco >= tamcache1 && endereco < tamcache1 + tamcache2)
   {
       for(int j = tamcache1 ; j < tamcache1 + tamcache2 ; j++)
       {
           if(cache2[j].endereco == endereco)
           {
               cache1[cacheSup1].conteudo = cache2[j].conteudo;
               printf("|Valor na cache2|  |Movendo valor da cache2 para cache1|\n");
               //*cacheHit = *cacheHit + 1;
               *custoTotal = *custoTotal + 20; 
               retornarovalorbuscado(cache1,cache2,cache3,cacheSup1,ram , cacheHit , cacheMiss , custoTotal);
           }
       }
   }

    /*for (int j = 0; j < tamcache2; j++) {
        if (cache2[j].endereco == endereco || cache2[j].refresh == 0) {
            //int n = definen(cache1, cache2, cache3, 1); //estamos escolhendo aqui qual posicao do cache1 vai ser apagado pra gente passar o da cache2 pra ca
            int n = 1;
            cache1[n] = cache2[j];  //transferindo o conteudo da cache2 pra posicao menos relevante da cache1
            printf("teste4\n");
            retornarovalorbuscado (cache1, cache2, cache3, endereco, ram);
            //Agora precismos definir em qual posicao cache1[??] vai ser apagada
            //precisamos trazer o valor da cache2 pra cache1 e apagar na cache 2
            //de acordo com as hierarquias definidas la
            
        }
    }
    */

   else if(endereco >= tamcache1 + tamcache2 && endereco < tamcache1 + tamcache2 + tamcache3)
   {
       for(int k = tamcache1 + tamcache2 ; k < tamcache1 + tamcache2 + tamcache3 ; k++)
       {
           if(cache3[k].endereco == endereco)
           {
                cache2[cacheSup2].conteudo = cache3[k].conteudo;
                printf("|Valor na cache3|  |Movendo valor da cache3 para cache2|\n");
                //*cacheHit = *cacheHit + 1;
                *custoTotal = *custoTotal + 30;
                retornarovalorbuscado(cache1,cache2,cache3,cacheSup2,ram, cacheHit , cacheMiss , custoTotal);
           }
       }
   }

   else if (endereco >= tamcache1 + tamcache2 + tamcache3 && endereco < tamanhoram)
   {
       for(int l = tamcache1 + tamcache2 + tamcache3 ; l < tamanhoram ; l++)          // 0 16 48 112
       {
           if(ram[l].endereco == endereco)
           {
               cache3[cacheSup3].conteudo = ram[l].conteudo;
               printf("|Valor na RAM|     |Movendo valor da RAM para cache3|\n");
               *cacheMiss = *cacheMiss + 1;
               *custoTotal = *custoTotal + 1000;
               *cacheHit = *cacheHit - 1;
               retornarovalorbuscado(cache1,cache2,cache3,cacheSup3,ram , cacheHit , cacheMiss , custoTotal);   
           }
       }
   }

   return 0;




    /*
    for (int k = 0; k < tamcache3; k++) {
        if (cache3[k].endereco == endereco || cache3[k].refresh == 0) {
            //int n = definen(cache1, cache2, cache3, 2);
            int n = 2;
            cache2[n] = cache3[k];  //transferindo o conteudo da cache3 pra posicao menos relevante da cache2
            printf("teste5\n");
            retornarovalorbuscado (cache1, cache2, cache3, endereco, ram);
            
        }
    }

    //int n = definen(cache1, cache2, cache3, 2);
    // cache3[n] = ram[endereco];  //transferindo o conteudo da cache3 pra posicao menos relevante da cache2
    printf("teste6\n");
    //retornarovalorbuscado (cache1, cache2, cache3, endereco, ram);
    */
}

void imprimirRelatorio(int cacheHit , int cacheMiss , int custoTotal)
{
    printf("\n|Cache Hit:   %d|   ", cacheHit);
    printf("|Cache Miss:  %d|   ", cacheMiss);
    printf("|Custo Total: %d|\n\n", custoTotal);
}






















/*
//Essa funcao vai varrer as caches e descobrir qual endereco dela pode ser substituido, retornando a posicao que e
int definen (blocodememoria *cache1, blocodememoria *cache2, blocodememoria *cache3, int n) {
    int soma1 = 0;
    int valor1, valor2;
    if (n == 1) {
        for (int i = 0; i < tamcache1; i++) {
            valor1 = cache1[i].prioridadeimportancia * 100000;
            valor2 = cache1[i].prioridadeidade * 10;
            cache1[i].soma = valor1 + valor2;
        }
        int menor = cache1[0].soma;
        for (int j = 0; j < tamcache1; j++) {
            if (cache1[j].soma < menor) {
                menor = cache1[j].soma;
            }
        }
        int posicaonacachesubstituivel;
        for (int i = 0; i < tamcache1; i++) {
            if (cache1[i].soma == menor) {
                posicaonacachesubstituivel = i;
            }
        }
        return posicaonacachesubstituivel; //oq tiver menor prioridade vai ser o apagado
    }

    if (n == 2) {
        for (int i = 0; i < tamcache2; i++) {
            valor1 = cache2[i].prioridadeimportancia * 100000;
            valor2 = cache2[i].prioridadeidade * 10;
            cache2[i].soma = valor1 + valor2;
        }
        int menor = cache2[0].soma;
        for (int j = 0; j < tamcache2; j++) {
            if (cache2[j].soma < menor) {
                menor = cache2[j].soma;
            }
        }
        int posicaonacachesubstituivel;
        for (int i = 0; i < tamcache2; i++) {
            if (cache2[i].soma == menor) {
                posicaonacachesubstituivel = i;
            }
        }
        return posicaonacachesubstituivel;
    }
    
    else {
        for (int i = 0; i < tamcache3; i++) {
            valor1 = cache3[i].prioridadeimportancia * 100000;
            valor2 = cache3[i].prioridadeidade * 10;
            cache3[i].soma = valor1 + valor2;
        }
        int menor = cache3[0].soma;
        for (int j = 0; j < tamcache3; j++) {
            if (cache3[j].soma < menor) {
                menor = cache3[j].soma;
            }
        }
        int posicaonacachesubstituivel;
        for (int i = 0; i < tamcache3; i++) {
            if (cache3[i].soma == menor) {
                posicaonacachesubstituivel = i;
            }
        }
        return posicaonacachesubstituivel;
    }
    
}
*/

//preciso atribuir valores pra prioridade de importancia e de idade;
//trazer da ram pra cache3
//cache miss e quando tira da ram
//cache hit eq aundo tira das caches