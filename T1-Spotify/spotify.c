#include "spotify.h"

//Cria uma Lista com elementos vazios
Lista* CriaLista() 
{
    Lista *l;
    l = malloc(sizeof(Lista)); // instancia lista
    // define lista vazia
    l->ini = NULL;
    l->fim = NULL;
    l->n_artistas = 0;
    l->n_musicas = 0;
    return l;
}

//Entra em cada artista, cada, album e exclui as musicas e volta excluindo tudo
void ExcluiLista(Lista *l) 
{
    // apaga os artistas
    Artista *aux;
    while (l->ini != NULL) 
    {
        aux = l->ini;
        l->ini = l->ini->prox;
        ExcluiArtista(aux);
    }
    // apaga lista
    free(l);
    l = NULL;
}

//Imprime os artistas
void ImprimeLista(Lista *l) 
{
    Artista *aux = l->ini;
    int i = 1;

    printf("O Dataset contem %d Artistas e %d Musicas\n", l->n_artistas, l->n_musicas);
    printf("Os artistas mais populares sao:\n");

    while (aux != NULL) {
        printf("(%d) Artista: %s, Musicas: %d musicas, Popularidade: %.2lf, Link: https://open.spotify.com/artist/%s\n", i, aux->nome, aux->n_musicas, aux->pop_media, aux->id);
        i++;
        aux = aux->prox;
    }
}

//Cria um novo artista e instancia dinamicamente
Artista* CriaArtista() 
{
    Artista *a;
    a = malloc(sizeof(Artista)); // instancia artista
    a->id = malloc(30);
    a->nome = malloc(50);
    a->pop_total = 0;
    a->n_musicas = 0;
    // define artista vazio
    a->ini = NULL;
    a->fim = NULL;
    return a;
}

//Entra em cada album e exclui todas as musicas, depois exclui os artistas
void ExcluiArtista(Artista *a) 
{
    // apaga os albums
    Album *aux;
    while (a->ini != NULL) {
        aux = a->ini;
        a->ini = a->ini->prox;
        ExcluiAlbum(aux);
    }
    // apaga artista
    free(a);
    a = NULL;
}

//Aloca um novo artista dinamicamente
void InsereArtista(Lista *l, Artista *a)
{
    // cria no
    a->prox = NULL;
    a->ant = l->fim;
    // atualiza ponteiros
    if (l->fim != NULL)
        l->fim->prox = a;
    l->fim = a;
    if (l->ini == NULL)
        l->ini = a;
    l->n_artistas += 1;
}

//Verifica se um artista já existe na lista, se sim retorna ele, se não, cria novo
Artista* ArtistaExiste(Lista *l, char *id)
{
    Artista *atual = l->ini;
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
    a->nome = malloc(50);
    // define artista vazio
    a->ini = NULL;
    a->fim = NULL;
    return a;
}

//Exclui todas as musicas do album, logo depois exclui o album
void ExcluiAlbum(Album *a) 
{
    // apaga as musicas
    Musica *aux;
    while (a->ini != NULL) {
        aux = a->ini;
        a->ini = a->ini->prox;
        free(aux);
    }
    // apaga album
    free(a);
    a = NULL;
}

//Insere um novo album no artista
void InsereAlbum(Artista *art, Album *alb)
{
    // cria no
    alb->prox = NULL;
    // atualiza ponteiros
    if (art->fim != NULL)
        art->fim->prox = alb;
    art->fim = alb;
    if (art->ini == NULL)
        art->ini = alb;
}

//Verifica se um album existe pelo id, se sim retorna ele, se não cria um novo
Album* AlbumExiste(Artista *a, char *id)
{
    Album *atual = a->ini;
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
    m->nome = malloc(50);
    m->instrumentalness = malloc(30);
    m->length = malloc(30);
    m->liveness = malloc(30);
    m->loudness = malloc(30);
    m->popularity = malloc(30);
    m->release_date = malloc(30);
    m->speechiness = malloc(30);
    m->tempo = malloc(30);
    m->time_signature = malloc(30);
    m->prox = NULL;

    return m;
}

//Insere musica no album
void InsereMusica(Album *a, Musica *m)
{
    // atualiza ponteiros
    if (a->fim != NULL)
        a->fim->prox = m;
    a->fim = m;
    if (a->ini == NULL)
        a->ini = m;
}

//Insere a partir de dados, um novo artista ou um existente, um novo album ou um existente e assim uma nova musica
void Insere(Lista *l, char *track_name, char *track_id, char *album_name, char *album_id, char *artist_name, char *artist_id, char *release_date, char *length, char *popularity, char *acousticness, char *danceability, char *energy, char *instrumentalness, char *liveness, char *loudness, char *speechiness, char *tempo, char *time_signature)
{
    Artista *art = ArtistaExiste(l, artist_id);
    Album *alb = AlbumExiste(art, album_id);
   

    if (art->ini == NULL) //Se o artista for novo
    {     
        strcpy(art->id, artist_id);
        strcpy(art->nome, artist_name);
        InsereArtista(l, art);   
    }
        
    if (alb->ini == NULL) //Se o album for novo
    {
        strcpy(alb->id, artist_id);
        strcpy(alb->nome, artist_name);
        InsereAlbum(art, alb);
    }


    Musica *m = CriaMusica();
    strcpy(m->id, track_id);
    strcpy(m->instrumentalness, instrumentalness);
    strcpy(m->length, length);
    strcpy(m->liveness, liveness);
    strcpy(m->loudness, loudness);
    strcpy(m->nome, track_name);
    strcpy(m->popularity, popularity);
    strcpy(m->release_date, release_date);
    strcpy(m->speechiness, speechiness);
    strcpy(m->tempo, tempo);
    strcpy(m->time_signature, time_signature);
 
    l->n_musicas += 1;
    art->n_musicas += 1;
    InsereMusica(alb, m);
    
    //ajusta popularidade do artista
    art->pop_total += atof(m->popularity);
    art->pop_media = (art->pop_total/art->n_musicas);
     
}

//Troca as informações, para organizar com o QuickSort
void swap ( Artista* a, Artista* b ) 
{     
    char *aux_id = a->id, *aux_nome = a->nome;
    double aux_pop_total = a->pop_total;
    double aux_pop_media = a->pop_media;
    int aux_n_musicas = a->n_musicas;
    Album *aux_ini = a->ini, *aux_fim = a->fim;

    a->id = b->id;
    a->nome = b->nome;
    a->pop_total = b->pop_total;
    a->pop_media = b->pop_media;
    a->n_musicas = b->n_musicas;
    a->ini = b->ini;
    a->fim = b->fim;

    b->id = aux_id;
    b->nome = aux_nome;
    b->pop_total = aux_pop_total;
    b->pop_media = aux_pop_media;
    b->n_musicas = aux_n_musicas;
    b->ini = aux_ini;
    b->fim = aux_fim;

} 

// A função que chama função que organiza recursivamente 
void QuickSort(Lista *l) 
{ 
    // Chama a função QuickSort recursiva
    _quickSort(l->ini, l->fim); 
} 
  
void _quickSort(Artista* low, Artista *high) 
{ 
    if (high != NULL && low != high && low != high->prox) 
    { 
        Artista *p = partition(low, high); 
        _quickSort(low, p->ant); 
        _quickSort(p->prox, high); 
    } 
}

Artista* partition(Artista *low, Artista *high) 
{ 
 
    double x = high->pop_media; 
  
    Artista *i = low->ant; 
   
    for (Artista *j = low; j != high; j = j->prox) 
    { 
        if (j->pop_media >= x) 
        { 
            i = (i == NULL) ? low : i->prox; 
  
            swap(i, j); 
        } 
    } 
    i = (i == NULL) ? low : i->prox;
    swap( i, high); 
    return i; 
}   