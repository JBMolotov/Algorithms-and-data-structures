// Johnny Silva
// 11371350

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[100];
    float preco;
} Livro;

//Função de ler nome das pessoas e suas respectivas cidades
void leLivros(Livro* p, int i);

int main(void)
{
    int n, k;
    Livro *l;

    scanf("%d ", &n);
    l = malloc(sizeof(Livro)*n);

    /*for (int i = 0; i < n; i++)
    {
        lerLivros(p, i);
    }*/

    mergeSort3Way(l,n); 

    free(l);

    return 0;
}

void lerLivros(Livro* l, int i)
{
    scanf("%[^,]s", l[i].nome);
    getchar(); //Consome Ponto
    getchar(); //Consome espaço
    scanf("%f", l[i].preco);
    getchar(); //Consome \n
    getchar(); //Consome \r
}

void merge(Livro* Copia, int low, int mid1,  
           int mid2, int high, Livro* livros)  
{  
    int i = low, j = mid1, k = mid2, l = low;  
  
    // choose smaller of the smallest in the three ranges  
    while ((i < mid1) && (j < mid2) && (k < high))  
    {  
        if(Copia[i].preco < Copia[j].preco) 
        { 
            if(Copia[i].preco < Copia[k].preco) 
            { 
                livros[l++] = Copia[i++]; 
            } 
            else
            { 
                livros[l++] = Copia[k++]; 
            } 
        } 
        else
        { 
            if(Copia[j].preco < Copia[k].preco) 
            { 
                livros[l++] = Copia[j++]; 
            } 
            else
            { 
                livros[l++] = Copia[k++]; 
            } 
        } 
    }  
  
    // case where first and second ranges 
    // have remaining values  
    while ((i < mid1) && (j < mid2))  
    {  
        if(Copia[i].preco < Copia[j].preco) 
        { 
            livros[l++] = Copia[i++]; 
        } 
        else
        { 
            livros[l++] = Copia[j++]; 
        } 
    }  
  
    // case where second and third ranges 
    // have remaining values  
    while ((j < mid2) && (k < high))  
    {  
        if(Copia[j].preco < Copia[k].preco) 
        { 
            livros[l++] = Copia[j++]; 
        } 
        else
        { 
            livros[l++] = Copia[k++]; 
        }  
    }  
  
    // case where first and third ranges have  
    // remaining values  
    while ((i < mid1) && (k < high))  
    {  
        if(Copia[i].preco < Copia[k].preco) 
        { 
            livros[l++] = Copia[i++]; 
        } 
        else
        { 
            livros[l++] = Copia[k++]; 
        }  
    }  
  
    // copy remaining values from the first range  
    while (i < mid1)  
        livros[l++] = Copia[i++];  
  
    // copy remaining values from the second range  
    while (j < mid2)  
        livros[l++] = Copia[j++];  
  
    // copy remaining values from the third range  
    while (k < high)  
        livros[l++] = Copia[k++];  
}  
  
  
/* Performing the merge sort algorithm on the  
given array of values in the rangeof indices  
[low, high). low is minimum index, high is  
maximum index (exclusive) */
void mergeSort3WayRec(Livro* Copia, int low, 
                      int high, Livro* livros)  
{  
    // If array size is 1 then do nothing  
    if (high - low < 2)  
        return;  
  
    // Splitting array into 3 parts  
    int mid1 = low + ((high - low) / 3);  
    int mid2 = low + 2 * ((high - low) / 3) + 1;  
  
    // Sorting 3 arrays recursively  
    mergeSort3WayRec(livros, low, mid1, Copia);  
    mergeSort3WayRec(livros, mid1, mid2, Copia);  
    mergeSort3WayRec(livros, mid2, high, Copia);  
  
    // Merging the sorted arrays  
    merge(livros, low, mid1, mid2, high, Copia);  
} 
  
void mergeSort3Way(Livro* livros, int n)  
{  
    // if array size is zero return null  
    if (n == 0)  
        return;  
  
    // creating duplicate of given array  
    Livro* Copia[n];
  
    // copying alements of given array into  
    // duplicate array  
    for (int i = 0; i < n; i++)  
        Copia[i] = livros[i];  
  
    // sort function  
    mergeSort3WayRec(Copia, 0, n, livros);  
  
    // copy back elements of duplicate array  
    // to given array  
    for (int i = 0; i < n; i++)  
        livros[i] = Copia[i];  
}  
//JBMolotov