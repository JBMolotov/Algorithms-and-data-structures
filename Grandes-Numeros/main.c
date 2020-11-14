//Johnny Silva - 11371350

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

void LerNumeros(Lista *num1, Lista *num2);
void Operacao(char *op, Lista *num1, Lista *num2);

int main(void) {
    Lista *num1, *num2;
    int n;
    char op[4];
    num1 = Cria();
    num2 = Cria();

    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%s", op);
        getchar(); //Elimina enter
        LerNumeros(num1, num2);
        printf("Resultado %d: ", i);
        Operacao(op, num1, num2);
        num1 = Limpa(num1); //Limpa as listas, para serem usadas novamente
        num2 = Limpa(num2);
    }

    Destroi(num1);
    Destroi(num2);
    return 0;
}

void LerNumeros(Lista *num1, Lista *num2)
{
    //Ler cada char, se achar sinal de negativo, muda o sinal na lista
    char x[255], y[255];
    scanf("%[^ ]s", x);
    getchar();
    scanf("%[^\n]s", y);
    for(int i = 0; i < strlen(x); i++)
    {        
         if (x[i] == '-')
            Negativar(num1);
        else
            InsereFim(num1, (int)x[i] - 48); //Subtrai o 48 no codigo ascii
    }
    for(int i = 0; i < strlen(y); i++)
    {        
        if (y[i] == '-')
            Negativar(num2);
        else
            InsereFim(num2, (int)y[i] - 48);
    }
}

void Operacao(char *op, Lista *num1, Lista *num2)
{
    if (strcmp(op, "sum")==0)
        Imprime( Soma(num1, num2) );
    else if(strcmp(op, "big")==0)
        printf("%d\n",  Maior(num1, num2));    
    else if(strcmp(op, "sml")==0)
        printf("%d\n", Maior(num2, num1));
    else
        printf("%d\n", Igual(num1, num2));
}

//Molotov