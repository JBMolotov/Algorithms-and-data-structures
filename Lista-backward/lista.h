#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no No;
typedef struct backward Lista;

Lista* Cria();
void Insere(Lista *l, int n, int j);
void Imprime(Lista *l);
int Remove(Lista *l, int x);
void Destroi(Lista *l);
