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
    
    for(int j = 0; j < i; j++)
    {
        printf ("%d\n", repeats[j]);
    }
    return 0;
}

void ocorrencia(int* n, int* repeats, int i)
{
    for (int j = 0; j < i; j++)
    {
        repeats[j] = 0;
        for (int k = 0; k < i; k++)
        {
            if (n[j] == n[k])
            {
                repeats[j]++;
                n[k] = NULL;
            }    
        }
    }
    return repeats;
}