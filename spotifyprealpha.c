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
Artista construtor_artista(char *nome, int id);
Album construtor_album(char *titulo, int ano, int id, int id_artista);
Musica construtor_musica(char *titulo, char *genero, int id, int id_album, int duracao, int faixa);
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

void clear()
{
    system("cls||clear");
}

Artista construtor_artista(char *nome, int id)
{
    Artista temp;
    strcpy(temp.nome, nome);
    temp.id = id;
    temp.ouvintes = 0;
    return temp;
}

Album construtor_album(char *titulo, int ano, int id, int id_artista)
{
    Album temp;

    strcpy(temp.titulo, titulo);
    temp.ano = ano;

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
    if (artista_index == -1)
    {
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
    if (album_index == -1)
    {
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

int atualizar_artista(Artista artista, RepMusica *rep)
{
    int index = buscar_artista(artista.id, rep);
    if (index == -1)
    {
        return 0;
    }
    rep->artistas.artistas[index] = artista;
    return 1;
}

int atualizar_album(Album album, RepMusica *rep)
{
    int index = buscar_album(album.id, rep);
    if (index == -1)
    {
        return 0;
    }
    rep->albuns.albuns[index] = album;
    return 1;
}

int atualizar_musica(Musica musica, RepMusica *rep)
{
    int index = buscar_musica(musica.id, rep), album_index = buscar_album(musica.id_album, rep);
    if (index == -1)
    {
        return 0;
    }
    rep->albuns.albuns[album_index].duracao += musica.duracao - rep->musicas.musicas[index].duracao;
    rep->musicas.musicas[index] = musica;

    return 1;
}

int remover_artista(int id, RepMusica *rep)
{
    int i, index = buscar_artista(id, rep);
    if (index == -1)
    {
        return 0;
    }
    for (i = index; i < rep->artistas.index - 1; i++)
    {
        rep->artistas.artistas[i] = rep->artistas.artistas[i + 1];
    }
    rep->artistas.index--;
    rep->artistas.artistas = (Artista *)realloc(rep->artistas.artistas, rep->artistas.index * sizeof(Artista));
    return 1;
}

int remover_album(int id, RepMusica *rep)
{
    int i, index = buscar_album(id, rep);
    if (index == -1)
    {
        return 0;
    }
    for (i = index; i < rep->albuns.index - 1; i++)
    {
        rep->albuns.albuns[i] = rep->albuns.albuns[i + 1];
    }
    rep->albuns.index--;
    rep->albuns.albuns = (Album *)realloc(rep->albuns.albuns, rep->albuns.index * sizeof(Album));
    return 1;
}

int remover_musica(int id, RepMusica *rep)
{
    int i, index = buscar_musica(id, rep);
    int album_index = buscar_album(rep->musicas.musicas[index].id_album, rep);
    if (index == -1)
    {
        return 0;
    }
    rep->albuns.albuns[album_index].duracao -= rep->musicas.musicas[index].duracao;
    for (i = index; i < rep->musicas.index - 1; i++)
    {
        rep->musicas.musicas[i] = rep->musicas.musicas[i + 1];
    }
    rep->musicas.index--;
    rep->musicas.musicas = (Musica *)realloc(rep->musicas.musicas, rep->musicas.index * sizeof(Musica));
    return 1;
}

void print_menu(char **menu)
{
    int i;
    for (i = 0; i < sizeof(menu) / sizeof(menu[0]); i++)
    {
        printf("%s\n", menu[i]);
    }
}

int main()
{
    RepMusica repositorio = construtor_rep();
    char menus[][23] = {"1. Gerenciar artistas", "2. Gerenciar albuns", "3. Gerenciar musicas", "4. Sair", "Digite a opcao: "};
    char menuCrud[][20] = {"1. Cadastrar", "2. Buscar", "3. Listar", "4. Atualizar", "5. Remover", "6. Cancelar", "Digite a opcao: "};
    registrar_artista(construtor_artista("JOAO", 0), &repositorio);
    registrar_artista(construtor_artista("JESSIKA", 0), &repositorio);

    registrar_album(construtor_album("BALADONA FODA", 2009, 0, 1), &repositorio);
    registrar_album(construtor_album("FESTA JUNINA", 2009, 0, 1), &repositorio);

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
    int op, subop, id, index, ano, id_artista, id_album, duracao, faixa;
    char nome[50], titulo[100], genero[20];
    Artista artista;
    Album album;
    Musica musica;

    do
    {
        int i, j, k;
        for (i = 0; i < 5; i++)
        {
            printf("%s\n", menus[i]);
        }
        scanf("%d", &op);
        if (op != 4)
        {
            for (j = 0; j < 7; j++)
            {
                printf("%s\n", menuCrud[j]);
            }
            scanf("%d", &subop);
        }
        switch (op)
        {
        case 1:
            switch (subop)
            {
            case 1:
                printf("Nome: ");
                scanf(" %[^\n]%*c", nome);
                registrar_artista(construtor_artista(nome, 0), &repositorio);
                break;
            case 2:
                printf("Id: ");
                scanf("%d", &id);
                index = buscar_artista(id, &repositorio);
                if (index != -1)
                {
                    artista = repositorio.artistas.artistas[index];
                    printf("Nome: %s\n", artista.nome);
                    printf("Ouvinte: %d\n", artista.ouvintes);
                }
                else
                {
                    printf("Artista nao encontrado!\n");
                }
                break;
            case 3:
                printf("---Artistas---\n");
                for (k = 0; k < repositorio.artistas.index; k++)
                {
                    printf("Id: %d\n", repositorio.artistas.artistas[k].id);
                    printf("Nome: %s\n", repositorio.artistas.artistas[k].nome);
                    printf("Ouvinte: %d\n", repositorio.artistas.artistas[k].ouvintes);
                    printf("--------------\n");
                }
                break;
            case 4:
                printf("Id: ");
                scanf("%d", &id);
                index = buscar_artista(id, &repositorio);
                if (index != -1)
                {
                    artista = repositorio.artistas.artistas[index];
                    printf("Nome: ");
                    scanf(" %[^\n]%*c", artista.nome);
                    atualizar_artista(artista, &repositorio);
                }
                else
                {
                    printf("Artista nao encontrado!\n");
                }
                break;
            case 5:
                printf("Id: ");
                scanf("%d", &id);
                if (!remover_artista(id, &repositorio))
                {
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
            switch (subop)
            {
            case 1:
                printf("Titulo: ");
                scanf(" %[^\n]%*c", titulo);
                printf("Ano: ");
                scanf("%d", &ano);
                printf("Id do Artista: ");
                scanf("%d", &id_artista);
                registrar_album(construtor_album(titulo, ano, 0, id_artista), &repositorio);
                break;
            case 2:
                printf("Id: ");
                scanf("%d", &id);
                index = buscar_album(id, &repositorio);
                if (index != -1)
                {
                    album = repositorio.albuns.albuns[index];
                    printf("Titulo: %s\n", album.titulo);
                    printf("Ano: %d\n", album.ano);
                    printf("Duracao: %d\n", album.duracao);
                    printf("Artista: %s\n", repositorio.artistas.artistas[buscar_artista(album.id_artista, &repositorio)].nome);
                }
                else
                {
                    printf("Album nao encontrado!\n");
                }
                break;
            case 3:
                printf("---Albuns---\n");
                for (k = 0; k < repositorio.albuns.index; k++)
                {
                    printf("Id: %d\n", repositorio.albuns.albuns[k].id);
                    printf("Titulo: %s\n", repositorio.albuns.albuns[k].titulo);
                    printf("Ano: %d\n", repositorio.albuns.albuns[k].ano);
                    printf("Duracao: %d\n", repositorio.albuns.albuns[k].duracao);
                    printf("Artista: %s\n", repositorio.artistas.artistas[buscar_artista(repositorio.albuns.albuns[k].id_artista, &repositorio)].nome);
                    printf("--------------\n");
                }
                break;
            case 4:
                printf("Id: ");
                scanf("%d", &id);
                index = buscar_album(id, &repositorio);
                if (index != -1)
                {
                    album = repositorio.albuns.albuns[index];
                    printf("Titulo: ");
                    scanf(" %[^\n]%*c", album.titulo);
                    printf("Ano: ");
                    scanf("%d", &album.ano);
                    printf("Id do Artista: ");
                    scanf("%d", &album.id_artista);
                    atualizar_album(album, &repositorio);
                }
                else
                {
                    printf("Album nao encontrado!\n");
                }
                break;
            case 5:
                printf("Id: ");
                scanf("%d", &id);
                if (!remover_album(id, &repositorio))
                {
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
            switch (subop)
            {
            case 1:
                printf("Titulo: ");
                scanf(" %[^\n]%*c", titulo);
                printf("Genero: ");
                scanf(" %[^\n]%*c", genero);
                printf("Duracao(min): ");
                scanf("%d", &duracao);
                printf("Numero da faixa: ");
                scanf("%d", &faixa);
                printf("Id do Album: ");
                scanf("%d", &id_album);
                registrar_musica(construtor_musica(titulo, genero, 0, id_album, duracao, faixa), &repositorio);
                break;
            case 2:
                printf("Id: ");
                scanf("%d", &id);
                index = buscar_musica(id, &repositorio);
                if (index != -1)
                {
                    musica = repositorio.musicas.musicas[index];
                    printf("Titulo: %s\n", musica.titulo);
                    printf("Genero: %s\n", musica.genero);
                    printf("Duracao: %d\n", musica.duracao);
                    printf("Numero da faixa: %d\n", musica.faixa);
                    album = repositorio.albuns.albuns[buscar_album(musica.id_album, &repositorio)];
                    printf("Album: %s\n", album.titulo);
                    printf("Artista: %s\n", repositorio.artistas.artistas[buscar_album(album.id_artista, &repositorio)].nome);
                }
                else
                {
                    printf("Album nao encontrado!\n");
                }
                break;
            case 3:
                printf("---Musicas---\n");
                for (k = 0; k < repositorio.musicas.index; k++)
                {
                    printf("Id: %d\n", repositorio.musicas.musicas[k].id);
                    printf("Titulo: %s\n", repositorio.musicas.musicas[k].titulo);
                    printf("Genero: %s\n", repositorio.musicas.musicas[k].genero);
                    printf("Duracao: %d\n", repositorio.musicas.musicas[k].duracao);
                    printf("Numero da faixa: %d\n", repositorio.musicas.musicas[k].faixa);
                    album = repositorio.albuns.albuns[buscar_album(repositorio.musicas.musicas[k].id_album, &repositorio)];
                    printf("Album: %s\n", album.titulo);
                    printf("Artista: %s\n", repositorio.artistas.artistas[buscar_album(album.id_artista, &repositorio)].nome);
                    printf("--------------\n");
                }
                break;
            case 4:
                printf("Id: ");
                scanf("%d", &id);
                index = buscar_musica(id, &repositorio);
                if (index != -1)
                {
                    musica = repositorio.musicas.musicas[index];
                    printf("Titulo: ");
                    scanf(" %[^\n]%*c", musica.titulo);
                    printf("Genero: ");
                    scanf(" %[^\n]%*c", musica.genero);
                    printf("Duracao(min): ");
                    scanf("%d", &musica.duracao);
                    printf("Numero da faixa: ");
                    scanf("%d", &musica.faixa);
                    atualizar_musica(musica, &repositorio);
                }
                else
                {
                    printf("Album nao encontrado!\n");
                }
                break;
            case 5:
                printf("Id: ");
                scanf("%d", &id);
                if (!remover_musica(id, &repositorio))
                {
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
    } while (op != 4);
}