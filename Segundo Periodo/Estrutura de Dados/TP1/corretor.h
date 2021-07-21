# ifndef corretor_h
# define corretor_h

typedef struct submissao TADsubmissao;

void lerSubmissao (int *n);

TADsubmissao *alocaSubmissao(TADsubmissao *S,int n);

TADsubmissao *desalocaSubmissao(TADsubmissao *S);

void povoarSubmissao(TADsubmissao *S, int n);

int nCorretos(TADsubmissao *S, int n);

int nTempo(TADsubmissao *S, int n);

void printSaida(int s, int p);


# endif