#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[50];
    int id_artista;
} artista;

typedef struct {
    artista *artistas;
    album *albuns;
    musica *musicas;
    int index, id_artista, id_album, id_musica;
} rep_musica;