#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

void Criterio(Pessoa p, Fila* f1, Fila* f3, Fila* f2, Fila* f4);
void Saida(Fila* f1, Fila* f3, Fila* f2, Fila* f4);

int main(void) {
    int n;
    char acao[6];
    Fila f1, f2, f3, f4;
    cria(&f1);
    cria(&f2);
    cria(&f3);
    cria(&f4);

    scanf("%d",&n);
    
    for (int i = 0; i < n; i++)
    {
        //getc(); //retirar o \n (enter)
        scanf("%s", acao);

        if(!strcmp(acao, "ENTRA"))
        {
            Pessoa p;
            scanf("%s", p.nome);
            scanf("%d", &p.idade);
            scanf("%d", &p.saude);
            Criterio(p, &f1, &f2, &f3, &f4);
        } 
        else
        {
            Saida(&f1, &f2, &f3, &f4);
        }
        
    }
    
    return 0; 
}

void Criterio(Pessoa p, Fila* f1, Fila* f3, Fila* f2, Fila* f4)
{
    if (p.saude)
        if (p.idade >= 60)
            entra(f1, p);
        else
            entra(f2, p);
    else
        if (p.idade >= 60)
            entra(f3, p);
        else
            entra(f4, p);
}

void Saida(Fila* f1, Fila* f3, Fila* f2, Fila* f4)
{
    Pessoa p;
    if (sai(f1, &p))
        printf("%s %d %d\n", p.nome, p.idade, p.saude);
    else if (sai(f2, &p))
            printf("%s %d %d\n", p.nome, p.idade, p.saude);
        else if (sai(f3, &p))
               printf("%s %d %d\n", p.nome, p.idade, p.saude);
           else if (sai(f4, &p))
                    printf("%s %d %d\n", p.nome, p.idade, p.saude);
                else
                    printf("FILA VAZIA\n");
}

//Molotov
