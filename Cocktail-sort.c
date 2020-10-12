// Johnny Silva
// 11371350

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char nome[100];
    char cidade[100];
} Pessoa;

//Função de ler nome das pessoas e suas respectivas cidades
void lerPessoas(Pessoa* p, int i);
//Função que organiza p com cocktail sort
void cocktail_sort(Pessoa* p, int n);
//função que busca se a cidade é são carlos e retorna 1 caso sim ou 0 caso não
int buscarCidade(Pessoa* p, int n);

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
    
    scanf("%d ", &k);
    for (int j = 0; j < k; j++)
    {
        printf("%d\n", buscarCidade(p, n));
    }

    free(p);

    return 0;
}

void lerPessoas(Pessoa* p, int i)
{
    scanf("%[^.]s", p[i].nome);
    getchar(); //Consome Ponto
    getchar(); //Consome espaço
    scanf("%[^.]s", p[i].cidade);
    getchar(); //Consome ponto
    getchar(); //Consome \n
    getchar(); //Consome \r
}

void cocktail_sort(Pessoa* p, int n)
{
    int bottom, top, swap, i;
    Pessoa aux;
    bottom = 0;
    top = n - 1;
    swap = 0; 
    while(swap == 0 && bottom < top)
    {
        swap = 1;
        for(i = bottom; i < top; i++)
        {
            int j = 0;
            while (tolower(p[i].nome[j]) == tolower(p[i+1].nome[j]))
            { //Função que verifica se a letra é a mesma
                j++;
            }
            
            if(tolower(p[i].nome[j]) > tolower(p[i + 1].nome[j]))
            {
                aux = p[i];
                p[i] = p[i+1];
                p[i+1] = aux;
                swap = 0;
            }
        }
        top = top - 1; 
        for(i = top; i > bottom; i--)
        {  
            int j = 0;
            while (tolower(p[i].nome[j]) == tolower(p[i-1].nome[j]))
            { //Função que verifica se a letra é a mesma
                j++;
            }
            if(tolower(p[i].nome[j]) < tolower(p[i-1].nome[j])) 
            {
                aux = p[i];
                p[i] = p[i-1];
                p[i-1] = aux;
                swap = 0;
            }
        }
        bottom = bottom + 1;  
    }
 }

int buscarCidade(Pessoa* p, int n)
{
    char nome[100];
    scanf("%[^.]s", nome); //Lê o nome da pessoa para buscar sua cidade
    getchar(); //Consome o .
    getchar(); //Consome o enter
    getchar(); //Consome \r
    for(int i = 0; i < n; i++)
    {
        if ((strcmp(nome, p[i].nome) == 0))
        {
            return (strcmp(p[i].cidade, "Sao Carlos")==0);
        }
    }
    return -1; //Retorna -1 caso não ache o nome da pesssoa
}

//JBMolotov