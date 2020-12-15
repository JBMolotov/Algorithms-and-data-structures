#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct album
{
    char *id, *nome;
    int n_musicas;
    struct album *prox;
}Album;

typedef struct artista
{
    char *id, *nome;
    int n_musicas;
    struct artista *prox;
}Artista;

typedef struct musica
{
    char *id, *nome;
    char *release_date;
    int length, popularity, time_signature;
    double acousticness, danceability, energy, instrumentalness, liveness, loudness, speechiness, tempo;    
    Album *alb;
    Artista *art;
    struct similar *similaridade;
    struct musica *prox, *ant;
}Musica;

typedef struct similar
{
    Musica *musica;
    double distance;
} Similar;

typedef struct lista
{
    Musica *mus_ini, *mus_fim;
    Artista *art_ini, *art_fim;
    Album *alb_ini, *alb_fim;
    int n_artistas;
    int n_albuns;
    int n_musicas;

    double **dissimilaridade; //matriz de dissimilaridade
}Lista;

Lista* CriaLista();
void ExcluiLista(Lista *l);
void ImprimeLista(Lista *l);
void ExcluiArtista(Artista *a);
void ExcluiAlbum(Album *a);
void ExcluiMusica(Musica *m);

void InsereArtista(Lista *l, Artista *art);
Artista* ArtistaExiste(Lista *l, char *id);

void InsereAlbum(Lista *l, Album *alb);
Album* AlbumExiste(Lista *l, char *id);

void InsereMusica(Lista *l, Musica *m);
void ImprimeMusica(Musica *a);

void Insere(Lista *l, char *track_name, char *track_id, char *album_name, char *album_id, char *artist_name, char *artist_id, char *release_date, char *length, char *popularity, char *acousticness, char *danceability, char *energy, char *instrumentalness, char *liveness, char *loudness, char *speechiness, char *tempo, char *time_signature);

void swap (Musica* a, Musica* b );
void QuickSort(Lista *l);
void _quickSort(Musica* low, Musica *high);
Musica* partition(Musica *low, Musica *high);

double distancia(Musica *m1, Musica *m2);
void CalcDissimilaridade(Lista *l);