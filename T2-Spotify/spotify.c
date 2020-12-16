#include "spotify.h"

//Cria uma Lista com elementos vazios
Lista* CriaLista() 
{
    Lista *l;
    l = malloc(sizeof(Lista)); // instancia lista
    
    // define lista vazia
    l->musicas = malloc(TAM * sizeof(Musica*));
    // for (int i = 0; i <= TAM; i++)
    //     l->musicas[i] = malloc(sizeof(Musica*));
    l->art_ini = NULL;
    l->art_fim = NULL;
    l->alb_ini = NULL;
    l->alb_fim = NULL;
    l->n_artistas = 0;
    l->n_artistas = 0;
    l->n_musicas = 0;
    l->dissimilaridade = NULL;
    return l;
}

void ExcluiArtista(Artista *a)
{
    free(a->id);
    free(a->nome);
    free(a);
    a = NULL;
}

void ExcluiAlbum(Album *a)
{
    free(a->id);
    free(a->nome);
    free(a);
    a = NULL;
}

void ExcluiMusica(Musica *m)
{   
    free(m->id);
    free(m->nome);
    free(m->release_date);
    free(m);
    m = NULL;
}

//Entra em cada artista, cada, album e exclui as musicas e volta excluindo tudo
void ExcluiLista(Lista *l) 
{
    // apaga os artistas
    Artista *art_aux;
    while (l->art_ini != NULL) 
    {
        art_aux = l->art_ini;
        l->art_ini = l->art_ini->prox;
        ExcluiArtista(art_aux);
    }

    // apaga os albuns
    Album *alb_aux;
    while (l->alb_ini != NULL) 
    {
        alb_aux = l->alb_ini;
        l->alb_ini = l->alb_ini->prox;
        ExcluiAlbum(alb_aux);
    }

    // apaga as musicas
    //apaga os vetores de similaridade
    for(int i = 0; i <= l->n_musicas; i++) 
    {
        ExcluiMusica(l->musicas[i]);
    }
    
    // apaga lista
    free(l);
    l = NULL;
}

//Imprime os artistas
void ImprimeLista(Lista *l) 
{
    for(int i = 0; i <= l->n_musicas; i++) 
    {
        printf("%d - %s\n", i, l->musicas[i]->id);
    }
}

//Cria um novo artista e instancia dinamicamente
Artista* CriaArtista() 
{
    Artista *a;
    a = malloc(sizeof(Artista)); // instancia artista
    a->id = malloc(30);
    a->nome = malloc(50);
    a->n_musicas = 0;
    return a;
}


//Aloca um novo artista dinamicamente
void InsereArtista(Lista *l, Artista *a)
{
    // cria no
    a->prox = NULL;
    // atualiza ponteiros
    if (l->art_fim != NULL)
        l->art_fim->prox = a;
    l->art_fim = a;
    if (l->art_ini == NULL)
        l->art_ini = a;
    l->n_artistas += 1;
}

//Verifica se um artista já existe na lista, se sim retorna ele, se não, cria novo
Artista* ArtistaExiste(Lista *l, char *id)
{
    Artista *atual = l->art_ini;
    while (atual != NULL)
    {
        if (strcmp(atual->id, id) == 0)
        {
            return atual; // achou, retorna ele
        }
        atual = atual->prox;
    }
    return CriaArtista(); // nao achou, retorna um novo
}

//Cria um novo album instanciando dinamicamente
Album* CriaAlbum() 
{
    Album *a;
    a = malloc(sizeof(Album)); // instancia artista
    a->id = malloc(30);
    a->nome = malloc(255);
    a->n_musicas = 0;
    return a;
}

//Insere um novo album na lista
void InsereAlbum(Lista *l, Album *alb)
{
    // cria no
    alb->prox = NULL;
    // atualiza ponteiros
    if (l->alb_fim != NULL)
        l->alb_fim->prox = alb;
    l->alb_fim = alb;
    if (l->alb_ini == NULL)
        l->alb_ini = alb;
}

//Verifica se um album existe pelo id, se sim retorna ele, se não cria um novo
Album* AlbumExiste(Lista *l, char *id)
{
    Album *atual = l->alb_ini;
    while (atual != NULL) {
        if (strcmp(atual->id, id) == 0)
            return atual; // achou
        atual = atual->prox;
    }
    return CriaAlbum(); // nao achou
}

//Cria uma nova musica e instancia dinamicamente
Musica* CriaMusica() 
{
   
    Musica *m;
    m = malloc(sizeof(Musica)); // instancia musica
    m->id = malloc(30);
    m->nome = malloc(255);
    m->release_date = malloc(12);
    m->alb = NULL;
    m->art = NULL;
    
    return m;
}


//Insere a partir de dados, um novo artista ou um existente, um novo album ou um existente e assim uma nova musica
void Insere(Lista *l, char *track_name, char *track_id, char *album_name, char *album_id, char *artist_name, char *artist_id, char *release_date, char *length, char *popularity, char *acousticness, char *danceability, char *energy, char *instrumentalness, char *liveness, char *loudness, char *speechiness, char *tempo, char *time_signature)
{
    Artista *art = ArtistaExiste(l, artist_id);
    Album *alb = AlbumExiste(l, album_id);
   
    
    if (art->n_musicas == 0) //Se o artista for novo
    {     
        strcpy(art->id, artist_id);
        strcpy(art->nome, artist_name);
        InsereArtista(l, art);
    }

        
    if (alb->n_musicas == 0) //Se o album for novo
    {
        strcpy(alb->id, album_id);
        strcpy(alb->nome, album_name);
        InsereAlbum(l, alb);
    }


    int m = l->n_musicas;
    l->musicas[m] = CriaMusica();

    strcpy(l->musicas[m]->id, track_id);
    strcpy(l->musicas[m]->nome, track_name);
    strcpy(l->musicas[m]->release_date, release_date);
    l->musicas[m]->popularity = atoi(popularity);
    l->musicas[m]->length = atoi(length);
    l->musicas[m]->time_signature = atoi(time_signature);
    l->musicas[m]->instrumentalness = atof(instrumentalness);
    l->musicas[m]->liveness = atof(liveness);
    l->musicas[m]->loudness = atof(loudness);
    l->musicas[m]->speechiness = atof(speechiness);
    l->musicas[m]->tempo = atof(tempo);
    l->musicas[m]->acousticness = atof(acousticness);
    l->musicas[m]->energy = atof(energy);
    l->musicas[m]->art = art;
    l->musicas[m]->alb = alb;


    l->n_musicas += 1;
    art->n_musicas += 1;
    alb->n_musicas += 1;
}

//Troca as informações, para organizar com o QuickSort
void swap (Musica *a, Musica *b ) 
{     
    Musica *tmp = CriaMusica();
    strcpy(tmp->id, a->id);
    strcpy(tmp->nome, a->nome);
    strcpy(tmp->release_date, a->release_date);
    tmp->popularity = a->popularity;
    tmp->length = a->length;
    tmp->time_signature = a->time_signature;
    tmp->instrumentalness = a->instrumentalness;
    tmp->liveness = a->liveness;
    tmp->loudness = a->loudness;
    tmp->speechiness = a->speechiness;
    tmp->tempo = a->tempo;
    tmp->acousticness = a->acousticness;
    tmp->energy = a->energy;
    tmp->danceability = a->danceability;
    tmp->art = a->art;
    tmp->alb = a->alb;

    strcpy(a->id, b->id);
    strcpy(a->nome, b->nome);
    strcpy(a->release_date, b->release_date);
    a->popularity = b->popularity;
    a->length = b->length;
    a->time_signature = b->time_signature;
    a->instrumentalness = b->instrumentalness;
    a->liveness = b->liveness;
    a->loudness = b->loudness;
    a->speechiness = b->speechiness;
    a->tempo = b->tempo;
    a->acousticness = b->acousticness;
    a->energy = b->energy;
    a->danceability = b->danceability;
    a->art = b->art;
    a->alb = b->alb;

    strcpy(b->id, tmp->id);
    strcpy(b->nome, tmp->nome);
    strcpy(b->release_date, tmp->release_date);
    b->popularity = tmp->popularity;
    b->length = tmp->length;
    b->time_signature = tmp->time_signature;
    b->instrumentalness = tmp->instrumentalness;
    b->liveness = tmp->liveness;
    b->loudness = tmp->loudness;
    b->speechiness = tmp->speechiness;
    b->tempo = tmp->tempo;
    b->acousticness = tmp->acousticness;
    b->energy = tmp->energy;
    b->danceability = tmp->danceability;
    b->art = tmp->art;
    b->alb = tmp->alb;

    ExcluiMusica(tmp);
} 

// A função que chama função que organiza recursivamente 
void QuickSort(Lista *l, int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition(l, low, high); 
  
        QuickSort(l, low, pi - 1); 
        QuickSort(l, pi + 1, high); 
    } 
} 

int partition (Lista* l, int low, int high) 
{ 
    char *pivot = l->musicas[high]->id;
    int i = (low - 1); 
  
    for (int j = low; j <= high- 1; j++) 
    { 
        if ( strcmp(l->musicas[j]->id, pivot) < 0) 
        { 
            i++;
            swap(l->musicas[i], l->musicas[j]); 
        } 
    } 
    swap(l->musicas[i + 1], l->musicas[high]); 
    return (i + 1); 
} 


double Distancia(Musica *m1, Musica *m2)
{
    if(m1 == m2)
        return 0;
    double d = 0;
    d += pow(m1->acousticness - m2->acousticness, 2);
    d += pow(m1->danceability - m2->danceability, 2);
    d += pow(m1->energy - m2->energy, 2);
    d += pow(m1->instrumentalness - m2->instrumentalness, 2);
    d += pow(m1->liveness - m2->liveness, 2);
    d += pow(m1->loudness - m2->loudness, 2);
    d += pow(m1->speechiness - m2->speechiness, 2);
    d += pow(m1->tempo - m2->tempo, 2);
    d += pow(m1->time_signature - m2->time_signature, 2);
    d = sqrt(d);
    return d;
}

void CalcDissimilaridade(Lista *l)
{
    l->dissimilaridade = malloc(l->n_musicas * sizeof(Similar));
    

    for (int z = 0; z <= l->n_musicas; z++)
        l->dissimilaridade[z] = malloc(l->n_musicas * sizeof(Similar));

    for (int i = 0; i <= l->n_musicas; i++)
    {   
        for (int j = 0; j <= l->n_musicas; j++)
        {
            l->dissimilaridade[i][j].musica = l->musicas[j];
            l->dissimilaridade[i][j].distance = Distancia(l->musicas[j], l->musicas[i]);       
        }    
    }
}

int buscaBinaria(Lista *l, char *procurado)
{
    int esq = 0, dir = l->n_musicas-1, meio;
    while(esq <= dir)
    {
        meio = (esq+dir)/2;
        if ( strcmp(l->musicas[meio]->id, procurado) == 0)
        {
            return meio;
        }    
        else if( strcmp(l->musicas[meio]->id, procurado) > 0)
        {
            dir = meio-1;
        }
        else
        {
            esq = meio+1;
        }
            
    }
    return -1; //não achou
}

void radixsort(Similar *vet, int n) 
{
	int i, exp = 1, bucket[n];
    int P = 1000000;
    Similar m, temp[n];

    m = vet[0];

	for(i = 0; i < n; i++) 
    {
		if(vet[i].distance > m.distance)
        {
			m = vet[i];
		}
	}

	while(( m.distance/exp ) > 0) 
    {
		for (i = 0; i < n; i++) 
        {
			bucket[i] = 0;
		}

		for(i = 0; i < n; i++)
        {
            int x = ((int)round(vet[i].distance * P / exp)) % 10;
            bucket[x]++;
		}

		for(i = 1; i < n; i++) 
        {
			bucket[i] += bucket[i-1];
		}
		
        for(i = (n - 1); i >= 0; i--)
        {
            int y = ((int)round(vet[i].distance * P / exp)) % 10;
        	temp[--bucket[y]] = vet[i];
		}
		for(i = 0; i < n; i++) {
			vet[i] = temp[i];
		}
		exp *= 10;
	}
}

void ImprimeSimilares(Lista *l, int index, int k)
{
    printf("----As %d musicas mais parecidas com %s sao:\n", k, l->musicas[index]->nome);
    for (int i=0; i<k; i++)
    {
        printf("\t(%d)Artista: %s\n", i, l->dissimilaridade[index][i].musica->art->nome);
        printf("\t\tMusica: %s\n", l->dissimilaridade[index][i].musica->nome);
        printf("\t\tDissimilaridade: %lf\n", l->dissimilaridade[index][i].distance);
        printf("\t\tLink: https://open.spotify.com/track/%s\n", l->dissimilaridade[index][i].musica->id);
    }
    printf("\n");

}