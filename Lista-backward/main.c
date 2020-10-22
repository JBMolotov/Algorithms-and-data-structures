#include "lista.h"

int LerOperacoes(char *op, Lista *l);

int main(void) {
    char *op = malloc(2);

    Lista *l = Cria();
    
    while(1)
    {
        scanf("%c", op);
        if (LerOperacoes(op, l))
        {
            break;
        }
    }

    Imprime(l);

    Destroi(l);
    
    return 0; // sucesso
}

int LerOperacoes(char *op, Lista *l)
{
    int n, j;

    switch (*op)
    {
        case 'f': //Sai do loop
            return 1;
        case 'i':
            scanf("%d %d", &n, &j);
            Insere(l, n, j);
            break;
        case 'r':
            scanf("%d", &n);
            Remove(l, n);
            break;
    }
    return 0;
}

//JBMolotov