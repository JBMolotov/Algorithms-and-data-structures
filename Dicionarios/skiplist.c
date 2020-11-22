#include "skiplist.h"

SkipList* Cria()
{
    SkipList *sk = (SkipList*) malloc(sizeof(SkipList));
    if(sk != NULL)
    {
        sk->nivel = -1;
        //cria cabecalho com a chave -1
        sk->inicio = NovoNo(MAX, NULL, NULL);
    }

    return sk;
}

No* NovoNo(int nivel, char *palavra, char *definicao)
{
    No* novo = malloc(sizeof(No));
    nivel++;
    if(novo != NULL)
    { //Cria novo nó apontando para NULL
        novo->palavra = malloc(50);
        novo->definicao = malloc(140);
        if (palavra != NULL)
        {
            strcpy(novo->palavra, palavra);
            strcpy(novo->definicao, definicao);
        }
        else
        {
            novo->palavra = NULL;
            novo->definicao = NULL;
        }
        
        
        novo->prox = malloc(nivel * sizeof(No*));
        for (int i = 0; i < nivel; i++)
        {
            novo->prox[i] = NULL;
        }
    }
    
    return novo;
}

void Libera(SkipList* sk)
{
    if (sk == NULL)
        return;
    
    No *aux, *atual;

    atual = sk->inicio->prox[0];
    while(atual != NULL)
    {
        aux = atual;
        atual = atual->prox[0];
        free(aux->palavra);
        free(aux->definicao);
        free(aux->prox);
        free(aux);
    }

    free(sk->inicio);
    free(sk);
    sk = NULL;
}

No* Busca(SkipList *sk, char *palavra)
{
    if (sk == NULL)
        return NULL;
    
    No *atual = sk->inicio;
    //Partindo do maior nivel para o menor no enquanto a chave for maior que o no
    for(int i = sk->nivel; i >= 0; i--)
    {
        atual = sk->inicio;
        while(atual->prox[i] != NULL && strcmp(atual->prox[i]->palavra, palavra) != 0)
        {
            //printf("%s %s\n", atual->prox[i]->palavra, atual->prox[i]->definicao);
            atual = atual->prox[i];
        }

        
    }
    //Verifica o nivel 0 onde a palavra deve estar
    atual = atual->prox[0];
    if(atual != NULL && strcmp(atual->palavra, palavra) == 0)
        return atual;
    else
        return NULL;
}

void ImprimeBusca(SkipList *sk, char *palavra)
{
    No *atual = Busca(sk, palavra);
    if(atual == NULL)
    { //Se retornar null não existe a palavra na skiplist
        printf("OPERACAO INVALIDA\n");
        return;
    }
    else
    {
        printf("%s %s\n", atual->palavra, atual->definicao);
    }
}

void Altera(SkipList *sk, char *palavra, char *definicao)
{
    No *atual = Busca(sk, palavra);
    if(atual == NULL)
    { //Se retornar null não existe a palavra na skiplist
        printf("OPERACAO INVALIDA\n");
        return;
    }
    else
    {
        strcpy(atual->definicao, definicao);
    }
}

void Insere(SkipList *sk, char *palavra, char *definicao)
{
    if(sk == NULL)
    {
        printf("OPERACAO INVALIDA\n");
        return;
    }
    
    No *atual = sk->inicio;
    No **aux = malloc((MAX+1) * sizeof(No));

    for(int i = 0; i <= MAX+1; i++)
        aux[i] = NULL;

    for(int i = sk->nivel; i >= 0; i--)
    {
        while(atual->prox[i] != NULL)
            atual = atual->prox[i];
        aux[i] = atual;
    }

    //verificar e inserir no nivel 0
    atual = atual->prox[0];

    if(atual == NULL || strcmp(atual->palavra, palavra) != 0)
    {
        int novo_nivel = random() % MAX;
        No *novo = NovoNo(novo_nivel, palavra, definicao);
        if (novo == NULL)
        {
            free(aux);
            return;
        }

        //Caso o random sorteie um nivel maior do que ja existe na skip
        if(novo_nivel > sk->nivel)
        {
            for(int i = sk->nivel+1; i<= novo_nivel; i++)
                aux[i] = sk->inicio;
            
            sk->nivel = novo_nivel;
        }

        //Insere o no e atualiza os ponteiros
        for(int i = 0; i <= novo_nivel; i++)
        {
            novo->prox[i] = aux[i]->prox[i];
            aux[i]->prox[i] = novo;
        }
        free(aux);
        return;
    }

}

void Remove(SkipList *sk, char *palavra)
{
    if(sk == NULL)
    {
        printf("OPERACAO INVALIDA\n");
        return;
    }

    No *atual = sk->inicio;
    No **aux = malloc((MAX+1)*sizeof(No));

    for(int i = 0; i <= MAX; i++)
        aux[i] = NULL;

    for(int i = sk->nivel; i >= 0; i--)
    {
        atual = sk->inicio;
        while(atual->prox[i] != NULL && strcmp(atual->prox[i]->palavra, palavra) != 0)
            atual = atual->prox[i];
        aux[i] = atual;
    }

    atual = atual->prox[0];
    if(atual != NULL && strcmp(atual->palavra, palavra) == 0)
    {
        for(int i = 0; i <= sk->nivel; i++)
        {
            if(aux[i]->prox[i] != atual)
                break;

            aux[i]->prox[i] = atual->prox[i];
        }

        while(sk->nivel > 0 && sk->inicio->prox[sk->nivel] == NULL)
        sk->nivel--;

        free(atual->prox);
        free(atual);
        free(aux);
        return;
    }

    free(aux);
    printf("OPERACAO INVALIDA\n");    
}

void Imprime(SkipList *sk, char ch)
{
    if (sk == NULL)
    {
        printf("OPERACAO INVALIDA\n");
        return;
    }
    
    No *atual = sk->inicio;
    int qtd = 0;
    while(atual->prox[0] != NULL)
    {
        if(atual->prox[0]->palavra[0] == ch) //Se houver uma palavra com o caracter informado        
        {
            printf("%s %s\n", atual->prox[0]->palavra, atual->prox[0]->definicao);
            qtd = 1;
        }
        atual = atual->prox[0];
    }

    if(!qtd)
        printf("NAO HA PALAVRAS INICIADAS POR %c\n", ch);
}