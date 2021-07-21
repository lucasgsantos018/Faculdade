//Nome: Lucas Gomes dos Santos
//Matrícula: 20.1.4108
//Turma: 43



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// estilização do programa

#define ANSI_RESET "\x1b[0m"
#define ANSI_BOLD "\x1b[1m"
#define ANSI_COLOR_BLACK "\x1b[30m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_BG_COLOR_BLACK "\x1b[40m"
#define ANSI_BG_COLOR_RED "\x1b[41m"
#define ANSI_BG_COLOR_GREEN "\x1b[42m"
#define ANSI_BG_COLOR_WHITE "\x1b[47m"

#define BOLD(string) ANSI_BOLD string ANSI_RESET
#define BLACK(string) ANSI_COLOR_BLACK string ANSI_RESET
#define RED(string) ANSI_COLOR_RED string ANSI_RESET
#define CYAN(string) ANSI_COLOR_CYAN string ANSI_RESET
#define BG_BLACK(string) ANSI_BG_COLOR_BLACK string ANSI_RESET
#define BG_RED(string) ANSI_BG_COLOR_RED string ANSI_RESET
#define BG_GREEN(string) ANSI_BG_COLOR_GREEN string ANSI_RESET
#define BG_WHITE(string) ANSI_BG_COLOR_WHITE string ANSI_RESET

#define TAB_HOR "\u2501"
#define TAB_VER "\u2503"

#define K 100

// Função que lê a matriz presente no arquivo
void lerMatrizDoJogo(FILE *matrizArqv, int **matrizjogo, int n, int m);

// Impressão de tabuleiro
void imprimirTabuleiro(int **matrizjogo, int n, int m);

// Estrutura principal do programa,tudo é definido pelos comandos apartir dela.
void lerEntrada(char comando[K], int **matrizjogo, int n, int m);

// Comandos de movimentação
void moverC(int **matrizjogo, char cord1, char cord2, int n, int m);
void moverB(int **matrizjogo, char cord1, char cord2, int n, int m);
void moverE(int **matrizjogo, char cord1, char cord2, int n, int m);
void moverD(int **matrizjogo, char cord1, char cord2, int n, int m);

// Função para salvar o jogo
void salvarJogo(int **matrizjogo, int n, int m, char salvarNome[K]);

// Função que analisa a situação atual do jogo e define se ganhou,perdeu ou se o jogo ainda esta em continuação
void analisarJogo(int **matrizjogo, int n, int m);

// Funções de impressão 
void imprimirMenu();
void recepcao();

// Função para o comando "ajuda" 
void ajuda(int **matrizjogo, int n , int m);

// Funções para alocar e liberar a matriz
void liberaMatriz(int **matrizjogo , int n);
int **criaMatriz(int n , int m);


int main(int argc, char **argv)
{
    int n, m, **matrizjogo;
    char comando[K];
    // Caso o usuário não passe um arquivo na execução do programa,será dada a opção de selecionar entre um jogo médio e difícil de dimensões aleatórias
    if (argc == 2) // Caso passe um arquivo
    {
        FILE *matrizArqv = fopen(argv[1], "r"); 

        fscanf(matrizArqv, "%d %d", &n, &m); // Lendo a dimensão da matriz do arquivo.

        matrizjogo = criaMatriz(n , m); // Matrizjogo recebendo a matriz criada dinâmicamente na função

        recepcao(); 

        printf("\n\nAbrindo o jogo %s\n\n", argv[1]);

        lerMatrizDoJogo(matrizArqv, matrizjogo, n, m); // Lendo os valores da matriz do arquivo.

        imprimirTabuleiro(matrizjogo, n, m);

        imprimirMenu();

        lerEntrada(comando, matrizjogo, n, m); // Função que lê os comandos
    }
    else if (argc == 1) // Caso não passe o arquivo como argumento
    {
        char modo;

        recepcao();

        printf("\n\n" CYAN(BOLD("Deseja jogar no modo médio ou hard? (m/h): ")));
        scanf("%c", &modo); // Lendo o modo de jogo definido pelo usuário
        getchar();
        srand(time(NULL)); // Alterando a semente para ser aleatória
        switch (modo)
        {
            case 'm': // Jogo médio de tamanho aleatório.
            {
            
                n = rand() % 6 + 4; // Randomizando dimensão da matriz de 4 a 9
                m = rand() % 6 + 4; 

                matrizjogo = criaMatriz(n , m); // Matrizjogo recebendo a matriz criada dinâmicamente na função
            
                for (int i = 0; i < n; i++) // Preenchendo a matriz com os pinos.
                {
                    for (int j = 0; j < m; j++)
                    {
                        matrizjogo[i][j] = 1;
                    }
                }
                matrizjogo[2][3] = 0; // Buraco do jogo.

                imprimirTabuleiro(matrizjogo, n, m);

                imprimirMenu();

                lerEntrada(comando, matrizjogo, n, m); // Função que lê os comandos

                break;
            }
            case 'h': // Jogo difícil de tamanho aleatório
            {
                n = rand() % 6 + 7; // Randomizando dimensão da matriz de 7 a 12
                m = rand() % 6 + 7;

                matrizjogo = criaMatriz(n , m); // Matrizjogo recebendo a matriz criada dinâmicamente na função

                for (int i = 0; i < n; i++) // Preenchendo a matriz com os pinos.
                {
                    for (int j = 0; j < m; j++)
                    {
                        matrizjogo[i][j] = 1;
                    }
                }

                matrizjogo[4][6] = 0; // Buraco do jogo.


                imprimirTabuleiro(matrizjogo, n, m);

                imprimirMenu();

                lerEntrada(comando, matrizjogo, n, m); // Função que lê os comandos

                break;
            }
        }
    }
    return 0;
}

void lerMatrizDoJogo(FILE *matrizArqv, int **matrizjogo, int n, int m)
{
    // Lendo a matriz do arquivo
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            fscanf(matrizArqv, "%d", &matrizjogo[i][j]);
        }
    }
    fclose(matrizArqv); // Fechando o arquivo
}

void imprimirTabuleiro(int **matrizjogo, int n, int m)
{
    printf("\n");
    int menosum = 32, zero = 45, um = 64; // Relacionando os pinos,buracos e áreas restritas do tabuleiro com caracteres da tabela ascii
    printf("  ");

    for (int A = 65; A < m + 65; A++)
    {
        printf("%3c", A); //Imprimindo coordenadas da coluna.
    }
    printf("\n");
    
    int a = 65; // 65 é igual ao A (maiusculo) na tabela ascii
    int color = 1;
    for (int i = 0; i < n; i++)
    {
        printf("%c ", a); //Imprimindo coordenadas da linha.

        for (int j = 0; j < m; j++)
        {
            if (color % 2 != 0) // Estilização do jogo.Caso color seja ímpar,a cor ao redor dos pinos será verde,caso seja par a cor será preta
            {
                if (matrizjogo[i][j] == -1)
                {
                    printf("%3c", menosum); 
                }
                else if (matrizjogo[i][j] == 0)
                {
                    printf(BG_RED("%3c"), zero); // Caso seja um buraco,a cor será vermelha.Caso seja uma área restrita,não apresentará cor
                }
                else if (matrizjogo[i][j] == 1)
                {
                    printf(BG_GREEN("%3c"), um);
                }
            }
            else
            {

                if (matrizjogo[i][j] == -1)
                {
                    printf("%3c", menosum);
                }
                else if (matrizjogo[i][j] == 0)
                {
                    printf(BG_RED("%3c"), zero);
                }
                else if (matrizjogo[i][j] == 1)
                {
                    printf(BG_BLACK("%3c"), um);
                }
            }

            color++;
        }
        printf("\n");
        a++; // a++ Para o print da coordenada das linhas acompanharem a tabela ascii
    }
}

void imprimirMenu()
{
    // Impressão do menu com os possíveis comandos de execução
    printf("\n"
           "\n" BG_WHITE(BLACK(BOLD("-------------Comandos básicos------------- ") "\n"
                                                                                   "\n")));
    printf(CYAN(BOLD("\nDigite \"salvar\" exemplo.txt: para salvar o jogo atual.\n")));
    printf(CYAN(BOLD("\nDigite \"sair\": para sair do jogo.\n")));
    printf("\n"
           "\n" BG_WHITE(BLACK(BOLD("-------------Comandos de ação------------- ") "\n"
                                                                                   "\n")));
    printf(CYAN(BOLD("\nComando \"c\": move o pino para cima.\n")));
    printf(CYAN(BOLD("\nComando \"b\": move o pino para baixo.\n")));
    printf(CYAN(BOLD("\nComando \"e\": move o pino para esquerda.\n")));
    printf(CYAN(BOLD("\nComando \"d\": move o pino para direita.\n")));
    printf(CYAN(BOLD("\nComando \"ajuda\": executa e informa um movimento possível.\n")));
    printf(BOLD(RED("\nExemplo de movimento: c aB -> move o pino da linha 'a' e coluna 'B' para cima.\n")));
    printf(BOLD(RED("\nExemplo de ajuda: ajuda 20 -> Executa e informa 20 movimentos feitos pelo computador.\n\n")));
}

void recepcao()
{
    // Função que imprime Bem vindo ao resta um
    printf("\n" TAB_HOR TAB_HOR TAB_HOR TAB_HOR);
    printf(TAB_VER BOLD(BG_RED("Bem vindo ao Resta UM!!!")));
    printf(TAB_VER TAB_HOR TAB_HOR TAB_HOR TAB_HOR);
}

void lerEntrada(char comando[K], int **matrizjogo, int n, int m)
{
    char cord1, cord2, salvarNome[K];
    int ajd;

    for (int i = 1; i > 0; i++) // 'For' feito infinitamente,pois não há motivos para condiciona-lo
    {
        printf(BOLD("\n\nDigite um comando: ")); // Leitura do comando
        fgets(comando, 100, stdin);
        int tam = strlen(comando) - 1;
        comando[tam] = '\0';

        // Caso seja escolhido um comando de movimentação, cord1 e cord2 armazenam as cordenadas do pino.

        if (comando[0] == 'c' || comando[0] == 'b' || comando[0] == 'e' || comando[0] == 'd')
        {
            cord1 = comando[2];
            cord2 = comando[3];
            comando[1] = '\0'; // Após armazenar as cordenadas, o '\0' entra logo após o comando de movimento para finalizar a string sem as coordenadas do pino.
        }
        // Caso seja escolhido o comando 'salvar',a string "salvarNome" armazena o nome do arquivo txt digitado pelo usuário.
        else if (strncmp(comando, "salvar" , 6) == 0)
        {
            int P = 7;

            for (int i = 0; i < K; i++)
            {
                salvarNome[i] = comando[P]; // P inicializa com 7, pois é o primeiro caractere após "salvar ".
                P++;
            }
            comando[6] = '\0'; // Após armazenar o nome do arquivo,o '\0' entra logo após o comando "salvar" para finalizar a string sem o nome do arquivo.
        }
        // Caso seja escolhido o comando 'ajuda', a variável 'ajd' armazena o número de ajudas solicitado pelo usuário 
        else if(strncmp(comando, "ajuda" , 5) == 0)
        {
            ajd = atoi(&comando[6]); // ajd recebendo os números inteiros(ja codificados) da string apartir do comando[6](número inteiro após o 'espaço' e "ajuda")
            comando[5] = '\0'; // Após armazenar o número de ajudas desejado,o '\0' entra logo após o comando "ajuda" para finalizar a string sem o número inteiro
        }
        

        // Caso seja selecionado um comando de movimentação,será passado como argumento as coordenadas(armazenadas pelo if anteriormente),assim como a matriz e suas dimensões.
        if (strcmp(comando, "c") == 0)
        {
            moverC(matrizjogo, cord1, cord2, n, m);

            analisarJogo(matrizjogo, n, m);

        }
        else if (strcmp(comando, "b") == 0)
        {
            moverB(matrizjogo, cord1, cord2, n, m);

            analisarJogo(matrizjogo, n, m);

        }
        else if (strcmp(comando, "e") == 0)
        {
            moverE(matrizjogo, cord1, cord2, n, m);

            analisarJogo(matrizjogo, n, m);

        }
        else if (strcmp(comando, "d") == 0)
        {
            moverD(matrizjogo, cord1, cord2, n, m);

            analisarJogo(matrizjogo, n, m);

        }
        else if (strcmp(comando, "sair") == 0)
        {
            printf("\n" BG_WHITE(BLACK(BOLD("Obrigado por jogar!!Te esperamos novamente!"))) "\n""\n");
            liberaMatriz(matrizjogo, n); // Liberando a matriz alocada antes do encerramento do programa
            exit(0);
        }
        // Caso seja selecionado o comando 'salvar',será passado como argumento o nome do arquivo digitado pelo usuário(armazenado pelo if anteriormente),assim como a matriz e suas dimensões.
        else if (strcmp(comando, "salvar") == 0)
        {
            salvarJogo(matrizjogo, n, m, salvarNome);
        }
        else if (strcmp(comando, "ajuda") == 0)
        {
            for(int i = 0; i < ajd ; i++) // O 'For' é condicionado pela variavel 'ajd', definida pelo usuário ao passar o número de ajudas.
            {
                ajuda(matrizjogo , n , m);
                
                analisarJogo(matrizjogo, n , m);
            }   
        }
        else // Caso nenhum comando seja validade,é imprimido uma mensagem de erro e a situação atual do jogo.Após o erro o jogo continua normalmente. 
        {
            printf(BOLD(RED("\nComando inválido!!")) "\nStatus atual do jogo:\n");
        }

        imprimirTabuleiro(matrizjogo, n, m);
        printf("\n");
    }
}

void moverC(int **matrizjogo, char cord1, char cord2, int n, int m)
{
    int coord1, coord2;
    int corecoluna = 65, corecolunaaux = 1;
    int corelinha = 65, corelinhaaux = 1;

    for (int i = 0; i < n; i++) // Transformando as coordenadas(dada por letras),em número por meio da tabela ascii.
    {

        if (cord1 == corelinha) // Identificando o caractere 'linha' e atribuindo seu respectivo número.
        {
            coord1 = corelinhaaux;
        }

        for (int j = 0; j < m; j++)
        {

            if (cord2 == corecoluna) // Identificando o caractere 'coluna' e atribuindo seu respectivo número.
            {
                coord2 = corecolunaaux;
            }

            corecolunaaux++;
            corecoluna++;
        }

        corelinha++;
        corelinhaaux++;
    }
    // Verificando se o movimento 'cima' é possível,em caso afirmativo o movimento é consolidado.
    if (coord1 - 3 >= 0 && matrizjogo[coord1 - 1][coord2 - 1] == 1 && matrizjogo[coord1 - 2][coord2 - 1] == 1 && matrizjogo[coord1 - 3][coord2 - 1] == 0)
    {
        matrizjogo[coord1 - 1][coord2 - 1] = 0;
        matrizjogo[coord1 - 2][coord2 - 1] = 0;
        matrizjogo[coord1 - 3][coord2 - 1] = 1;
    }
    else
    {
        printf(BOLD(RED("\n\nErro! Infelizmente você não pode executar essa jogada!\nStatus atual do jogo:\n\n")));
    }
}

void moverB(int **matrizjogo, char cord1, char cord2, int n, int m)
{
    int coord1, coord2;
    int corecoluna = 65, corecolunaaux = 1;
    int corelinha = 65, corelinhaaux = 1;

    for (int i = 0; i < n; i++) // Transformando as coordenadas(dada por letras),em números por meio da tabela ascii.
    {

        if (cord1 == corelinha) // Identificando o caractere 'linha' e atribuindo seu respectivo número.
        {
            coord1 = corelinhaaux;
        }

        for (int j = 0; j < m; j++)
        {

            if (cord2 == corecoluna) // Identificando o caractere 'coluna' e atribuindo seu respectivo número.
            {
                coord2 = corecolunaaux;
            }

            corecolunaaux++;
            corecoluna++;
        }

        corelinha++;
        corelinhaaux++;
    }
    // Verificando se o movimento 'baixo' é possível,em caso afirmativo o movimento é consolidado.
    if (coord1 + 1 < n && matrizjogo[coord1 - 1][coord2 - 1] == 1 && matrizjogo[coord1][coord2 - 1] == 1 && matrizjogo[coord1 + 1][coord2 - 1] == 0)
    {
        matrizjogo[coord1 - 1][coord2 - 1] = 0;
        matrizjogo[coord1][coord2 - 1] = 0;
        matrizjogo[coord1 + 1][coord2 - 1] = 1;
    }
    else
    {
        printf(BOLD(RED("\n\nErro! Infelizmente você não pode executar essa jogada!\nStatus atual do jogo:\n\n")));
    }
}

void moverE(int **matrizjogo, char cord1, char cord2, int n, int m)
{
    int coord1, coord2;
    int corecoluna = 65, corecolunaaux = 1;
    int corelinha = 65, corelinhaaux = 1;

    for (int i = 0; i < n; i++) // Transformando as coordenadas(dada por números),em letras por meio da tabela ascii.
    {

        if (cord1 == corelinha) // Identificando o caractere 'linha' e atribuindo seu respectivo número.
        {
            coord1 = corelinhaaux;
        }

        for (int j = 0; j < m; j++)
        {

            if (cord2 == corecoluna) // Identificando o caractere 'coluna' e atribuindo seu respectivo número.
            {
                coord2 = corecolunaaux;
            }

            corecolunaaux++;
            corecoluna++;
        }

        corelinha++;
        corelinhaaux++;
    }
    // Verificando se o movimento 'esquerda' é possível,em caso afirmativo o movimento é consolidado.
    if (coord2 - 3 >= 0 && matrizjogo[coord1 - 1][coord2 - 1] == 1 && matrizjogo[coord1 - 1][coord2 - 2] == 1 && matrizjogo[coord1 - 1][coord2 - 3] == 0)
    {
        matrizjogo[coord1 - 1][coord2 - 1] = 0;
        matrizjogo[coord1 - 1][coord2 - 2] = 0;
        matrizjogo[coord1 - 1][coord2 - 3] = 1;
    }
    else
    {
        printf(BOLD(RED("\n\nErro! Infelizmente você não pode executar essa jogada!\nStatus atual do jogo:\n\n")));
    }
}

void moverD(int **matrizjogo, char cord1, char cord2, int n, int m)
{
    int coord1, coord2;
    int corecoluna = 65, corecolunaaux = 1;
    int corelinha = 65, corelinhaaux = 1;

    for (int i = 0; i < n; i++) // Transformando as coordenadas(dada por números),em letras por meio da tabela ascii.
    {

        if (cord1 == corelinha) // Identificando o caractere 'linha' e atribuindo seu respectivo número.
        {
            coord1 = corelinhaaux;
        }

        for (int j = 0; j < m; j++)
        {

            if (cord2 == corecoluna) // Identificando o caractere 'coluna' e atribuindo seu respectivo número.
            {
                coord2 = corecolunaaux;
            }

            corecolunaaux++;
            corecoluna++;
        }

        corelinha++;
        corelinhaaux++;
    }
    // Verificando se o movimento 'direita' é possível,em caso afirmativo o movimento é consolidado.
    if (coord2 + 1 < m && matrizjogo[coord1 - 1][coord2 - 1] == 1 && matrizjogo[coord1 - 1][coord2] == 1 && matrizjogo[coord1 - 1][coord2 + 1] == 0)
    {
        matrizjogo[coord1 - 1][coord2 - 1] = 0;
        matrizjogo[coord1 - 1][coord2] = 0;
        matrizjogo[coord1 - 1][coord2 + 1] = 1;
    }
    else
    {
        printf(BOLD(RED("\n\nErro! Infelizmente você não pode executar essa jogada!\nStatus atual do jogo:\n\n")));
    }
}

void salvarJogo(int **matrizjogo, int n, int m, char salvarNome[K])
{
    // Salva o jogo no arquivo definido pelo usuário.

    FILE *saida = fopen(salvarNome, "w");
    fprintf(saida, "%d %d\n\n", n, m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            fprintf(saida, "%3d", matrizjogo[i][j]);
        }
        fprintf(saida, "\n");
    }

    fclose(saida);

    printf(BOLD("\nJogo salvo em arquivo: %s\n\n"), salvarNome);
}
    
void analisarJogo(int **matrizjogo, int n, int m)
{
    int vitoria = 0, jogadaspossiveis = 0;

    for (int i = 0; i < n; i++) // O 'for' percorre a matriz inteira contando os pinos presentes no jogo.
    {
        for (int j = 0; j < m; j++)
        {
            if (matrizjogo[i][j] == 1)
            {
                vitoria++;
            }
        }
    }

    if (vitoria == 1) // Caso reste apenas um pino,o usuário é vencedor.
    {
        printf("\n" CYAN(BOLD("Parabéns!!!Você venceu!")) "\n");
        printf(BOLD("\nJogo vencedor: \n\n"));
        imprimirTabuleiro(matrizjogo, n, m);
        printf("\n");
        liberaMatriz(matrizjogo, n); // Libera a matriz alocada antes do encerramento do programa
        exit(0);
    }
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (matrizjogo[i][j] == 1) // O 'for' percorre a matriz inteira a procura de pinos restantes.
            {
                // Ao achar um pino,o 'if' analiza se é possível executar algum tipo de jogada.Caso seja possivel,o usuário segue o jogo.
                if (i-2 >= 0 && matrizjogo[i - 1][j] == 1 && matrizjogo[i - 2][j] == 0) // comando cima
                {
                    jogadaspossiveis++; 
                }

                else if (i+2 < n && matrizjogo[i + 1][j] == 1 && matrizjogo[i + 2][j] == 0) // comando baixo
                {
                    jogadaspossiveis++; 
                }
                
                else if (j+2 < m && matrizjogo[i][j + 1] == 1 && matrizjogo[i][j + 2] == 0) // comando direita
                {
                    jogadaspossiveis++; 
                }
                else if (j-2 >= 0 && matrizjogo[i][j - 1] == 1 && matrizjogo[i][j - 2] == 0) // comando esquerda
                {
                    jogadaspossiveis++; 
                }
                
            }
        }
    }

    if (jogadaspossiveis == 0) // Caso não exista mais jogadas possíveis e o usuário não ganhou,ele perde.
    {
        printf("\n" CYAN(BOLD("Você perdeu!!"))"\n""\n");
        liberaMatriz(matrizjogo, n); // Liberando a matriz alocada antes do encerramento do programa
        exit(0);
    }
}

void ajuda(int **matrizjogo,int n , int m)
{
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0; j < m ; j++)
        {
            if(matrizjogo[i][j] == 1) // Procura por algum pino existente
            {
                if(i-2 >= 0 && matrizjogo[i - 1][j] == 1 && matrizjogo[i - 2][j] == 0) // Caso o comando 'cima' seja possível,o programa executa
                {
                    matrizjogo[i][j] = 0;
                    matrizjogo[i - 1][j] = 0;
                    matrizjogo[i - 2][j] = 1;
                    printf("\nFoi executado o comando 'c' nas coordenadas %c%c\n\n", i + 65,j + 65); // +65 para ser impresso em letras na coordenada
                    return;
                }
                else if(i+2 < n && matrizjogo[i + 1][j] == 1 && matrizjogo[i + 2][j] == 0 ) // Caso o comando 'baixo' seja possível,o programa executa
                {
                    matrizjogo[i][j] = 0;
                    matrizjogo[i + 1][j] = 0;
                    matrizjogo[i + 2][j] = 1;
                    printf("\nFoi executado o comando 'b' nas coordenadas %c%c\n\n", i + 65,j + 65); // +65 para ser impresso em letras na coordenada
                    return;
                }
                else if(j-2 >= 0 && matrizjogo[i][j - 1] == 1 && matrizjogo[i][j - 2] == 0) // Caso o comando 'esquerda' seja possível,o programa executa
                {
                    matrizjogo[i][j] = 0;
                    matrizjogo[i][j - 1] = 0;
                    matrizjogo[i][j - 2] = 1;
                    printf("\nFoi executado o comando 'e' nas coordenadas %c%c\n\n", i + 65,j + 65); // +65 para ser impresso em letras na coordenada
                    return;
                }
                else if(j+2 < m && matrizjogo[i][j + 1] == 1 && matrizjogo[i][j + 2] == 0) // Caso o comando 'direita' seja possível,o programa executa
                {
                    matrizjogo[i][j] = 0;
                    matrizjogo[i][j + 1] = 0;
                    matrizjogo[i][j + 2] = 1;
                    printf("\nFoi executado o comando 'd' nas coordenadas %c%c\n\n", i + 65,j + 65); // +65 para ser impresso em letras na coordenada
                    return;
                }
            }

        }
    }
}

int **criaMatriz(int n , int m)
{
    // Criando matriz dinâmicamente
    int **matriz;
    matriz = malloc (n * sizeof(int *));

    for(int i = 0; i < n ; i++)
    {
        matriz[i] = malloc (m * sizeof(int));
    }

    return matriz;

}

void liberaMatriz(int **matrizjogo , int n)
{
    // Função para liberar a matriz alocada dinâmicamente
    for(int i = 0; i < n ; i++)
    {
        free(matrizjogo[i]);
    }

    free(matrizjogo);
}