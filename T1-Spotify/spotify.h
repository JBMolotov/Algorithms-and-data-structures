#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct musica Musica;
typedef struct album Album;
typedef struct artista Artista;
typedef struct lista Lista;

struct musica
{
    char *id, *nome;
    char *release_date, *length, *popularity, *acousticness, *danceability, *energy, *instrumentalness, *liveness, *loudness, *speechiness, *tempo, *time_signature;
    struct musica *prox;
};

struct album
{
    char *id, *nome;
    Musica *ini, *fim;
    struct album *prox;
};

struct artista
{
    char *id, *nome;
    double pop_total, pop_media;
    int n_musicas;
    Album *ini, *fim;
    struct artista *prox, *ant;
};

struct lista
{
    Artista *ini, *fim;
    int n_artistas;
    int n_musicas;
};

Lista* CriaLista();
void ExcluiLista(Lista *l);
void ImprimeLista(Lista *l);


void ExcluiArtista(Artista *a);
void InsereArtista(Lista *l, Artista *art);
Artista* ArtistaExiste(Lista *l, char *id);


void ExcluiAlbum(Album *album);
void InsereAlbum(Artista *art, Album *alb);
Album* AlbumExiste(Artista *a, char *id);

void InsereMusica(Album *album, Musica *m);
void ImprimeMusica(Musica *a);

void Insere(Lista *l, char *track_name, char *track_id, char *album_name, char *album_id, char *artist_name, char *artist_id, char *release_date, char *length, char *popularity, char *acousticness, char *danceability, char *energy, char *instrumentalness, char *liveness, char *loudness, char *speechiness, char *tempo, char *time_signature);

void swap ( Artista* a, Artista* b );
void QuickSort(Lista *l);
void _quickSort(Artista* low, Artista *high);
Artista* partition(Artista *low, Artista *high);