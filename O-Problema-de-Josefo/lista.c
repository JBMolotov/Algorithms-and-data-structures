#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

struct pessoa
{
	int info;
	struct pessoa *proximo, *anterior;
};

struct lista
{
	Pessoa *inicio, *fim;
    int totalElementos;
};


Lista* CriarLista()
{
	Lista *pLista = malloc(sizeof(Lista));
	pLista->inicio = pLista->fim = NULL;
	pLista->totalElementos = 0;

	return pLista;
}

int ListaVazia(Lista *pLista)
{
	return !pLista->inicio;
}

//Preenche a lista com numeros de 1 a n
void PreencheLista(Lista *pLista, int n)
{
    for (int i = 1; i <= n; i++)
    {
        Insere(pLista, i);
    }
}

int Insere(Lista *pLista, int x)
{
	Pessoa *novaPessoa = (Pessoa *)malloc(sizeof(Pessoa));

	if (!novaPessoa)
		return -1; // Erro ao alocar
	else
	{
		novaPessoa->info = x;

		if (ListaVazia(pLista))
		{
			novaPessoa->proximo = novaPessoa;	
			novaPessoa->anterior = novaPessoa;
			pLista->inicio = novaPessoa;
		}
		else
		{
			novaPessoa->anterior = pLista->fim;
			novaPessoa->proximo = pLista->inicio;

			pLista->fim->proximo = novaPessoa; 
			pLista->inicio->anterior = novaPessoa;
		}

		pLista->fim = novaPessoa;
		return pLista->totalElementos++;
	}
}

// Remove Pessoa da lista
int Remove(Lista *pLista, Pessoa *x)
{
    //Atualizar encadeamento
    x->anterior->proximo = x->proximo;
    x->proximo->anterior = x->anterior;

    if (x == pLista->fim)
    {
        pLista->fim = x->anterior;
        pLista->inicio->anterior = x->anterior;

        if (pLista->inicio == x)
            pLista->inicio = pLista->fim = NULL;
    }
    else if (x == pLista->inicio)
    {
        pLista->inicio = x->proximo;
        pLista->fim->proximo = x->proximo;
    }    

    free(x);
    return pLista->totalElementos--;
	
}

//Remove periodicamente todas as ocorrencias da lista e retorna o valor que sobrar
int RemoveIndex(Lista *pLista, int k)
{
    int index = 1;
    Pessoa *pIndex = pLista->inicio;

    while (pLista->totalElementos > 1) //Enquanto não tirar o penultimo, continua contando
    {
        if (index == k)
        {
            index = 1;
            Pessoa *pDelete = pIndex;
            pIndex = pIndex->proximo;
            Remove(pLista, pDelete);
            
        }
        else
        {
            index++;
            pIndex = pIndex->proximo;
        }
        
    } 
    return pIndex->info;
}

void Destroi(Lista *pLista)
{
    //Como só vai sobrar um elemento
    free(pLista->inicio);
    free(pLista);
}