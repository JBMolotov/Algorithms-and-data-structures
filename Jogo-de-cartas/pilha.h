#define TAM 100

typedef int elem;

typedef struct {
    elem vet[TAM];
    int topo;
} Pilha;

// cria pilha
void create(Pilha *p);

// esvazia pilha
void empty(Pilha *p);

// esta vazia?
int isEmpty(Pilha p); // parametro passado por valor

// esta cheia?
int isFull(Pilha *p); // parametro passado por referecia

// insere na pilha
int push(Pilha *p, elem x);

// remove da pilha
int pop(Pilha *p, elem *x);

// consulta topo
int top(Pilha *p, elem *x);
