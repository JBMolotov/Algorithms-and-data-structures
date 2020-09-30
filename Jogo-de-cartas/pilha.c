#include "pilha.h"

// cria pilha
void create(Pilha *p) {
    p->topo = -1;
    return;
}

// insere na pilha
int push(Pilha *p, elem x) {
    if (isFull(p))
        return 1; // erro, pilha cheia
    p->topo++; // atualiza o topo
    p->vet[p->topo] = x; // copia informacao
    return 0; // sucesso
}

// remove da pilha
int pop(Pilha *p, elem *x) {
    if (isEmpty(*p))
        return 1; // erro, pilha vazia
    *x = p->vet[p->topo]; // copia informacao
    p->topo--; // atualiza o topo
    //p->topo--;
    //*x = p->vet[p->topo+1];
    return 0; // sucesso
}

// consulta topo
int top(Pilha *p, elem *x) {
    if (isEmpty(*p))
        return 1; // erro, pilha vazia
    *x = p->vet[p->topo];
    return 0; // sucesso
}

