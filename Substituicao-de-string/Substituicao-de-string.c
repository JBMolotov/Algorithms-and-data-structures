#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
 
void LerEntradas();
int Substituir(char *frase, char *erro, char *corrigido);

int main()
{
    LerEntradas();
    return 0;
}

void LerEntradas()
{
    char frase[100]; //frase inicial
    char erro[20]; //erro a ser corrigido
    char correcao[20]; //correçã
    
    scanf("%[^\n]s", frase); 
    //printf("%s\n", frase);   
    getchar(); //retirar o \n (enter)

    scanf("%[^\n]s", erro);     
    //printf("%s\n", erro);
    getchar(); 

    scanf("%[^\n]s", correcao);   
    //printf("%s\n", correcao);
    int ch =  getchar(); 

    Substituir(frase, erro, correcao);
    printf("%s\n", frase); 

    if(!(ch == EOF)) //Se não for o final do arquivo, leia as entradas novamente
    {
        LerEntradas();
    }
}


int Substituir(char *frase, char *erro,  char *corrigido)
{
   int n_erros;
   char *aux; // auxiliar
   
   //se não achar mais erros, retorna 0
   if ((aux = strstr(frase, erro)) == NULL) 
   {
      return(0);
   }

   n_erros = 1;
   int eLen = strlen(erro);
   int cLen = strlen(corrigido);
   if (eLen > cLen) {
      // mover da direita pra esquerda
      char *fonte = aux + eLen;
      char *destino = aux + cLen;
      while((*destino = *fonte) != '\0') { destino++; fonte++; }
   } else if (eLen < cLen) {
      // mover da esquerda pra direita
      int tLen = strlen(aux) - eLen;
      char *parar = aux + cLen;
      char *fonte = aux + eLen + tLen;
      char *destino = aux + cLen + tLen;
      while(destino >= parar) { *destino = *fonte; destino--; fonte--; }
   }
   memcpy(aux, corrigido, cLen); //copiar a correção para o auxiliar

   n_erros += Substituir(aux + cLen, erro, corrigido); //tenta achar mais erros

   return(n_erros);
}

//Molotov