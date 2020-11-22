#include "skiplist.h"

//ALERT - THIS CODE IS NOT WORKING RIGHT

void Operacao(SkipList *sk);

int main(void) 
{
    SkipList *sk = Cria();
    
    srand(time(NULL));
    
    Operacao(sk);

    Libera(sk);

    return 0; 
}


void Operacao(SkipList *sk)
{
    char *op = malloc(15);
    char ch;
    char *palavra = malloc(15); 
    char *definicao = malloc(15);
    while(!feof(stdin))
    {
        scanf("%s", op);
        getchar();

        if(strcmp(op, "insercao") == 0)
        {
            scanf("%s %[^\n\t]s", palavra, definicao);
            getchar();
            Insere(sk, palavra, definicao);
        } 
        else if(strcmp(op, "alteracao") == 0){
            scanf("%s %[^\n\t]s", palavra, definicao);
            getchar();
            Altera(sk, palavra, definicao);
        }
        else if(strcmp(op, "remocao") == 0){
            scanf("%s", palavra);
            getchar();
            Remove(sk, palavra);
        }
        else if(strcmp(op, "busca") == 0){
            scanf("%s", palavra);
            getchar();
            ImprimeBusca(sk, palavra);
        } 
        else if(strcmp(op, "impressao") == 0){
            scanf("%c", &ch);
            getchar();
            Imprime(sk, ch);
        }

    }
    free(palavra);
    free(definicao);
    free(op);
}

//Molotov