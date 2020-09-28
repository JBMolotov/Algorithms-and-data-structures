#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
 
FILE* AbrirArquivos();
void LerEntradas(FILE*, int*, int*, int*, int*);
char** LerLabirinto(FILE*, int, int, int*, int*);
void FecharArquivo(FILE*);
int PercorrerLabirinto(char**, int, int, int, int);
int Busca(char**, int, int, int, int, int*);
void ImprimirSaida(char**, int, int, int, int);
void LimparLabirinto(char**, int);


int main(int argc, char **argv)
{
    int linhas, colunas;
    int x_inicial, y_inicial;
    int npessoas = 0, caminhos = 0, visitados = 0;

    FILE *fb = AbrirArquivos();
    LerEntradas(fb, &linhas, &colunas, &x_inicial, &y_inicial);
    char** labirinto = LerLabirinto(fb, linhas, colunas, &npessoas, &caminhos);
    FecharArquivo(fb);
    visitados = PercorrerLabirinto(labirinto, x_inicial, y_inicial, linhas, colunas);
    ImprimirSaida(labirinto, linhas, npessoas, caminhos, visitados);
    LimparLabirinto(labirinto, linhas);
    return 0;
}

FILE* AbrirArquivos()
{
    FILE *fb;
    char arquivo[20];
    scanf("%[^\n]s", arquivo);
    
    if ((fb = fopen(arquivo, "r")) == NULL)
    {
        printf("Erro ao abrir o arquivo.");
        // Sair do programa caso retornar NULL
        exit(1);
    }

    return fb;
}

void LerEntradas(FILE* fb, int *linhas, int *colunas, int *x_inicial, int *y_inicial)
{
    fscanf(fb, "%d %d %d %d", linhas, colunas, y_inicial, x_inicial); 

    fgetc(fb); //retirar o \n (enter)      
}

char** LerLabirinto(FILE* fb, int linhas, int colunas, int *npessoas, int *caminhos)
{
    char **labirinto; //Array que irá armazenar o labirinto dinâmicamente

    //Aloca primeiro as linhas, e depois as colunas
    labirinto = malloc(linhas * sizeof(char*));
    for (int i = 0; i < linhas; i++)
        labirinto[i] = malloc((colunas+1) * sizeof(char));


    for(int j = 0; j < linhas; j++)
    {
        fscanf(fb, "%[^\n]s", labirinto[j]);
        fgetc(fb); //retirar o \n (enter)
    }

   for(int i = 0; i < linhas; i++)
    {
        for(int j = 0; j < colunas; j++)
        {
            if(labirinto[i][j] == '#') { *npessoas += 1; }
            else if(labirinto[i][j] == '.') { *caminhos += 1; }
        }
    }

    return labirinto;
}

int PercorrerLabirinto(char** labirinto, int x, int y, int linhas, int colunas)
{
    int visitados = 0;
    labirinto[y][x] = '*'; //marcar o inicio como preenchido
    Busca(labirinto, x, y, linhas-1, colunas-1, &visitados);
    return visitados;
}

int Busca(char** labirinto, int x, int y, int y_final, int x_final, int* visitados)
{
    int tentiva = 0;
    
    if (x == x_final || y == y_final || x == 0 || y == 0)
    {
        labirinto[y][x] = '*'; //marcar o final como preenchido
        *visitados += 1;
        return 1;
    }   
    else
    {
        labirinto[y][x] = '*'; //marcar o caminho como preenchido
        //Ordem de busca (Cima, Direita, Baixo, Esquerda);
        if(labirinto[y-1][x] == '.' && tentiva == 0) 
        { 
            tentiva += Busca(labirinto, x, y-1, y_final, x_final, visitados);
            *visitados += 1;
        } //Cima

        if(labirinto[y][x+1] == '.' && tentiva == 0)
        {
            tentiva += Busca(labirinto, x+1, y, y_final, x_final, visitados);
            *visitados += 1;
        } //Direita

        if(labirinto[y+1][x] == '.' && tentiva == 0)
        { 
            tentiva += Busca(labirinto, x, y+1, y_final, x_final, visitados);
            *visitados += 1;
        } //Baixo

        if(labirinto[y][x-1] == '.' && tentiva == 0) 
        { 
            tentiva += Busca(labirinto, x-1, y, y_final, x_final, visitados);
            *visitados += 1;
        } //Esquerda

        return tentiva; 
    }
}





void ImprimirSaida(char** labirinto, int linhas, int npessoas, int caminhos, int visitados)
{
    double exploracao = (visitados*100)/caminhos;
    for(int i = 0; i < linhas; i++)
    {
        printf("%s\n", labirinto[i]); 
    }

    printf("\nVoce escapou de todos! Ninguem conseguiu te segurar!\n");
    printf("Veja abaixo os detalhes da sua fuga:\n");
    printf("----Pessoas te procurando: %d\n", npessoas);
    printf("----Numero total de caminhos validos:   %d\n", caminhos);
    printf("----Numero total de caminhos visitados: %d\n", visitados);
    printf("----Exploracao total do labirinto: %.1lf%%\n", exploracao);
}

void FecharArquivo(FILE* fb)
{
    fclose(fb);
}

void LimparLabirinto(char** labirinto, int linhas)
{
    //Primeiro limpa as linhas, depois as colunas
    for (int i = 0; i < linhas; i++)
        free(labirinto[i]);
    free(labirinto);
}

//Molotov