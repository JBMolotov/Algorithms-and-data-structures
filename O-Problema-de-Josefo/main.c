#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
	Lista *pLista = CriarLista();
    int n, k, t; 
    scanf("%d", &t);
    for (int i = 1; i <= t; i ++)
    { //Casos
        pLista = CriarLista();
        scanf("%d %d", &n, &k);
        PreencheLista(pLista, n);
        printf("Caso %d: %d\n", i, RemoveIndex(pLista, k));
    }

    Destroi(pLista);
	return 0;
}

//JBMolotov