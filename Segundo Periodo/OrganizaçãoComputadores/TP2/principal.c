#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// instructions
#define T 100

// cache
typedef struct cache Cache;

// bloco
typedef struct block Block;

// menu
void Menu();

// machine
void maquina(int* ARITMETIC_memory, int** program);

// instructions
int* criaAritmetica(int size);
void liberaAritmetica(int* ARITMETIC_memory);
int** criaPrograma(int size);
void delete_programa(int** program, int programa_size);
int** programaSoma(int* ARITMETIC_memory, int size);
int** programaSubtracao(int programa_size, int* Aritmetic_memory);
int** starta_instrucoes(int* inst, int L1_size);
int** ler_instrucoes(int* inst, bool* flag);

// cpu
void CPU(Cache* RAM_memory, Cache* cacheL1, Cache* cacheL2, Cache* cacheL3, int* ARITMETIC_memory, int** instructions);
int MMU(Cache* RAM_memory,Cache* cacheL1, Cache* cacheL2, Cache* cacheL3, int addBlock1, int word, int addBlock2);
int ALU(int* ARITMETIC_memory, int pick, int* one_problem, Cache* cacheL1, Cache* cacheL2, Cache* cacheL3, Cache* RAM_memory);

// cache
Cache* createCache(int num);
Cache* cache_creat_ram(int size);
void clearCache(Cache* cache);
void deleteCache(Cache* cache);
void cache_switch(Cache* cache1, int add1, Cache* cache2, int add2);
void cache_up(Cache* cache1, int pos, Block* bloco);
Block* cache_return_block(Cache* cache, int addBlock);
int getHitCache(Cache* cache);
int getMissCache(Cache* cache);
int getSizeCache(Cache* cache);
Block* getBlockCache(Cache* cache, int pos);
void setHitCache(Cache* cache,int hit);
void setMissCache(Cache* cache,int miss);
void setSizeCache(Cache* cache, int size);
void setBlockCache(Cache* cache, Block** bloco);
void showCache_all(Cache* cacheL1, Cache* cacheL2, Cache* cacheL3, Cache* RAM_memory);
void cache_show_statistic(Cache* cacheL1, Cache* cacheL2, Cache* cacheL3, Cache* RAM_memory, double* time);

// bloco
Block* createBlock();
Block* block_creat_random(int add);
void deleteBlock(Block* bloco);
int getWordBlock(Block* bloco, int add);
int getAddBlock(Block* bloco);
int getHitBlock(Block* bloco);
bool getUpdateBlock(Block* bloco);
bool getEmptyBlock(Block* bloco);
void setWordBlock(Block* bloco,int add, int valor);
void setAddBlock(Block* bloco,int add);
void setHitBlock(Block* bloco, int hit);
void setHitZero(Block* bloco, int hit);
void setUpdateBlock(Block* bloco,bool update);
void setEmptyBlock(Block* bloco, bool empty);


int main()
{
    srand(time(NULL));
	Menu();
	return 0;
}


// menu
void Menu(){

  Cache* cacheL1 = NULL;
  Cache* cacheL2 = NULL;
  Cache* cacheL3 = NULL;

  do{
    cacheL1=createCache(1);
      if(getSizeCache(cacheL1)<2){
        deleteCache(cacheL1);
        printf("Tamanho inválido\n");
        continue;
      }
      else{
          do{
              cacheL2 = createCache(2);
              if(getSizeCache(cacheL2)<=getSizeCache(cacheL1)){
                  deleteCache(cacheL2);
                  printf("Tamanho inválido\n");
                  continue;
              }
              else{
                  do{
                      cacheL3 = createCache(3);
                      if(getSizeCache(cacheL3)<=getSizeCache(cacheL2)){
                          deleteCache(cacheL3);
                          printf("Tamanho inválido\n");
                          continue;
                      }
                  }while(getSizeCache(cacheL3)<=getSizeCache(cacheL2));
              }
          }while(getSizeCache(cacheL2)<=getSizeCache(cacheL1));
      }
    }while(getSizeCache(cacheL1)<1);

    clock_t temp;
    temp=clock();

    int ARITMETIC_size=11;

    int* ARITMETIC_memory=criaAritmetica(ARITMETIC_size);

    int* inst = malloc(sizeof(int));

    int** instructions=starta_instrucoes(inst, getSizeCache(cacheL1));

    Cache* RAM_memory=cache_creat_ram(1000);

    CPU(RAM_memory, cacheL1, cacheL2, cacheL3, ARITMETIC_memory, instructions);

    temp=clock()-temp;
    double* exec_time=malloc(sizeof(double));
    *exec_time=temp/(CLOCKS_PER_SEC/1000.0);
    printf("\n\n");
    cache_show_statistic(cacheL1, cacheL2, cacheL3, RAM_memory, exec_time);
    printf("\n\n");

    deleteCache(cacheL3);
    deleteCache(cacheL2);
    deleteCache(cacheL1);
    deleteCache(RAM_memory);
    liberaAritmetica(ARITMETIC_memory);
    free(exec_time);
    free(inst);
}


// machine
void maquina(int* ARITMETIC_memory, int** program){

    int pc = 0;
    int opcode = 0;
    while(opcode != -1){
        int* one_instruction=program[pc];
        opcode = one_instruction[0];
        switch(opcode){

          case 0:{
              //somar
              int add1 = ARITMETIC_memory[one_instruction[1]];
              int add2 = ARITMETIC_memory[one_instruction[2]];
              int sum=add1+add2;
              ARITMETIC_memory[one_instruction[3]]+=sum;
              break;
          }

          case 1:{

              //subtrai
              int add1 = ARITMETIC_memory[one_instruction[1]];
              int add2 = ARITMETIC_memory[one_instruction[2]];
              int sub=add1-add2;
              ARITMETIC_memory[one_instruction[3]]+=sub;
              break;
          }
        }
        pc++;
    }
}


// instructions
int* criaAritmetica(int size){
    int* ARITMETIC_memory=malloc(size*sizeof(int));
    for (int i=0; i<size; i++){
        ARITMETIC_memory[i]=0;
    }
    return ARITMETIC_memory;
}

void liberaAritmetica(int* ARITMETIC_memory){
    free(ARITMETIC_memory);
}

int** criaPrograma(int size){
  int** programa=malloc(size*sizeof(int*));
  for(int i=0; i<size; i++){
    programa[i]=malloc(4*sizeof(int));
  }
  return programa;
}

void delete_programa(int** program, int programa_size){
    for(int i=0; i<programa_size; i++){
        free(program[i]);
    }
    free(program);
}

//Se o usuario desejar realizar uma soma simples essa funcao e chamada e as instrucoes são encaminhadas para a maquina
int** programaSoma(int* ARITMETIC_memory, int size){

    size= 1+1;
    int** program=criaPrograma(size);

    program[0][0] = 0;
    program[0][1] = 1;
    program[0][2] = 2;
    program[0][3] = 0;

    //Halt
    program[1][0] = -1;
    program[1][1] = -1;
    program[1][2] = -1;
    program[1][3] = -1;

    return program;
}

//Logica semelhante da funcao proginstructionsaSoma, porem engloba a subtracao
int** programaSubtracao(int programa_size, int* Aritmetic_memory){
    programa_size=1+1;
    int** program=criaPrograma(programa_size);

    program[0][0] = 1;
    program[0][1] = 1;
    program[0][2] = 2;
    program[0][3] = 0;

    //halt
    program[1][0] = -1;
    program[1][1] = -1;
    program[1][2] = -1;
    program[1][3] = -1;

    return program;
}

int** starta_instrucoes(int* inst, int L1_size){
    int choice;
    bool *flag=malloc(sizeof(bool));
    int** problems = NULL;
        do{
            problems = ler_instrucoes(inst, flag);
        }while(!flag);

        return problems;
}


int** ler_instrucoes(int* inst, bool *flag){
    char name[100];
    printf("Digite o nome do arquivo: ");
    scanf("%s",name);
    FILE* load = fopen(name,"r");
    if(load == NULL){
        printf("Erro ao tentar abrir arquivo\n");
        return NULL;
    }
    else{

        *inst = 0;
        char ch;

        while((ch = fgetc(load)) != EOF){
            if(ch == '\n'){
                (*inst)++;
            }
        }

        rewind(load);

        //Declara matriz com o mesmo numero de linhas que o arquivo
        int** novo=malloc((*inst) *sizeof(int*));
        for(int i=0; i<(*inst); i++){
            novo[i]=malloc(7 *sizeof(int));
        }

        int op;
        int addBlock1;
        int word1;
        int addBlock2;
        int word2;
        int addBlock3;
        int word3;

        //Adiciona os valores a matriz
        for(int index=0; index<(*inst); index++){
            fscanf(load,"%d %d %d %d %d %d %d", &op, &addBlock1, &word1, &addBlock2, &word2, &addBlock3, &word3);
            novo[index][0] = op;
            novo[index][1] = addBlock1;
            novo[index][2] = word1;
            novo[index][3] = addBlock2;
            novo[index][4] = word2;
            novo[index][5] = addBlock3;
            novo[index][6] = word3;

        }
        fclose(load);

        *flag=true;

        printf("\n\n");

        return novo;
    }
}


// cpu
void CPU(Cache* RAM_memory, Cache* cacheL1, Cache* cacheL2, Cache* cacheL3, int* ARITMETIC_memory, int** instruction){
    int time=0;
    int pick=0;
    int result;

    while(pick!=-1){

        int* one=instruction[time];
        pick=one[0];

        if(pick==-1){
            continue;
        }
        else{
            ARITMETIC_memory[10]=0;
            ARITMETIC_memory[0]=0;
            ARITMETIC_memory[1]=MMU(RAM_memory, cacheL1, cacheL2, cacheL3, one[1], one[2], one[3]);
            ARITMETIC_memory[2]=MMU(RAM_memory, cacheL1, cacheL2, cacheL3, one[3], one[4], one[1]);

            //Salvando na memoria cache.
            setWordBlock(getBlockCache(cacheL1, 0), 0, ALU(ARITMETIC_memory, pick, one, cacheL1, cacheL2, cacheL3, RAM_memory));
            printf("%d\n", getWordBlock(getBlockCache(cacheL1, 0), 0));
        }
        showCache_all(cacheL1, cacheL2, cacheL3, RAM_memory);

        free(one);

        time++;
    }
    clearCache(cacheL3);
    clearCache(cacheL2);
    clearCache(cacheL1);
}

int MMU(Cache* RAM_memory,Cache* cacheL1, Cache* cacheL2, Cache* cacheL3, int addBlock1, int word, int addBlock2){
    //Verificação da cache 1
    for(int i = 0; i<getSizeCache(cacheL1); i++){
        if(getAddBlock(getBlockCache(cacheL1, i)) == addBlock1 && !getEmptyBlock(getBlockCache(cacheL1,i))){
            setHitCache(cacheL1,1);
            setHitBlock(getBlockCache(cacheL1, i), 1);
            return getWordBlock(getBlockCache(cacheL1, i), word);
        }
    }
    setMissCache(cacheL1, 1);

    //Verificacao da cache 2
    for(int i = 0; i<getSizeCache(cacheL2); i++){
        if(getAddBlock(getBlockCache(cacheL2, i)) == addBlock1 && !getEmptyBlock(getBlockCache(cacheL2,i))){
            setHitCache(cacheL2,1);
            setHitBlock(getBlockCache(cacheL2,i),1);

            //Caso cache 1 esteja vazia
            for(int j = 0; j<getSizeCache(cacheL1); j++){
                if(getEmptyBlock(getBlockCache(cacheL1,j))){
                    //Um bloco vai da cache 2 para a cache 1
                    cache_switch(cacheL1,j,cacheL2,i);
                    return getWordBlock(getBlockCache(cacheL1,j), word);
                }
            }
            //Caso a cache 1 não esteja vazia
            int add = 0;
            int menor = getHitBlock(getBlockCache(cacheL1, add));
            for(int j = 0; j<getSizeCache(cacheL1); j++){
                if(getHitBlock(getBlockCache(cacheL1,j))<=menor){
                    if(getAddBlock(getBlockCache(cacheL1,j))!= addBlock1){
                        if(getAddBlock(getBlockCache(cacheL1,j)) != addBlock2){
                            add = j;
                            menor = getHitBlock(getBlockCache(cacheL1,add));
                            break;
                        }
                    }
                }
            }
            cache_switch(cacheL1,add,cacheL2,i);
            return getWordBlock(getBlockCache(cacheL1,add), word);
        }
    }
    setMissCache(cacheL2,1);

    //Verificacao na cache 3
    for(int i = 0; i<getSizeCache(cacheL3); i++){
        if(getAddBlock(getBlockCache(cacheL3,i)) == addBlock1 && !getEmptyBlock(getBlockCache(cacheL3,i))){
            setHitCache(cacheL3,1);
            setHitBlock(getBlockCache(cacheL3,i),1);

            //Verifica se cache 2  ta vazia
            //Se cache 2 esta vazia
            for(int j = 0; j< getSizeCache(cacheL2); j++){
                if(getEmptyBlock(getBlockCache(cacheL2,j)))
          {
                    cache_switch(cacheL2,j,cacheL3,i);

                    //Caso a cache 1 esteja vazia
                    for(int k = 0; k<getSizeCache(cacheL1); k++){
                        if(getEmptyBlock(getBlockCache(cacheL1,k))){
                            cache_switch(cacheL1,k,cacheL2,j);
                            return getWordBlock(getBlockCache(cacheL1,k), word);
                        }
                    }

                    //Caso a cache 1 não esteja vazia
                    int add = 0;
                    int menor = getHitBlock(getBlockCache(cacheL1,add));
                    for(int k = 0; k<getSizeCache(cacheL1); k++){
                        if(getHitBlock(getBlockCache(cacheL1,k)) <= menor){
                            if(getAddBlock(getBlockCache(cacheL1,k)) != addBlock1){
                                if(getAddBlock(getBlockCache(cacheL1,k)) != addBlock2){
                                    add = k;
                                    menor = getHitBlock(getBlockCache(cacheL1,add));
                                    break;
                                }
                            }
                        }
                    }
                    //Troca de um bloco entre cache 2 e cache 1
                    cache_switch(cacheL1,add,cacheL2,j);
                    return getWordBlock(getBlockCache(cacheL1,add),word);

            }

            //Caso a cache 2 nao esteja vazia
            int add2 = 0;
            int menor = getHitBlock(getBlockCache(cacheL2,add2));
            for(int j = 0; j<getSizeCache(cacheL2); j++){
                if(getHitBlock(getBlockCache(cacheL2,j))<=menor){
                    if(getAddBlock(getBlockCache(cacheL2,j))!=addBlock1){
                        if(getAddBlock(getBlockCache(cacheL2,j))!=addBlock2){
                            add2 = j;
                            menor = getHitBlock(getBlockCache(cacheL2,add2));
                            break;
                        }
                    }
                }
            }
            //Troca de bloco entre cache 3 e cache 2
            cache_switch(cacheL2,add2,cacheL3,i);
            int add1 = 0;
            menor  = getHitBlock(getBlockCache(cacheL1,add1));
            for(int j = 0; j<getSizeCache(cacheL1); j++){
                if(getHitBlock(getBlockCache(cacheL1,j))<=menor){
                    if(getAddBlock(getBlockCache(cacheL1,j)) != addBlock1){
                        if(getAddBlock(getBlockCache(cacheL1,j)) != addBlock2){
                            add1 = j;
                            menor = getHitBlock(getBlockCache(cacheL1,add1));
                            break;
                        }
                    }
                }
            }
            //Troca um bloco entre a cache 2 e a cache 1
            cache_switch(cacheL1,add1,cacheL2,add2);
            return getWordBlock(getBlockCache(cacheL1,add1),word);
        }
    }
    setMissCache(cacheL3,1);

    //Verifica na memoria Ram(ultimo caso para pesquisa)
    for(int i = 0; i<getSizeCache(RAM_memory); i++){
        if(getAddBlock(getBlockCache(RAM_memory,i)) == addBlock1){
            setHitCache(RAM_memory,1);
            setHitBlock(getBlockCache(RAM_memory,i),1);

            //Caso a cache 3 esteja vazia
            for(int m = 0; m<getSizeCache(cacheL3); m++){
                if(getEmptyBlock(getBlockCache(cacheL3,m))){
                    cache_up(cacheL3,m,cache_return_block(RAM_memory, i));

                    //Verifica se a cache 2 tá vazia
                    //Se a cache 2 estiver vazia
                    for(int j = 0; j<getSizeCache(cacheL2); j++){
                        if(getEmptyBlock(getBlockCache(cacheL2,j))){
                            cache_switch(cacheL2,j,cacheL3,m);
                            //Se a cache 1 esta vazia
                            int add = 0;
                            int menor  = getHitBlock(getBlockCache(cacheL1,add));
                            for(int k = 1; k<getSizeCache(cacheL1); k++){
                                if(getHitBlock(getBlockCache(cacheL1,k))<=menor){
                                    if(getAddBlock(getBlockCache(cacheL1,k))!= addBlock1){
                                        if(getAddBlock(getBlockCache(cacheL1,k))!= addBlock2){
                                            add = k;
                                            menor = getHitBlock(getBlockCache(cacheL1,add));
                                            break;
                                        }
                                    }
                                }
                            }
                            cache_switch(cacheL1,add,cacheL2,j);
                            return getWordBlock(getBlockCache(cacheL1,add),word);

                        }
                    }
                    //Caso a cache 2 nao esteja vazia
                    int add2 = 0;
                    int menor = getHitBlock(getBlockCache(cacheL2,add2));
                    for(int j = 1; j<getSizeCache(cacheL2); j++){
                        if(getHitBlock(getBlockCache(cacheL2,j))<=menor){
                            if(getAddBlock(getBlockCache(cacheL2,j))!=addBlock1){
                                if(getAddBlock(getBlockCache(cacheL2,j)) != addBlock2){
                                    add2 = 1;
                                    menor = getHitBlock(getBlockCache(cacheL2,add2));
                                    break;
                                }
                            }
                        }
                    }
                    //Troca um bloco entre cache 3 e cache 2
                    cache_switch(cacheL2,add2,cacheL3,m);
                    int add1 = 0;
                    menor = getHitBlock(getBlockCache(cacheL1,add1));
                    for(int j = 1; j<getSizeCache(cacheL1); j++){
                        if(getHitBlock(getBlockCache(cacheL1,j))<=menor){
                            if(getAddBlock(getBlockCache(cacheL1,j)) != addBlock1){
                                if(getAddBlock(getBlockCache(cacheL1,j)) != addBlock2){
                                    add1 = j;
                                    menor  = getHitBlock(getBlockCache(cacheL1,add1));
                                    break;
                                }
                            }
                        }
                    }
                    cache_switch(cacheL1,add1,cacheL2,add2);
                    return getWordBlock(getBlockCache(cacheL1,add1),word);
                }
            }
            //Caso a cache 3 nao esteja vazia
            int add3 = 0;
            int menor = getHitBlock(getBlockCache(cacheL3,add3));
            for(int j = 1; j<getSizeCache(cacheL3); j++){
                if(getHitBlock(getBlockCache(cacheL3,j)) <= menor){
                    if(getAddBlock(getBlockCache(cacheL3,j)) != addBlock1){
                        if(getAddBlock(getBlockCache(cacheL3,j)) != addBlock2){
                            add3 = j;
                            menor = getHitBlock(getBlockCache(cacheL3,add3));
                            break;
                        }
                    }
                }
            }
            cache_up(cacheL3,add3,cache_return_block(RAM_memory,addBlock1));
            //Se a cache 2 nao estiver vazia
            int add2 = 0;
            menor = getHitBlock(getBlockCache(cacheL2,add2));
            for(int j = 1; j< getSizeCache(cacheL2); j++){
                if(getHitBlock(getBlockCache(cacheL2,j))<=menor){
                    if(getAddBlock(getBlockCache(cacheL2,j)) != addBlock1){
                        if(getAddBlock(getBlockCache(cacheL2,j)) != addBlock2){
                            add2 = j;
                            menor = getHitBlock(getBlockCache(cacheL2,add2));
                            break;
                        }
                    }
                }
            }
            cache_switch(cacheL2,add2,cacheL3,add3);
            int add1 = 0;
            menor = getHitBlock(getBlockCache(cacheL1, add1));
            for(int j = 1; j<getSizeCache(cacheL1); j++){
                if(getHitBlock(getBlockCache(cacheL1,j))<=menor){
                    if(getAddBlock(getBlockCache(cacheL1,j))!=addBlock1){
                        if(getAddBlock(getBlockCache(cacheL1,j))!=addBlock2){
                            add1 = j;
                            menor = getHitBlock(getBlockCache(cacheL1,add1));
                            break;
                        }
                    }
                }
            }
            cache_switch(cacheL1,add1,cacheL2,add2);
            return getWordBlock(getBlockCache(cacheL1,add1),word);
        }
    }
  }
    return 0;
}

int ALU(int* ARITMETIC_memory, int pick, int* one_problem, Cache* cacheL1, Cache* cacheL2, Cache* cacheL3, Cache* RAM_memory){
    int** program;
    int program_size;
    int term1=ARITMETIC_memory[1], term2=ARITMETIC_memory[2];
    switch(pick){
        case 0:{
            program=programaSoma(ARITMETIC_memory, program_size);
            maquina(ARITMETIC_memory, program);
            printf("\nConta: %d + %d = ", term1, term2);
            return ARITMETIC_memory[0];
            break;
        }
        case 1:{
            program = programaSubtracao(program_size, ARITMETIC_memory);
            maquina(ARITMETIC_memory, program);
            printf("\nConta: %d - %d = ", term1, term2);
            return ARITMETIC_memory[0];
            break;
        }
    }
    delete_programa(program, program_size);
    return ARITMETIC_memory[0];
}


// cache
struct cache{
    Block** bloco;
    int size;
    int hit;
    int miss;
};

Cache* createCache(int num){
    int size;
    do{
        printf("Digite o tamanho da cache L%d: ", num);
        scanf("%d", &size);
        if(size<2){
            printf("Tamanho invalido");
        }
    }while(size<2);

    Cache* novo = malloc(sizeof(Cache));

    novo->bloco = malloc(size*sizeof(Block*));
    for(int i = 0;i < size; i++){
        novo->bloco[i]=createBlock();
    }
    novo->size = size;
    novo->hit = 0;
    novo->miss = 0;
    return novo;
}

Cache* cache_creat_ram(int size){
    Cache* novo=malloc(sizeof(Cache));
    novo->bloco=malloc(size*sizeof(Block*));
    for(int i=0; i<size; i++){
        novo->bloco[i]=block_creat_random(i);
    }
    novo->size = size;
    novo->hit = 0;
    novo->miss = 0;
    return novo;
}

void clearCache(Cache* cache){
    for(int i = 0;i<getSizeCache(cache);i++){
        Block* aux = createBlock();
        cache->bloco[i] = aux;
    }
}

void deleteCache(Cache* cache){
    for(int i = 0; i<getSizeCache(cache); i++){
        deleteBlock(cache->bloco[i]);
    }
    free(cache->bloco);
    free(cache);
}

void cache_switch(Cache* cache1, int add1, Cache* cache2, int add2){
    Block* aux=cache1->bloco[add1];
    cache1->bloco[add1]=cache2->bloco[add2];
    cache2->bloco[add2]=aux;
}

void cache_up(Cache* cache1, int pos, Block* bloco){
    cache1->bloco[pos]=bloco;
}

Block* cache_return_block(Cache* cache, int addBlock){
    for(int i = 0; i < getSizeCache(cache); i++){
        if(getAddBlock(getBlockCache(cache, i)) == addBlock){
            return cache->bloco[i];
        }
    }
    return cache->bloco[0];
}

int getHitCache(Cache* cache){
    return cache->hit;
}

int getMissCache(Cache* cache){
    return cache->miss;
}

int getSizeCache(Cache* cache){
    return cache->size;
}

Block* getBlockCache(Cache* cache, int pos){
    return cache->bloco[pos];
}

void setHitCache(Cache* cache,int hit){
    cache->hit += hit;
}

void setMissCache(Cache* cache,int miss){
    cache->miss += miss;
}

void setSizeCache(Cache* cache, int size){
    cache->size = size;
}

void setBlockCache(Cache* cache, Block** bloco){
    cache->bloco = bloco;
}

void showCache(Cache* cache, char* name){
    printf("\n%s | HIT: %d | MISS: %d \n\n", name, getHitCache(cache), getMissCache(cache));
    for (int i=0; i<getSizeCache(cache); i++){
        printf("\t %d", i+1);
    }
    printf("\n");
    printf("Word1: ");
    for (int i=0; i<getSizeCache(cache); i++){
        printf("\t %d", getWordBlock(getBlockCache(cache, i), 0));
    }
    printf("\n");
    printf("Word2: ");
    for (int i=0; i<getSizeCache(cache); i++){
        printf("\t %d", getWordBlock(getBlockCache(cache, i), 1));
    }
    printf("\n");
    printf("Word3: ");
    for (int i=0; i<getSizeCache(cache); i++){
        printf("\t %d", getWordBlock(getBlockCache(cache, i), 2));
    }
    printf("\n");
    printf("Word4: ");
    for (int i=0; i<getSizeCache(cache); i++){
        printf("\t %d", getWordBlock(getBlockCache(cache, i), 3));
    }
    printf("\n");
    printf("R_add: ");
    for (int i=0; i<getSizeCache(cache); i++){
        printf("\t %d", getAddBlock(getBlockCache(cache, i)));
    }
    printf("\n");
    printf("Empty: ");
    for (int i=0; i<getSizeCache(cache); i++){
        printf("\t %d", getEmptyBlock(getBlockCache(cache, i)));
    }
    printf("\n");
}
void showCache_all(Cache* cacheL1, Cache* cacheL2, Cache* cacheL3, Cache* RAM_memory){
    printf("------------------------------------------------------------------------------------------\n");
    char name[20];
    strcpy(name, "Cache L1");
    showCache(cacheL1, name);
    strcpy(name, "Cache L2");
    showCache(cacheL2, name);
    strcpy(name, "Cache L3");
    showCache(cacheL3, name);
    strcpy(name, "RAM_memory");
    showCache(RAM_memory, name);
}

void cache_show_statistic(Cache* cacheL1, Cache* cacheL2, Cache* cacheL3, Cache* RAM_memory, double* time){
  printf("------------------------------------------------------------------------------------------\n");
  printf("Informativo\n");
  printf("------------------------------------------------------------------------------------------\n");
  printf("\nTamanho da Cache:\n\n");
  printf("CacheL1: %d\n", getSizeCache(cacheL1));
  printf("CacheL2: %d\n", getSizeCache(cacheL2));
  printf("CacheL3: %d\n", getSizeCache(cacheL3));
  printf("RAM_memory: %d\n", getSizeCache(RAM_memory));

  printf("\nQuantidade de HIT/MISS:\n\n");
  printf("CacheL1: HIT: %d | MISS: %d\n", getHitCache(cacheL1),getMissCache(cacheL1));
  printf("CacheL2: HIT: %d | MISS: %d\n", getHitCache(cacheL2),getMissCache(cacheL2));
  printf("CacheL3: HIT: %d | MISS: %d\n", getHitCache(cacheL3),getMissCache(cacheL3));
  printf("RAM_memory: HIT: %d | MISS: %d\n", getHitCache(RAM_memory), 0);

  printf("\nTempo de execucao: %lf ms.\n", *time);

  double l1=(100.0*(double)(getHitCache(cacheL1)))/(double)(getHitCache(cacheL1)+getHitCache(cacheL2)+getHitCache(cacheL3)+getHitCache(RAM_memory));
  double l2=(100.0*(double)(getHitCache(cacheL2)))/(double)(getHitCache(cacheL1)+getHitCache(cacheL2)+getHitCache(cacheL3)+getHitCache(RAM_memory));
  double l3=(100.0*(double)(getHitCache(cacheL3)))/(double)(getHitCache(cacheL1)+getHitCache(cacheL2)+getHitCache(cacheL3)+getHitCache(RAM_memory));
  double ram=(100.0*(double)(getHitCache(RAM_memory)))/(double)(getHitCache(cacheL1)+getHitCache(cacheL2)+getHitCache(cacheL3)+getHitCache(RAM_memory));
  double ltotal=(100.0*(double)(getHitCache(cacheL1)+getHitCache(cacheL2)+getHitCache(cacheL3)))/(double)(getHitCache(cacheL1)+getHitCache(cacheL2)+getHitCache(cacheL3)+getHitCache(RAM_memory));

  printf("\nDados estatisticos:\n\n");

  printf("Cache L1: HIT: %.2lf %% | Miss: %.2lf %% |\n", l1, 100-l1);
  printf("Cache L2: HIT: %.2lf %% | Miss: %.2lf %% |\n", l2, 100-l2);
  printf("Cache L3: HIT: %.2lf %% | Miss: %.2lf %% |\n", l3, 100-l3);
  printf("RAM_memory: HIT: %.2lf %% | Miss: 0.0 |\n", ram);
  printf("Total: HIT: %.2lf %% | Miss: %.2lf %% |\n", ltotal, 100-ltotal);
}


// bloco
struct block{
    int* words;
    bool empty;
    bool update;
    int add;
    int hit;
};

Block* createBlock(){
    Block* bloco = malloc(sizeof(Block));
    bloco->words = malloc(4*sizeof(int));
    for(int i=0; i<4; i++){
        bloco->words[i] = 0;
    }
    bloco->add = 0;
    bloco->hit = 0;
    bloco->update = false;
    bloco->empty = true;
    return bloco;
}

Block* block_creat_random(int add){
    int num;
    Block* block=malloc(sizeof(Block));
    block->words=malloc(4*sizeof(int));
    for(int i=0; i<4; i++){
        num=rand()%100;
        block->words[i]=num;
    }
    block->add=add;
    block->hit=0;
    block->update=false;
    block->empty=false;
    return block;
}

void deleteBlock(Block* bloco){
    free(bloco->words);
    free(bloco);
}

int getWordBlock(Block* bloco, int add){
    return bloco->words[add];
}

int getAddBlock(Block* bloco){
    return bloco->add;
}

int getHitBlock(Block* bloco){
    return bloco->hit;
}

bool getUpdateBlock(Block* bloco){
    return bloco->update;
}

bool getEmptyBlock(Block* bloco){
    return bloco->empty;
}

void setWordBlock(Block* bloco,int add, int valor){
    bloco->words[add] = valor;
}

void setAddBlock(Block* bloco,int add){
    bloco->add = add;
}

void setHitBlock(Block* bloco, int hit){
    bloco->hit += hit;
}

void setHitZero(Block* bloco, int hit){
    bloco->hit = hit;
}

void setUpdateBlock(Block* bloco,bool update){
    bloco->update = update;
}

void setEmptyBlock(Block* bloco, bool empty){
    bloco->empty = empty;
}

void tester(Block* bloco);