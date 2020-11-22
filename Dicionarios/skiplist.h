#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX 24

typedef struct no 
{
    char *palavra, *definicao;
    struct no **prox;
} No;

typedef struct skiplist
{
    No *inicio;
    int nivel;
} SkipList;

SkipList* Cria();
No* NovoNo(int nivel, char *palavra, char *definicao);
void Libera(SkipList* sk);
void Insere (SkipList *sk, char *palavra, char *definicao);
void Altera (SkipList *sk, char *palavra, char *definicao);
void Remove(SkipList *sk, char *palavra);
void Imprime(SkipList *sk, char ch);
void ImprimeBusca(SkipList *sk, char *palavra);
