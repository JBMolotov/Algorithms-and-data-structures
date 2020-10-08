#define TAM 10

typedef struct {
    char nome[20];
    int idade, saude;
} Pessoa;

typedef struct {
    int ini, fim, total;
    Pessoa vet[TAM];
} Fila;

void cria(Fila *f);
void esvazia(Fila *f);
int estaVazia(Fila *f);
int estaCheia(Fila *f);
int entra(Fila *f, Pessoa x);
int sai(Fila *f, Pessoa *x);
