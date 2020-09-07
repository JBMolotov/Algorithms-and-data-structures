#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void ocorrencia(int*, int*, int);

int main ()
{
    char str[1000]; //so pra ler a entrada
    int n[100], repeats[100];
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
    
    ocorrencia(&n, &repeats, i);
    int x = eliminarOcorrencia(&n, &repeats, i);
    
    for(int j = 0; j < x; j++)
    {
        printf ("%d(%d)\n", n[j], repeats[j]);
    }
    return 0;
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
    return repeats;
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