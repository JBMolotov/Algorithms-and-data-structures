//Johnny Silva 11371350

#include "spotify.h"

FILE* AbrirArquivo();
void LerDados(Lista* spotify, FILE *fb);

int main(void) 
{
    Lista *spotify;
    
    spotify = CriaLista();

    FILE *fb = AbrirArquivo();    

    LerDados(spotify, fb);

    QuickSort(spotify);
    ImprimeLista(spotify);
   
    ExcluiLista(spotify);
    
    return 0;
}

FILE* AbrirArquivo()
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

void LerDados(Lista* spotify, FILE *fb)
{
    char aux[50];
    for (int i = 1; i <= 18; i++)
    {
        fscanf(fb, "%[^;]s", aux);
        getc(fb);
    }

    char track_name[255], track_id[50], album_name[50], album_id[50], artist_name[50], artist_id[50], release_date[50], length[50], popularity[50], acousticness[50], danceability[50], energy[50], instrumentalness[50], liveness[50], loudness[50], speechiness[50], tempo[50], time_signature[50];
    
    int c = getc(fb);
    while(c != EOF)
    {
        for (int i = 1; i <= 18; i++)
        {
           
            switch (i)
            {
            case 1:
                fscanf(fb, "%[^;]s", track_name);
                break;
            case 2:
                fscanf(fb, "%[^;]s", track_id);
                break;
            case 3:
                fscanf(fb, "%[^;]s", album_name);
                break;
            case 4:
                fscanf(fb, "%[^;]s", album_id);
                break;
            case 5:
                fscanf(fb, "%[^;]s", artist_name);
                break;
            case 6:
                fscanf(fb, "%[^;]s", artist_id);
                break;
            case 7:
                fscanf(fb, "%[^;]s", release_date);
                break;
            case 8:
                fscanf(fb, "%[^;]s", length);
                break;
            case 9:
                fscanf(fb, "%[^;]s", popularity);
                break;
            case 10:
                fscanf(fb, "%[^;]s", acousticness);
                break;
            case 11:
                fscanf(fb, "%[^;]s", danceability);
                break;
            case 12:
                fscanf(fb, "%[^;]s", energy);
                break;
            case 13:
                fscanf(fb, "%[^;]s", instrumentalness);
                break;
            case 14:
                fscanf(fb, "%[^;]s", liveness);
                break;
            case 15:
                fscanf(fb, "%[^;]s", loudness);
                break;
            case 16:
                fscanf(fb, "%[^;]s", speechiness);
                break;
            case 17:
                fscanf(fb, "%[^;]s", tempo);
                break;
            case 18:
                fscanf(fb, "%[^;]s", time_signature);
                break;
            default:
                break;
            }
            getc(fb);
            c = getc(fb);
        }
        if(c != EOF)
            Insere(spotify, track_name, track_id, album_name, album_id, artist_name, artist_id, release_date, length, popularity, acousticness, danceability, energy, instrumentalness, liveness, loudness, speechiness, tempo, time_signature);
    }

    fclose(fb);
}

//Molotov