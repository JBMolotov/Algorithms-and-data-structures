#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

struct no 
{
    char numero;
    struct no *prox;
    struct no *ant;
};

struct lista 
{
    No *ini, *fim;
    char sinal; //0 = neg, 1 = pos
};

Lista* Cria() 
{
    Lista *l;
    l = malloc(sizeof(Lista)); // instancia lista
    // define lista vazia
    l->ini = NULL;
    l->fim = NULL;
    l->sinal = 1;
    return l;
}

void Destroi(Lista *l) 
{
    // apaga elementos
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

Lista* Limpa(Lista *l) 
{
    Destroi(l);
    l = Cria();
    return l;
}

void Negativar(Lista *l)
{
    l->sinal = 0;
}

// insere no inicio
void InsereInicio(Lista *l, int x)
{
    No *aux;
    // cria no
    aux = malloc(sizeof(No));
    aux->numero = x;
    aux->prox = l->ini;
    aux->ant = NULL;
    if(l->ini != NULL)
        l->ini->ant = aux;
    // atualiza lista
    l->ini = aux;
    if (l->fim == NULL)
        l->fim = aux;
}

void InsereFim(Lista *l, int x)
{
    if (l->fim == NULL && x == 0)
        return;
    No *aux;
    // cria no
    aux = malloc(sizeof(No));
    aux->numero = x;
    aux->prox = NULL;
    aux->ant = l->fim;
    // atualiza ponteiros
    if (l->fim != NULL)
        l->fim->prox = aux;
    l->fim = aux;
    if (l->ini == NULL)
        l->ini = aux;
}

void Imprime(Lista *l) 
{
    No *aux = l->ini;
    while (aux != NULL) {
        printf("%d", aux->numero);
        aux = aux->prox;
    }
    printf("\n");
}

int Tamanho(Lista *l)
{
    No *aux = l->ini;
    int contagem = 0;
    while (aux != NULL) {
        contagem++;
        aux = aux->prox;
    }
    return contagem;
}


int Maior(Lista *num1, Lista *num2)
{
    //Verifica se o sinais são diferentes, se somente um negativo, ja temos a respsota
    if (num1->sinal > num2->sinal)
        return 1;
    else if (num2->sinal > num1->sinal)
        return 0;

    int tam_num1 = Tamanho(num1);
    int tam_num2 = Tamanho(num2);

    if(tam_num1 > tam_num2)
        return 1;
    else if (tam_num1 < tam_num2)
        return 0;
    else
    {
        No *aux1 = num1->ini;
        No *aux2 = num2->ini;
        
        for (int i = 0; i < tam_num1; i++)
        {
            if (aux1->numero > aux2->numero)
                return 1;
            else if (aux2->numero > aux1->numero)
                return 0;
            else
            {
                aux1 = aux1->prox;
                aux2 = aux2->prox;
            }
        }
    }

    return 0;
}

int Igual(Lista *num1, Lista *num2)
{
    //Verifica se o sinais são diferentes, se somente um negativo, ja temos a respsota
    if (num1->sinal != num2->sinal)
        return 0;

    if(Tamanho(num1) != Tamanho(num2))
    {
        return 0;
    }   
    else
    {
        No *aux1 = num1->ini;
        No *aux2 = num2->ini;
        
        while (aux1 != num1->fim)
        {
            if (aux1->numero != aux2->numero)
                return 0;
            else
            {
                aux1 = aux1->prox;
                aux2 = aux2->prox;
            }
        }
    }

    return 1;
}

Lista* Soma(Lista *num1, Lista *num2)
{ 
    No *aux1 = num1->fim;
    No *aux2 = num2->fim;

    Lista *total;
    total = Cria();

    int x = 0;
    
    while (aux1 != NULL || aux2 != NULL) //Caracteriza inicio apontando ao ant
    {
        //Se algum numero for menor em tamanho na lista, continua adicionando
        if (aux1 == NULL)
            x += aux2->numero;
        else if (aux2 == NULL)
            x += aux1->numero;
        else
            x += aux1->numero + aux2->numero;

        //Seguindo a logica de soma, os numeros sao adicionados pela frente
        if (x >= 10)
        {
            x -= 10;
            InsereInicio(total, x);
            x = 1;
        }
        else
        {
            InsereInicio(total, x);
            x = 0;
        }

        if(aux1 != NULL)
            aux1 = aux1->ant;
        if(aux2 != NULL)
            aux2 = aux2->ant;
    }

    //Se x for diferente de 0, adiciona esse numero na frente, que seria o remanescente da soma
    if (x != 0)
        InsereInicio(total, x);

    return total;
}