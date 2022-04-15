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
    char titulo[100];
    int id, ano, id_artista, duracao;
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
Artista construtor_artista(char *nome);
Album construtor_album(char *titulo, int ano, int id_artista);
Musica construtor_musica(char *titulo, char *genero, int id_album, int duracao, int faixa);
RepMusica construtor_rep();
void registrar_artista(Artista artista, RepMusica *rep);
int registrar_album(Album album, RepMusica *rep);
int registrar_musica(Musica musica, RepMusica *rep);
int buscar_artista(int id, RepMusica *rep);
int buscar_album(int id, RepMusica *rep);
int buscar_musica(int id, RepMusica *rep);
int atualizar_artista(Artista artista, RepMusica *rep);
int atualizar_album(Album album, RepMusica *rep);
int atualizar_musica(Musica musica, RepMusica *rep);
int remover_artista(int id, RepMusica *rep);
int remover_album(int id, RepMusica *rep);
int remover_musica(int id, RepMusica *rep);
void exibir_artista(int index, RepMusica *rep);
void exibir_album(int index, RepMusica *rep);
void exibir_musica(int index, RepMusica *rep);
void listar_artistas(int op, char *nome, RepMusica *rep);
void listar_albuns(int op, int id_artista, int ano, char *titulo, RepMusica *rep);
void listar_musicas(int op, char *titulo, int id_artista, int id_album, char *genero, RepMusica *rep);

int main() {
    int h, m, s;
    RepMusica repositorio = construtor_rep();
    char menus[][40] = {"Spotify pre-ALPHA (0.15a)", "1. Gerenciar artistas", "2. Gerenciar albuns", "3. Gerenciar musicas", "4. Sair", "\nDigite a opcao: "};
    char menuCrud[][40] = {"1. Cadastrar", "2. Buscar", "3. Listar", "4. Atualizar", "5. Remover", "6. Cancelar", "\nDigite a opcao: "};
    char menuFiltrarArtista[][40] = {"1. Mostrar todos", "2. Filtrar por nome", "3. Cancelar", "\nDigite a opcao: "};
    char menuFiltrarAlbum[][40] = {"1. Mostrar todos", "2. Filtrar por titulo", "3. Filtrar por ano", "4. Filtrar por artista", "5. Cancelar", "\nDigite a opcao: "};
    char menuFiltrarMusica[][40] = {"1. Mostrar todos", "2. Filtrar por titulo", "3. Filtrar por artista", "4. Filtrar por album", "5. Filtrar por genero", "6. Cancelar", "\nDigite a opcao: "};
    int op, subop, filtrarop, id, index, ano, id_artista, id_album, faixa;
    char nome[50], titulo[100], genero[20];
    Artista artista;
    Album album;
    Musica musica;

    do {
        int i;
        op = 0;
        subop = 0;
        filtrarop = 0;
        clear();
        for (i = 0; i < 6; i++) {
            printf("%s\n", menus[i]);
        }
        scanf("%d", &op);

        if (op >=1 && op <= 3) {
            clear();
            switch (op) {
                case 1:
                    printf("Gerenciamento de artistas\n");
                    break;
                case 2:
                    printf("Gerenciamento de albuns\n");
                    break;
                case 3:
                    printf("Gerenciamento de musicas\n");
                    break;
            }
            for (i = 0; i < 7; i++) {
                printf("%s\n", menuCrud[i]);
            }
            scanf("%d", &subop);
        }
        switch (op) {
            case 1:
                switch (subop) {
                    case 1:
                        printf("Nome: ");
                        scanf(" %[^\n]%*c", nome);
                        registrar_artista(construtor_artista(nome), &repositorio);
                        break;
                    case 2:
                        printf("Id: ");
                        scanf("%d", &id);
                        index = buscar_artista(id, &repositorio);
                        clear();
                        if (index != -1) {
                            exibir_artista(index, &repositorio);
                        } else {
                            printf("Artista nao encontrado!\n");
                        }
                        break;
                    case 3:
                        clear();
                        for (i = 0; i < 4; i++) {
                            printf("%s\n", menuFiltrarArtista[i]);
                        }
                        scanf("%d", &filtrarop);
                        switch (filtrarop) {
                            case 1:
                                listar_artistas(1, NULL, &repositorio);
                                break;
                            case 2:
                                printf("Nome: ");
                                scanf(" %[^\n]%*c", nome);
                                listar_artistas(2, nome, &repositorio);
                                break;
                            case 3:
                                break;
                            default:
                                printf("Operacao invalida\n");
                                break;
                        }
                        break;
                    case 4:
                        printf("Id: ");
                        scanf("%d", &id);
                        index = buscar_artista(id, &repositorio);
                        if (index != -1) {
                            artista = repositorio.artistas.artistas[index];
                            printf("Nome: ");
                            scanf(" %[^\n]%*c", artista.nome);
                            atualizar_artista(artista, &repositorio);
                        } else {
                            printf("Artista nao encontrado!\n");
                        }
                        break;
                    case 5:
                        printf("Id: ");
                        scanf("%d", &id);
                        if (!remover_artista(id, &repositorio)) {
                            printf("Artista nao encontrado!\n");
                        }
                        break;
                    case 6:
                        break;
                    default:
                        printf("Opcao invalida!\n");
                        break;
                }
                break;
            case 2:
                switch (subop) {
                    case 1:
                        printf("Titulo: ");
                        scanf(" %[^\n]%*c", titulo);
                        printf("Ano: ");
                        scanf("%d", &ano);
                        printf("Id do Artista: ");
                        scanf("%d", &id_artista);
                        if (registrar_album(construtor_album(titulo, ano, id_artista), &repositorio) == -1) {
                            printf("Artista invalido\n");
                        }
                        break;
                    case 2:
                        printf("Id: ");
                        scanf("%d", &id);
                        index = buscar_album(id, &repositorio);
                        clear();
                        if (index != -1) {
                            exibir_album(index, &repositorio);
                        } else {
                            printf("Album nao encontrado!\n");
                        }
                        break;
                    case 3:
                        clear();
                        for (i = 0; i < 6; i++) {
                            printf("%s\n", menuFiltrarAlbum[i]);
                        }
                        scanf("%d", &filtrarop);
                        switch (filtrarop) {
                            case 1:
                                listar_albuns(1, 0, 0, NULL, &repositorio);
                                break;
                            case 2:
                                printf("Titulo: ");
                                scanf(" %[^\n]%*c", titulo);
                                listar_albuns(4, 0, 0, titulo, &repositorio);
                                break;
                            case 3:
                                printf("Ano: ");
                                scanf("%d", &ano);
                                listar_albuns(3, 0, ano, "", &repositorio);
                                break;
                            case 4:
                                printf("Id do Artista: ");
                                scanf("%d", &id_artista);
                                listar_albuns(2, id_artista, 0, NULL, &repositorio);
                                break;
                            case 5:
                                break;
                            default:
                                printf("Opcao invalida\n");
                                break;
                        }
                        break;
                    case 4:
                        printf("Id: ");
                        scanf("%d", &id);
                        index = buscar_album(id, &repositorio);
                        if (index != -1) {
                            album = repositorio.albuns.albuns[index];
                            printf("Titulo: ");
                            scanf(" %[^\n]%*c", album.titulo);
                            printf("Ano: ");
                            scanf("%d", &album.ano);
                            printf("Id do Artista: ");
                            scanf("%d", &album.id_artista);
                            atualizar_album(album, &repositorio);
                        } else {
                            printf("Album nao encontrado!\n");
                        }
                        break;
                    case 5:
                        printf("Id: ");
                        scanf("%d", &id);
                        if (!remover_album(id, &repositorio)) {
                            printf("Album nao encontrado!\n");
                        }
                        break;
                    case 6:
                        break;
                    default:
                        printf("Opcao invalida!\n");
                        break;
                }
                break;
            case 3:
                switch (subop) {
                    case 1:
                        printf("Titulo: ");
                        scanf(" %[^\n]%*c", titulo);
                        printf("Genero: ");
                        scanf(" %[^\n]%*c", genero);
                        printf("Duracao (hh:mm:ss): ");
                        scanf("%d:%d:%d", &h, &m, &s);
                        printf("Numero da faixa: ");
                        scanf("%d", &faixa);
                        printf("Id do Album: ");
                        scanf("%d", &id_album);
                        if (registrar_musica(construtor_musica(titulo, genero, id_album, h * 60 * 60 + m * 60 + s, faixa), &repositorio) == -1) {
                            printf("Album invalido\n");
                        }
                        break;
                    case 2:
                        printf("Id: ");
                        scanf("%d", &id);
                        index = buscar_musica(id, &repositorio);
                        clear();
                        if (index != -1) {
                            exibir_musica(index, &repositorio);
                            repositorio.artistas.artistas[buscar_artista(album.id_artista, &repositorio)].ouvintes++;
                        } else {
                            printf("Album nao encontrado!\n");
                        }
                        break;
                    case 3:
                        clear();
                        for (i = 0; i < 7; i++) {
                            printf("%s\n", menuFiltrarMusica[i]);
                        }
                        scanf("%d", &filtrarop);
                        switch (filtrarop) {
                            case 1:
                                listar_musicas(1, "", 0, 0, "", &repositorio);
                                break;
                            case 2:
                                printf("Titulo: ");
                                scanf(" %[^\n]%*c", titulo);
                                listar_musicas(2, titulo, 0, 0, "", &repositorio);
                                break;
                            case 3:
                                printf("Id do artista: ");
                                scanf("%d", id_artista);
                                listar_musicas(3, "", id_artista, 0, "", &repositorio);
                                break;
                            case 4:
                                printf("Id do Album: ");
                                scanf("%d", &id_album);
                                listar_musicas(4, "", 0, id_album, "", &repositorio);
                                break;
                            case 5:
                                printf("Genero: ");
                                scanf(" %[^\n]%*c", genero);
                                listar_musicas(5, "", 0, 0, genero, &repositorio);
                                break;
                            case 6:
                                break;
                            default:
                                break;
                        }
                        break;
                    case 4:
                        printf("Id: ");
                        scanf("%d", &id);
                        index = buscar_musica(id, &repositorio);
                        if (index != -1) {
                            musica = repositorio.musicas.musicas[index];
                            printf("Titulo: ");
                            scanf(" %[^\n]%*c", musica.titulo);
                            printf("Genero: ");
                            scanf(" %[^\n]%*c", musica.genero);
                            printf("Duracao (hh:mm:ss): ");
                            scanf("%d:%d:%d", &h, &m, &s);
                            musica.duracao = h * 60 * 60 + m * 60 + s;
                            printf("Numero da faixa: ");
                            scanf("%d", &musica.faixa);
                            atualizar_musica(musica, &repositorio);
                        } else {
                            printf("Album nao encontrado!\n");
                        }
                        break;
                    case 5:
                        printf("Id: ");
                        scanf("%d", &id);
                        if (!remover_musica(id, &repositorio)) {
                            printf("Album nao encontrado!\n");
                        }
                        break;
                    case 6:
                        break;
                    default:
                        printf("Opcao invalida!\n");
                        break;
                }
                break;
            case 4:
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
        system("pause");
    } while (op != 4);

    return 0;
}

void clear() {
    system("cls||clear");
}

Artista construtor_artista(char *nome) {
    Artista temp;
    strcpy(temp.nome, nome);
    temp.ouvintes = 0;
    return temp;
}

Album construtor_album(char *titulo, int ano, int id_artista) {
    Album temp;

    strcpy(temp.titulo, titulo);
    temp.ano = ano;

    temp.id_artista = id_artista;
    temp.duracao = 0;
    return temp;
}

Musica construtor_musica(char *titulo, char *genero, int id_album, int duracao, int faixa) {
    Musica temp;
    strcpy(temp.titulo, titulo);
    strcpy(temp.genero, genero);
    temp.id_album = id_album;
    temp.duracao = duracao;
    temp.faixa = faixa;
    return temp;
}

RepMusica construtor_rep() {
    RepMusica temp;

    temp.artistas.artistas = (Artista *)malloc(0);
    temp.albuns.albuns = (Album *)malloc(0);
    temp.musicas.musicas = (Musica *)malloc(0);

    temp.artistas.index = temp.albuns.index = temp.musicas.index = 0;
    temp.artistas.next_id = temp.albuns.next_id = temp.musicas.next_id = 1;

    return temp;
}

void registrar_artista(Artista artista, RepMusica *rep) {
    rep->artistas.artistas = (Artista *)realloc(rep->artistas.artistas, (rep->artistas.index + 1) * sizeof(Artista));

    artista.id = rep->artistas.next_id;
    rep->artistas.artistas[rep->artistas.index] = artista;

    rep->artistas.next_id++;
    rep->artistas.index++;
}

int registrar_album(Album album, RepMusica *rep) {
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

int registrar_musica(Musica musica, RepMusica *rep) {
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
    return rep->musicas.index - 1;
}

int buscar_artista(int id, RepMusica *rep) {
    int i, index = -1;
    for (i = 0; i < rep->artistas.index; i++) {
        if (rep->artistas.artistas[i].id == id) {
            index = i;
            break;
        }
    }
    return index;
}

int buscar_album(int id, RepMusica *rep) {
    int i, index = -1;
    for (i = 0; i < rep->albuns.index; i++) {
        if (rep->albuns.albuns[i].id == id) {
            index = i;
            break;
        }
    }
    return index;
}

int buscar_musica(int id, RepMusica *rep) {
    int i, index = -1;
    for (i = 0; i < rep->musicas.index; i++) {
        if (rep->musicas.musicas[i].id == id) {
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

int atualizar_album(Album album, RepMusica *rep) {
    int index = buscar_album(album.id, rep);
    if (index == -1) {
        return 0;
    }
    rep->albuns.albuns[index] = album;
    return 1;
}

int atualizar_musica(Musica musica, RepMusica *rep) {
    int index = buscar_musica(musica.id, rep), album_index = buscar_album(musica.id_album, rep);
    if (index == -1) {
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
    for (i = index; i < rep->artistas.index - 1; i++) {
        rep->artistas.artistas[i] = rep->artistas.artistas[i + 1];
    }
    rep->artistas.index--;
    rep->artistas.artistas = (Artista *)realloc(rep->artistas.artistas, rep->artistas.index * sizeof(Artista));
    return 1;
}

int remover_album(int id, RepMusica *rep) {
    int i, index = buscar_album(id, rep);
    if (index == -1) {
        return 0;
    }
    for (i = index; i < rep->albuns.index - 1; i++) {
        rep->albuns.albuns[i] = rep->albuns.albuns[i + 1];
    }
    rep->albuns.index--;
    rep->albuns.albuns = (Album *)realloc(rep->albuns.albuns, rep->albuns.index * sizeof(Album));
    return 1;
}

int remover_musica(int id, RepMusica *rep) {
    int i, index = buscar_musica(id, rep);
    int album_index = buscar_album(rep->musicas.musicas[index].id_album, rep);
    if (index == -1) {
        return 0;
    }
    rep->albuns.albuns[album_index].duracao -= rep->musicas.musicas[index].duracao;
    for (i = index; i < rep->musicas.index - 1; i++) {
        rep->musicas.musicas[i] = rep->musicas.musicas[i + 1];
    }
    rep->musicas.index--;
    rep->musicas.musicas = (Musica *)realloc(rep->musicas.musicas, rep->musicas.index * sizeof(Musica));
    return 1;
}

void exibir_artista(int index, RepMusica *rep) {
    Artista artista = rep->artistas.artistas[index];
    printf("Id: %d\n", artista.id);
    printf("Nome: %s\n", artista.nome);
    printf("Ouvintes: %d\n", artista.ouvintes);
}

void exibir_album(int index, RepMusica *rep) {
    int h, m, s;
    Album album = rep->albuns.albuns[index];
    printf("Id: %d\n", album.id);
    printf("Titulo: %s\n", album.titulo);
    printf("Ano: %d\n", album.ano);
    h = album.duracao / 3600;
    m = (album.duracao - h * 3600) / 60;
    s = album.duracao - h * 3600 - m * 60;
    printf("Duracao: %d:%d:%d\n", h, m, s);
    printf("Artista: %s\n", rep->artistas.artistas[buscar_artista(album.id_artista, rep)].nome);
}

void exibir_musica(int index, RepMusica *rep) {
    int h, m, s;
    Musica musica = rep->musicas.musicas[index];
    Album album = rep->albuns.albuns[buscar_album(musica.id_album, rep)];
    printf("Id: %d\n", musica.id);
    printf("Titulo: %s\n", musica.titulo);
    printf("Genero: %s\n", musica.genero);
    h = musica.duracao / 3600;
    m = (musica.duracao - h * 3600) / 60;
    s = musica.duracao - h * 3600 - m * 60;
    printf("Duracao: %d:%d:%d\n", h, m, s);
    printf("Numero da faixa: %d\n", musica.faixa);
    printf("Album: %s\n", album.titulo);
    printf("Artista: %s\n", rep->artistas.artistas[buscar_album(album.id_artista, rep)].nome);
}

void listar_artistas(int op, char *nome, RepMusica *rep) {
    int i;
    printf("---Artistas---\n");
    for (i = 0; i < rep->artistas.index; i++) {
        switch (op) {
            case 1:
                exibir_artista(i, rep);
                printf("-----------\n");
                break;
            case 2:
                if (strstr(rep->artistas.artistas[i].nome, nome) != NULL) {
                    exibir_artista(i, rep);
                    printf("-----------\n");
                }
                break;
        }
    }
}

void listar_albuns(int op, int id_artista, int ano, char *titulo, RepMusica *rep) {
    int i;
    printf("---Albuns---\n");
    for (i = 0; i < rep->albuns.index; i++) {
        switch (op) {
            case 1:
                exibir_album(i, rep);
                printf("-----------\n");
                break;
            case 2:
                if (strstr(rep->albuns.albuns[i].titulo, titulo) != NULL) {
                    exibir_album(i, rep);
                    printf("-----------\n");
                }
                break;
            case 3:
                if (rep->albuns.albuns[i].ano == ano) {
                    exibir_album(i, rep);
                    printf("-----------\n");
                }
                break;
            case 4:
                if (rep->albuns.albuns[i].id_artista == id_artista) {
                    exibir_album(i, rep);
                    printf("-----------\n");
                }
                break;
        }
    }
}

void listar_musicas(int op, char *titulo, int id_artista, int id_album, char *genero, RepMusica *rep) {
    int i, indexalbum = 0;
    printf("---Musicas---\n");
    for (i = 0; i < rep->musicas.index; i++) {
        switch (op) {
            case 1:
                exibir_musica(i, rep);
                printf("--------------\n");
                break;
            case 2:
                if (strstr(rep->musicas.musicas[i].titulo, titulo) != NULL) {
                    exibir_musica(i, rep);
                    printf("--------------\n");
                }
                break;
            case 3:
                if (buscar_artista(id_artista, rep) != -1) {
                    indexalbum = buscar_album(rep->musicas.musicas[i].id_album, rep);
                    if (rep->albuns.albuns[indexalbum].id_artista == id_artista) {
                        exibir_musica(i, rep);
                        printf("--------------\n");
                    }
                } else {
                    printf("Artista nao encontrado!");
                }
                break;
            case 4:
                indexalbum = buscar_album(id_album, rep);
                if (indexalbum != -1) {
                    if (rep->musicas.musicas[i].id_album == id_album) {
                        exibir_musica(i, rep);
                        printf("--------------\n");
                    }
                } else {
                    printf("Album nao encontrado!");
                }
                break;
            case 5:
                if (strstr(rep->musicas.musicas[i].genero, genero) != NULL) {
                    exibir_musica(i, rep);
                    printf("--------------\n");
                }
                break;
        }
    }
}