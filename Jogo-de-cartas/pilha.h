#define TAM 100000

typedef int elem;

typedef struct {
    elem vet[TAM];
    int topo;
} Pilha;

// cria pilha
void create(Pilha *p);

// insere na pilha
int push(Pilha *p, elem x);

// remove da pilha
int pop(Pilha *p, elem *x);

// consulta topo
int top(Pilha *p, elem *x);
