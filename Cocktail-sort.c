#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[100];
    char cidade[100];
} Pessoa;

void lerPessoas(Pessoa* p, int i);
void cocktail_sort(Pessoa* p, int n);
int buscarCidade(Pessoa* p, char nome[100], int n);

int main(void)
{
    int n, k;
    Pessoa *p;

    scanf("%d ", &n);
    p = malloc(sizeof(Pessoa)*n);

    for (int i = 0; i < n; i++)
    {
        lerPessoas(p, i);
    }

    cocktail_sort(p, n);

    for (int j = 0; j < n; j++)
    {
        printf("%s.\n", p[j].nome);
    }
    scanf("%d", &k);
    char nome[100];

    for (int j = 0; j < k; j++)
    {
        scanf("%[^.]s", nome);
        getchar(); //Consome o .
        getchar(); //Consome o enter
        printf("%d\n", buscarCidade(p, nome, n));
    }

    return 0;
}

void lerPessoas(Pessoa* p, int i)
{
    scanf("%[^.]s", p[i].nome);
    getchar();
    getchar();
    scanf("%[^\n]s", p[i].cidade);
    getchar();
}

void cocktail_sort(Pessoa* p, int n)
{
    int bottom, top, swapped, i;
    Pessoa aux;
    bottom = 0;
    top = n - 1;
    swapped = 0; 
    while(swapped == 0 && bottom < top)
    {
        swapped = 1;
        for(i = bottom; i < top; i++)
        {
            int j = 0;
            while (p[i].nome[j] == p[i+1].nome[j])
            { //Função que verifica se a letra é a mesma
                j++;
            }
            
            if(p[i].nome[j] > p[i + 1].nome[j])
            {
                aux = p[i];
                p[i] = p[i+1];
                p[i+1] = aux;
                swapped = 0;
            }
        }
        top = top - 1; 
        for(i = top; i > bottom; i--)
        {  
            int j = 0;
            while (p[i].nome[j] == p[i-1].nome[j])
            { //Função que verifica se a letra é a mesma
                j++;
            }
            if(p[i].nome[j] < p[i-1].nome[j]) 
            {
                aux = p[i];
                p[i] = p[i-1];
                p[i-1] = aux;
                swapped = 0;
            }
        }
        bottom = bottom + 1;  
    }
 }

int buscarCidade(Pessoa* p, char nome[100], int n)
{
    for(int i = 0; i < n; i++)
    {
        if ((strcmp(nome, p[i].nome) == 0))
        {
            return (strcmp(p[i].cidade, "Sao Carlos.")==0);
        }
    }
    return 0;
}

//JBMolotov