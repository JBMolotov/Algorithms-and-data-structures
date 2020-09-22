#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
 
FILE* AbrirArquivo(char*);
void LerEntradas(FILE*);
int Substituir(char *frase, char *erro, char *corrigido);
void FecharArquivo(FILE*);

int main(int argc, char **argv)
{
    FILE *fb = AbrirArquivo(argv[1]);
    LerEntradas(fb);
    FecharArquivo(fb);
    return 0;
}

FILE* AbrirArquivo(char* arquivo)
{
    FILE *fb;

    if ((fb = fopen(arquivo, "r")) == NULL)
    {
        printf("Erro ao abrir o arquivo.");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }
    
    return fb;
}

void LerEntradas(FILE* fb)
{
    char frase[100]; //frase inicial
    char erro[20]; //erro a ser corrigido
    char correcao[20]; //correçã
    
    fscanf(fb, "%[^\n]s", frase); 
    //printf("%s\n", frase);   
    fgetc(fb); //retirar o \n (enter)

    fscanf(fb, "%[^\n]s", erro);     
    //printf("%s\n", erro);
    fgetc(fb);

    fscanf(fb, "%[^\n]s", correcao);   
    //printf("%s\n", correcao);
    int ch = fgetc(fb);

    Substituir(frase, erro, correcao);
    printf("%s\n", frase); 

    if(!(ch == EOF)) //Se não for o final do arquivo, leia as entradas novamente
    {
        LerEntradas(fb);
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

void FecharArquivo(FILE* fb)
{
    fclose(fb);
}

//Molotov