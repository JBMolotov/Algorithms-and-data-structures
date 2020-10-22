#include "lista.h"

struct no {
    int chave, tempo;
    struct no *prox, *ant,*back;
};

struct backward {
    int tempo_atual;
    No *ini, *fim;
};

Lista* Cria() {
    Lista *l = malloc(sizeof(Lista)); // instancia lista
    // define lista vazia
    l->tempo_atual = 0;
    l->ini = NULL;
    l->fim = NULL;
    return l;
}

void Destroi(Lista *l) {
    // apaga chaves
    No *aux;
    while (l->ini != NULL) {
        aux = l->ini;
        l->ini = l->ini->prox;
        free(aux);
    }
    // apaga lista
    free(l);
    l = NULL;
}

void Insere(Lista *l, int n, int j) {
    No *aux;
    // cria no auxiliar
    aux = malloc(sizeof(No));
    aux->chave = n;
    aux->tempo = l->tempo_atual;
    aux->prox = NULL;
    aux->ant = l->fim; //Inserido no final

    // atualiza ponteiros e tempo
    if (l->fim != NULL)
        l->fim->prox = aux;
    l->fim = aux;
    if (l->ini == NULL)
        l->ini = aux;

    // atualiza o back
    if(j > 0)
    {
        aux->back = l->fim; //back começa como ultimo
        for(int i = 1; i <= j; i++)
        {
            aux->back = aux->back->ant;
        }
    }
    else //se o j for 0, back é null
        aux->back = NULL;

    l->tempo_atual ++;
}

int AcharPos(No* ini, No* back)
{
    int count = 0;
    No *aux = ini;
    while(back != aux)
    {
        aux = aux->prox;
        count ++;
    }

    return count;
}

void Imprime(Lista *l) {
    No *aux = l->ini;
    if(aux==NULL)
    { //Caso a lista esteja vazia
        printf("-1");
        return;
    }

    while (aux != NULL) 
    {
        if (aux->back == NULL)
            printf("[%d,%d] ", aux->chave, aux->tempo);
        else
            printf("[%d,%d,%d] ", aux->chave, aux->tempo, AcharPos(l->ini,aux->back));
        aux = aux->prox;
    }
    printf("\n");
}

void RemoveBack(No* ini, No* atual)
{ //Função para remover possiveis ponteiros para n 
    No *aux = ini;
    while (aux != NULL) 
    {
        if(aux->back == atual)
        {
            aux->back = NULL;
        }
        aux = aux->prox;
    }
}

int Remove(Lista *l, int n) {
    No *atual;
    atual = l->ini;
    l->tempo_atual ++;
    while (atual != NULL) {
        if (atual->chave == n) { // encontrou, entao apaga
            RemoveBack(l->ini, atual);
            if (atual == l->ini && atual == l->fim)
            {
                l->ini = NULL;
                l->fim = NULL;
            }
            else
            {
                if (atual == l->ini)
                {
                    l->ini = atual->prox; // setar novo inicio
                } 
                else if (atual == l->fim)
                {
                    l->fim = atual->ant; // para quando removeu o ultimo
                    l->fim->prox = NULL;
                }
                else
                {
                    atual->ant->prox = atual->prox; // atualiza o proximo do anterior para o seguinte
                    atual->prox->ant = atual->ant; // atualiza o anterior do proximo para o anterior 
                }
                    
            }
            
            free(atual); // apaga
            return 1; // sucesso
        }
        atual = atual->prox;
    }
    return 0; // nao achou
}