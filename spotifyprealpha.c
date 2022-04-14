#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[50];
    int id, ouvintes;
} Artista;

typedef struct
{
    char titulo[50];
    int id, ano, id_artista, duracao;
    char **generos;
} Album;

typedef struct
{
    char titulo[100];
    char genero[20];
    int id, id_album, duracao, faixa;
} Musica;

typedef struct
{
    Artista *artistas;
    int index, next_id;
} Artistas;

typedef struct
{
    Album *albuns;
    int index, next_id;
} Albuns;

typedef struct
{
    Musica *musicas;
    int index, next_id;
} Musicas;

typedef struct
{
    Artistas artistas;
    Albuns albuns;
    Musicas musicas;
} RepMusica;

void clear();
Artista construtor_artista(char *nome, int id);
Album construtor_album(char *titulo, int ano, int id, int id_artista);
Musica construtor_musica(char *titulo, char *genero, int id, int id_album, int duracao, int faixa);
RepMusica construtor_rep();
void registrar_artista(Artista artista, RepMusica *rep);
int registrar_album(Album album, RepMusica *rep);
int registrar_musica(Musica musica, RepMusica *rep);
void adicionar_generos(Musica musica, RepMusica *rep);
void remover_generos(Musica musica, RepMusica *rep);
int buscar_artista(int id, RepMusica *rep);
int buscar_album(int id, RepMusica *rep);
int buscar_musica(int id, RepMusica *rep);
int atualizar_artista(Artista artista, RepMusica *rep);
int atualizar_album(Album album, RepMusica *rep);
int atualizar_musica(Musica musica, RepMusica *rep);
int remover_artista(int id, RepMusica *rep);
int remover_album(int id, RepMusica *rep);
int remover_musica(int id, RepMusica *rep);

void clear() {
    system("cls||clear");
}

Artista construtor_artista(char *nome, int id)
{
    Artista temp;
    strcpy(temp.nome, nome);
    temp.id = id;
    return temp;
}

Album construtor_album(char *titulo, int ano, int id, int id_artista)
{
    Album temp;
    
    strcpy(temp.titulo, titulo);
    temp.ano = ano;
    
    temp.generos = (char**)malloc(sizeof(char*));

    temp.id = id;
    temp.id_artista = id_artista;
    temp.duracao = 0;
    return temp;
}

Musica construtor_musica(char *titulo, char *genero, int id, int id_album, int duracao, int faixa)
{
    Musica temp;
    strcpy(temp.titulo, titulo);
    strcpy(temp.genero, genero);
    temp.id = id;
    temp.id_album = id_album;
    temp.duracao = duracao;
    temp.faixa = faixa;
    return temp;
}

RepMusica construtor_rep()
{
    RepMusica temp;

    temp.artistas.artistas = (Artista *)malloc(0);
    temp.albuns.albuns = (Album *)malloc(0);
    temp.musicas.musicas = (Musica *)malloc(0);

    temp.artistas.index = temp.albuns.index = temp.musicas.index = 0;
    temp.artistas.next_id = temp.albuns.next_id = temp.musicas.next_id = 1;

    return temp;
}

void registrar_artista(Artista artista, RepMusica *rep)
{
    rep->artistas.artistas = (Artista *)realloc(rep->artistas.artistas, (rep->artistas.index + 1) * sizeof(Artista));

    artista.id = rep->artistas.next_id;
    rep->artistas.artistas[rep->artistas.index] = artista;

    rep->artistas.next_id++;
    rep->artistas.index++;
}

int registrar_album(Album album, RepMusica *rep)
{
    int artista_index = buscar_artista(album.id_artista, rep);
    if (artista_index == -1) {
        return artista_index;
    }
    rep->albuns.albuns = (Album *)realloc(rep->albuns.albuns, (rep->albuns.index + 1) * sizeof(Album));

    album.id = rep->albuns.next_id;
    rep->albuns.albuns[rep->albuns.index] = album;

    rep->albuns.next_id++;
    rep->albuns.index++;

    return rep->albuns.index - 1;
}

int registrar_musica(Musica musica, RepMusica *rep)
{
    int album_index = buscar_album(musica.id_album, rep);
    if (album_index == -1) {
        return album_index;
    }
    rep->musicas.musicas = (Musica *)realloc(rep->musicas.musicas, (rep->musicas.index + 1) * sizeof(Musica));

    musica.id = rep->musicas.next_id;
    rep->musicas.musicas[rep->musicas.index] = musica;

    rep->musicas.next_id++;
    rep->musicas.index++;

    rep->albuns.albuns[album_index].duracao += musica.duracao;
    adicionar_generos(musica, rep);
    return rep->musicas.index - 1;
}

// void adicionar_generos(Musica musica, RepMusica *rep){
//     int indexAlbum = buscar_album(musica.id_album, rep);
//     Album album = rep->albuns.albuns[indexAlbum];
//     if(strstr(album.generos, musica.genero) == NULL){
//         int size = ((sizeof(musica.genero)+sizeof(album.generos))/sizeof(char))+3;
//         rep->albuns.albuns[indexAlbum].generos = (char*) realloc(rep->albuns.albuns[indexAlbum].generos, size);
//         strcat(rep->albuns.albuns[indexAlbum].generos, " / ");
//         strcat(rep->albuns.albuns[indexAlbum].generos, musica.genero);
//     }
// }

// void remover_generos(Musica musica, RepMusica *rep){
//     int i, indexAlbum = buscar_album(musica.id_album, rep);
//     Album album = rep->albuns.albuns[indexAlbum];
//     char *strgenero = strstr(album.generos, musica.genero);
//     if(strgenero != NULL){
//         int tprefix = 0;
//         if(strgenero[-2] == '/'){
//             tprefix = 3;
//         }
//         for (i =-tprefix; i < strlen(musica.genero); i++)
//         {
//             rep->albuns.albuns[indexAlbum].generos[i] = rep->albuns.albuns[indexAlbum].generos[i + strlen(musica.genero) + tprefix];
//         }
//         int size = (-(sizeof(musica.genero)+sizeof(album.generos))/sizeof(char))-tprefix;
//         rep->albuns.albuns[indexAlbum].generos = (char*) realloc(rep->albuns.albuns[indexAlbum].generos, size);
//     }
// }

int buscar_artista(int id, RepMusica *rep)
{
    int i, index = -1;
    for (i = 0; i < rep->artistas.index; i++)
    {
        if (rep->artistas.artistas[i].id == id)
        {
            index = i;
            break;
        }
    }
    return index;
}

int buscar_album(int id, RepMusica *rep)
{
    int i, index = -1;
    for (i = 0; i < rep->albuns.index; i++)
    {
        if (rep->albuns.albuns[i].id == id)
        {
            index = i;
            break;
        }
    }
    return index;
}

int buscar_musica(int id, RepMusica *rep)
{
    int i, index = -1;
    for (i = 0; i < rep->musicas.index; i++)
    {
        if (rep->musicas.musicas[i].id == id)
        {
            index = i;
            break;
        }
    }
    return index;
}

int atualizar_artista(Artista artista, RepMusica *rep) {
    int index = buscar_artista(artista.id, rep);
    if (index == -1) {
        return 0;
    }
    rep->artistas.artistas[index] = artista;
    return 1;
}

int atualizar_album(Album album, RepMusica *rep){
    int index = buscar_album(album.id, rep);
    if(index == -1) {
        return 0;
    }
    rep->albuns.albuns[index] = album;
    return 1;
}

int atualizar_musica(Musica musica, RepMusica *rep){
    int index = buscar_musica(musica.id, rep), album_index = buscar_album(musica.id_album, rep);
    if(index == -1) {
        return 0;
    }
    rep->albuns.albuns[album_index].duracao += musica.duracao - rep->musicas.musicas[index].duracao;
    rep->musicas.musicas[index] = musica;

    return 1;
}

int remover_artista(int id, RepMusica *rep) {
    int i, index = buscar_artista(id, rep);
    if (index == -1) {
        return 0;
    }
    for (i = index; i < rep->artistas.index-1; i++) {
        rep->artistas.artistas[i] = rep->artistas.artistas[i+1];
    }
    rep->artistas.index--;
    rep->artistas.artistas = (Artista*) realloc(rep->artistas.artistas, rep->artistas.index * sizeof(Artista));
    return 1;
}

int remover_album(int id, RepMusica *rep) {
    int i, index = buscar_album(id, rep);
    if (index == -1) {
        return 0;
    }
    for (i = index; i < rep->albuns.index-1; i++) {
        rep->albuns.albuns[i] = rep->albuns.albuns[i+1];
    }
    rep->albuns.index--;
    rep->albuns.albuns = (Album*) realloc(rep->albuns.albuns, rep->albuns.index * sizeof(Album));
    return 1;
}

int remover_musica(int id, RepMusica *rep){
    int i, index = buscar_musica(id, rep);
    int album_index = buscar_album(rep->musicas.musicas[index].id_album, rep);
    if(index == -1) {
        return 0;
    }
    rep->albuns.albuns[album_index].duracao -= rep->musicas.musicas[index].duracao;
    remover_generos(rep->musicas.musicas[index], rep);
    for(i=index; i<rep->musicas.index-1; i++){
        rep->musicas.musicas[i] = rep->musicas.musicas[i+1];
    }
    rep->musicas.index--;
    rep->musicas.musicas = (Musica*) realloc(rep->musicas.musicas, rep->musicas.index * sizeof(Musica));
    return 1;
}

void print_menu(char **menu) {
    int i;
    for (i = 0; i < sizeof(menu)/sizeof(menu[0]); i++) {
        printf("%s\n", menu[i]);
    }
}

int main()
{
    RepMusica repositorio = construtor_rep();
    // char menus[][] = {"1. Gerenciar artistas", "2. Gerenciar albuns", "3. Gerenciar musicas"};
    

    registrar_artista(construtor_artista("JOAO", 0), &repositorio);
    registrar_artista(construtor_artista("JESSIKA", 0), &repositorio);

    registrar_album(construtor_album("BALADONA FODA", 2009, "", 0, 1), &repositorio);
    registrar_album(construtor_album("FESTA JUNINA", 2009, "", 0, 1), &repositorio);

    registrar_musica(construtor_musica("CHORAR D:", "ROCK", 0, 1, 230, 1), &repositorio);
    registrar_musica(construtor_musica("OwO", "ROCK", 0, 1, 230, 2), &repositorio);
    registrar_musica(construtor_musica("EEE", "ASDA", 0, 2, 230, 1), &repositorio);
    registrar_musica(construtor_musica(":O", "LOLOLOL", 0, 2, 230, 2), &repositorio);

    remover_musica(1, &repositorio);

    printf("%s\n", repositorio.artistas.artistas[0].nome);
    printf("%s\n", repositorio.artistas.artistas[1].nome);

    printf("%d\n", repositorio.albuns.albuns[0].ano);
    printf("%d\n", repositorio.albuns.albuns[1].ano);
    printf("%d\n", repositorio.albuns.albuns[0].duracao);
    printf("%d\n", repositorio.albuns.albuns[1].duracao);
    printf("%s\n", repositorio.albuns.albuns[0].generos);
    printf("%s\n", repositorio.albuns.albuns[1].generos);
    printf("%s\n", repositorio.albuns.albuns[0].titulo);
    printf("%s\n", repositorio.albuns.albuns[1].titulo);

    // printf("%d\n", repositorio.musicas.musicas[0].duracao);
    printf("%d\n", repositorio.musicas.musicas[1].duracao);
    // printf("%d\n", repositorio.musicas.musicas[0].faixa);
    printf("%d\n", repositorio.musicas.musicas[1].faixa);
    // printf("%s\n", repositorio.musicas.musicas[0].genero);
    printf("%s\n", repositorio.musicas.musicas[1].genero);
    // printf("%s\n", repositorio.musicas.musicas[0].titulo);
    printf("%s\n", repositorio.musicas.musicas[1].titulo);
}