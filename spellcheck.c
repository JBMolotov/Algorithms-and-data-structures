//Johnny Silva 11371350

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM 1000000

typedef struct texto 
{
    int total;
    char **palavra;
} Texto;

Texto* criaTexto();
void excluiTexto(Texto *dic);
FILE* abriArquivo();
void lerLivro (Texto *dic);
void lerTweet (Texto *twt);
void imprimirLivro(Texto *dic);
void quickSort(Texto *dic, int low, int high);
Texto* eliminaRepeticao(Texto *dic);
void compararPalavras(Texto *dic, Texto *twt);

int main(void) 
{
    Texto *dic = criaTexto(); //Dicionario de palavras
    Texto *twt = criaTexto(); //Tweets
    
    lerLivro(dic);
    lerTweet(twt);

    quickSort(dic, 0, dic->total-1);
    dic = eliminaRepeticao(dic);
    
    compararPalavras(dic, twt);

    excluiTexto(dic);
    excluiTexto(twt);
    return 0; 
}

Texto* criaTexto()
{
    Texto *dic;
    dic = malloc(sizeof(Texto));
    dic->palavra = malloc(TAM);
    dic->total = 0;
    return dic;
} 

void excluiTexto(Texto *dic)
{
    for (int i = 0; i < dic->total; i++) free(dic->palavra[i]);
    free(dic->palavra);
    free(dic);
}

FILE* abriArquivo()
{
    FILE *fb;
    char arquivo[20];
    scanf("%s", arquivo);
    
    if ((fb = fopen(arquivo, "r")) == NULL)
    {
        printf("Erro ao abrir o arquivo.");
        // Sair do programa caso retornar NULL
        exit(1);
    }

    return fb;
}

void lerLivro (Texto *dic)
{
    FILE *livro = abriArquivo();
    char *palavra = malloc(45);
    int status;
    while((status = fscanf(livro, "%s", palavra)) != EOF)
    {
        dic->palavra[dic->total] = malloc(45);
        char *token = strtok(palavra, " ’“”_][\r\t1234567890\n\"\'$%():/.,!?&;@-,# ");
        if (token != NULL)
        {
            strcpy(dic->palavra[dic->total], token); //Insere no vetor
            //passar para minuscula
            for(int i = 0; dic->palavra[dic->total][i]; i++)
                dic->palavra[dic->total][i] = tolower(dic->palavra[dic->total][i]);
            dic->total += 1;   
        }
    }

    free(palavra);
    fclose(livro);
}

void imprimirLivro(Texto *dic)
{
    for(int i = 0; i < dic->total; i++)
    {
        printf("%s ", dic->palavra[i]);
    }
    printf("\n");
}

// A utility function to swap two elements 
void swap(char *a, char *b) 
{ 
    char *t = malloc(45);
    strcpy(t, a);
    strcpy(a, b); 
    strcpy(b, t);
    free(t);
} 
  
int partition (Texto *dic, int low, int high) 
{ 
    char *pivot = malloc(45);
    strcpy(pivot, dic->palavra[high]);

    int i = (low - 1);
   
    for (int j = low; j <= high- 1; j++) 
    { 
        if (strcmp(dic->palavra[j], pivot) < 0) 
        { 
            i++;
            swap(dic->palavra[i], dic->palavra[j]); 
        } 
    } 
    swap(dic->palavra[i + 1], dic->palavra[high]); 
    free(pivot);
    return (i + 1); 
} 
  
void quickSort(Texto *dic, int low, int high) 
{ 
    
    if (low < high) 
    { 
        int pi = partition(dic, low, high); 
        quickSort(dic, low, pi - 1); 
        quickSort(dic, pi + 1, high); 
    } 
} 
  
Texto* eliminaRepeticao(Texto *dic)
{
    Texto *novo = criaTexto();

    char *old = malloc(45);

    strcpy(old, dic->palavra[0]); //pega a primeira palavra
    novo->palavra[0] = malloc(45);
    strcpy(novo->palavra[0], dic->palavra[0]); //adiociona ao novo texto
    
    novo->total += 1; //será o numero do vetor sem repeticao
    for(int i = 1; i < dic->total; i++)
    {
        if ( strcmp(old, dic->palavra[i]) != 0)
        {
            novo->palavra[novo->total] = malloc(45);
            strcpy(novo->palavra[novo->total], dic->palavra[i]);
            strcpy(old, novo->palavra[novo->total]);
            novo->total += 1;
        }
    }

    excluiTexto(dic);

    return novo;
}

void lerTweet (Texto *twt)
{
    FILE *tweet = abriArquivo();
    char *palavra = malloc(255);
    
    int status;
    
    while((status = fscanf(tweet, "%s", palavra)) != EOF)
    {
        if ( strcmp(palavra, "\"text\":") == 0 )
        {
            getc(tweet);
            getc(tweet);
            while(strcmp(palavra, "truncated") != 0)
            {
                fscanf(tweet, "%s", palavra);
                char* token = strtok(palavra, " ’“”_][\r\t1234567890…\"\'\n\\$*%():/.,!?&;@-,#");
                if (token != NULL)
                {
                    strcpy(palavra, token);
                    if (strcmp(palavra, "truncated") != 0 )
                    {
                        twt->palavra[twt->total] = malloc(45);
                        strcpy(twt->palavra[twt->total], token); //Insere no vetor
                        twt->total += 1;
                    }
                }
                
            }

            twt->palavra[twt->total] = malloc(45);
            strcpy(twt->palavra[twt->total], "\n"); //Insere no vetor para saber que o tweet terminou
            twt->total += 1;
        }    
    }

    free(palavra);
    fclose(tweet);
}

int buscaBinaria(Texto *dic, char *procurado)
{
    char* aux = malloc(45);
    strcpy(aux, procurado);
    for(int i = 0; aux[i]; i++)
        aux[i] = tolower(aux[i]);
    int esq = 0, dir = dic->total-1, meio;
    while(esq <= dir)
    {
        meio = (esq+dir)/2;
        if ( strcmp(dic->palavra[meio], aux) == 0)
        {
            free(aux);
            return 1;
        }    
        else if(  strcmp(dic->palavra[meio], aux) > 0)
        {
            dir = meio-1;
        }
        else
        {
            esq = meio+1;
        }
            
    }
    free(aux);
    return 0;
}

void compararPalavras(Texto *dic, Texto *twt)
{
    if (twt->total == 0) //Não achou twitters
    {
        printf("No tweets to check\n");
        return;
    }

    for( int i = 0; i < twt->total-1; i++)
    {
        if (!buscaBinaria(dic, twt->palavra[i]))
        {
            printf("%s ", twt->palavra[i]); 
        }
    }

}

//JBMolotov