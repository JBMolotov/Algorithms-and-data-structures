#include <stdio.h>
#include "pilha.h"

void Rodada(Pilha* morto, Pilha* descarte, elem* aux, int* seq);
void DescToCompra (Pilha* descarte, Pilha* compra, int n);

int main(void) {
    //n = numero de cartas
    //aux = usado para ler as cartas
    //seq = qual carta deve ser retirada, em sequencia
    //rodadas = quantas rodadas, a primeira é obrigatória
    int n, rodadas = 1, seq = 1;
    elem aux, psy;
    Pilha compra, descarte, morto;
    
    create(&compra);
    create(&descarte);
    create(&morto);
    
    scanf("%d",&n);
    
    for (int i = 0; i < n; i++)
    { //Realiza a primeira rodada lendo os dados inseridos
        scanf("%d",&aux);
        Rodada(&morto, &descarte, &aux, &seq);
    } //terminou de ler a pilha compra
    n = n-(seq - 1); //atualiza o n baseado em quantas cartas foram achadas
    
    //enquanto a descarte não estiver vazia
    while (!top(&descarte, &psy))
    {
        
        int ant_seq = seq;
        DescToCompra(&descarte, &compra, n);
        for (int i = 0; i < n; i++)
        {
            pop(&compra, &aux);
            Rodada(&morto, &descarte, &aux, &seq);
        }
        n = n-(seq - ant_seq); //atualiza o n, so que baseado na sequencia antes da rodada
        rodadas++;
    }
    
    printf("%d\n", rodadas);
    
    return 0;
}

void Rodada(Pilha* morto, Pilha* descarte, elem* aux, int* seq)
{
    if (*aux == *seq)
    { // se igual ao proximo da sequencia, insere na morto
        push(morto, *aux);
        *seq += 1; //somar qual é o novo número a ser procurado
    }
    else
    { //senão insere no descarte
        push(descarte, *aux);
    }
}

//desempilhar a descarte na compra
void DescToCompra (Pilha* descarte, Pilha* compra, int n)
{
    elem aux;
    for(int i = 0; i < n; i++)
    {
        pop(descarte, &aux);
        push(compra, aux);
    }
}
//Molotov