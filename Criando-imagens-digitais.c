#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h>
 
void LerEntradas(int *N, int *x, int *y, int *T);
int** CriarImg(int N);
void CriarArquivo(int** img, int N, char* arquivo);
void ImprimirImg(int** img, int N);
void IniciaBusca(int** img, int l, int c, int N, int T);
void Percorrer(int** img, int l, int c, int N, int T, int p);
void LimparImg(int** img, int N);

int main(int argc, char **argv)
{
    int N, x, y, T;
    LerEntradas(&N, &x, &y, &T);
    srandom(T);
    int** img = CriarImg(N);
    ImprimirImg(img, N);
    CriarArquivo(img, N, "inicial.pgm");
    printf("\n");
    IniciaBusca(img, x, y, N-1, T);
    ImprimirImg(img, N);
    CriarArquivo(img, N, "final.pgm");

    LimparImg(img, N);
    return 0;
}

void CriarArquivo(int** img, int N, char * arquivo)
{
    FILE *fb;
     
    if ((fb = fopen(arquivo, "wt")) == NULL)
    {
        printf("Erro ao criar o arquivo.");
        // Sair do programa caso retornar NULL
        exit(1);
    }
    else
    {
        fprintf(fb, "P2\n%d %d\n", N, N);
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
            {
                fprintf(fb ,"%d\t", img[i][j]);
            }
            fprintf(fb, "\n");
        }
    }
    
    fclose(fb);
}

void LerEntradas(int *N, int *x, int *y, int *T)
{
    scanf("%d %d %d %d", N, x, y, T);     
}

int** CriarImg(int N)
{
    int **img; //Array que irá armazenar a img dinâmicamente

    //Aloca primeiro as linhas, e depois as colunas
    img = malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++)
        img[i] = malloc((N)*sizeof(int));

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            img[i][j] = random() % 256;
        }
    }

    return img;
}

void IniciaBusca(int** img, int l, int c, int N, int T)
{
    int p =  img[l][c];
    
    Percorrer(img, l, c, N, T, p);
}

void Percorrer(int** img, int l, int c, int N, int T, int p)
{
    if(l < 0 || l > N || c < 0 || c > N)
        return;

    img[l][c] = p;

    //Ordem de Percorrer (Cima, Direita, Baixo, Esquerda);
    //Cima
    if (l>0 && p != img[l-1][c] && fabs(p - img[l-1][c]) <= T)
    {
        Percorrer(img, l-1, c, N, T, p);
    }
    
    //Direita
    if (c<N && p != img[l][c+1] && fabs(p - img[l][c+1]) <= T)
    {
        Percorrer(img, l, c+1, N, T, p);
    }

    //Baixo
    if (l<N && p != img[l+1][c] && fabs(p - img[l+1][c]) <= T)
    {
        Percorrer(img, l+1, c, N, T, p);
    }

    //Esquerda
    if (c>0 && p != img[l][c-1] && fabs(p - img[l][c-1]) <= T)
    {
        Percorrer(img, l, c-1, N, T, p);
    } 
}


void ImprimirImg(int** img, int N)
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            printf("%d\t", img[i][j]);
        }
        printf("\n");
    }
}

void LimparImg(int** img, int N)
{
    //Primeiro limpa as linhas, depois as colunas
    for (int i = 0; i < N; i++)
        free(img[i]);
    free(img);
}

//Molotov