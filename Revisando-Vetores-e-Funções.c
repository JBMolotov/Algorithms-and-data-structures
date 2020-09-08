#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int lerEntradas(int*);
void ocorrencia(int*, int*, int);
int eliminarOcorrencia(int*, int*, int);
void imprimirResultados(int*, int*, int);

int main ()
{
    int n[100], r[100];  //n -> entradas em vetor, r -> repeticoes em vetor respetivamente ao n
    int i = lerEntradas(n); //i -> numero de itens lidos
    ocorrencia(n, r, i); //calcula as ocorrencias de cada item
    int x = eliminarOcorrencia(n, r, i); //x -> numero atualizado de itens
    imprimirResultados(n, r, x);
    
    return 0;
}

int lerEntradas(int* n)
{
    char str[1000]; //so pra ler a entrada
    int i = 0; //numero de entradas, max 100
    scanf("%[^\n]s", str); 
    char * pch;
    pch = strtok (str, " ");
    while (pch != NULL)
    {   
        n[i] = atoi(pch);
        pch = strtok (NULL, " ");
        i++;
    }
    return i;
}

void ocorrencia(int* n, int* repeats, int i)
{
    for (int j = 0; j < i; j++)
    {
        repeats[j] = 0;
        for (int k = j; k < i; k++)
        {
            if (n[j] == n[k])
            {
                repeats[j]++;
            }    
        }
    }
}

int eliminarOcorrencia(int* n, int* repeats, int i)
{
    int n_aux[100], r_aux[100];
    int x = 0, k = 0;
    for (int j = 0; j < i; j++)
    {
        for (k = 0; k < x; k++)
        {
            if (n[j] == n[k])
            {
               
               break;
            }    
        }

        if (k == x)
        {
            n_aux[x] = n[j];
            r_aux[x] = repeats[j];
            x++;
        }
    }
    n = n_aux;
    repeats = r_aux;
    return x;
}

void imprimirResultados(int* n, int* r, int x)
{
    for(int j = 0; j < x; j++)
    {
        printf ("%d(%d)\n", n[j], r[j]);
    }
}

//Molotov