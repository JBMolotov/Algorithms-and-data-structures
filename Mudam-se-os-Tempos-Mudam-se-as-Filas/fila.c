#include "fila.h"

void cria(Fila *f) {
    //f->ini = f->fim = f->total = 0;
    f->ini = 0;
    f->fim = 0;
    f->total = 0;
    return;
}

void esvazia(Fila *f) {
    cria(f);
    return;
}

int estaVazia(Fila *f) {
    //return (f->total == 0);
    //return (!(f->total));
    if (f->total == 0)
        return 1; // fila vazia
    else
        return 0; // fila nao vazia
}

int estaCheia(Fila *f) {
    return (f->total == TAM);
}

void avanca(int *valor) {
    if (*valor == TAM - 1)
        *valor = 0; // reinicia
    else
        (*valor)++;
    return;
}

int entra(Fila *f, Pessoa x) {
    if (estaCheia(f))
        return 1; // erro
    f->vet[f->fim] = x; // copia elemento
    f->total++; // incrementa total
    avanca(&(f->fim)); // avanca fim
    return 0; // sucesso
}

int sai(Fila *f, Pessoa *x) {
    if (estaVazia(f))
        return 0; // erro, invertido para uso da saida
    *x = f->vet[f->ini]; // copia elemento
    f->total--; // decrementa total
    avanca(&(f->ini)); // avanca ini
    return 1; // sucesso
}

