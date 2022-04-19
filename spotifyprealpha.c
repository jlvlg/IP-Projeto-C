#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32 
    #include <windows.h>
#endif

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
int *listar_artistas_por_nome(char *nome, RepMusica *rep);
int *listar_albuns_por_artista(int id_artista, RepMusica *rep);
int *listar_albuns_por_ano(int ano, RepMusica *rep);
int *listar_albuns_por_titulo(char *titulo, RepMusica *rep);
int *listar_musicas_por_artista(int id_artista, RepMusica *rep);
int *listar_musicas_por_titulo(char *titulo, RepMusica *rep);
int *listar_musicas_por_album(int id_album, RepMusica *rep);
int *listar_musicas_por_genero(char *genero, RepMusica *rep);

int main() {
    int h, m, s;
    RepMusica repositorio = construtor_rep();
    // Menu pricipal
    char menus[][40] = {"Spotify pre-ALPHA (0.15a)", "1. Gerenciar artistas", "2. Gerenciar albuns", "3. Gerenciar musicas", "4. Sair", "\nDigite a opcao: "};
    // Submenu com as operações de CRUD
    char menuCrud[][40] = {"1. Cadastrar", "2. Buscar", "3. Listar", "4. Atualizar", "5. Remover", "6. Cancelar", "\nDigite a opcao: "};
    // Submenu com as opções de listagem para Artista
    char menuFiltrarArtista[][40] = {"Listar artistas", "1. Mostrar todos", "2. Filtrar por nome", "3. Cancelar", "\nDigite a opcao: "};
    // Submenu com as opções de listagem para Álbum
    char menuFiltrarAlbum[][40] = {"Listar albuns", "1. Mostrar todos", "2. Filtrar por titulo", "3. Filtrar por ano", "4. Filtrar por artista", "5. Cancelar", "\nDigite a opcao: "};
    // Submenu com as opções de listagem para Músicas
    char menuFiltrarMusica[][40] = {"Listar musicas", "1. Mostrar todos", "2. Filtrar por titulo", "3. Filtrar por artista", "4. Filtrar por album", "5. Filtrar por genero", "6. Cancelar", "\nDigite a opcao: "};
    int op, subop, filtrarop, id, index, ano, id_artista, id_album, faixa;
    int *artistas, *albuns, *musicas;
    char nome[50], titulo[100], genero[20];
    Artista artista;
    Album album;
    Musica musica;

    #ifdef _WIN32
        SetConsoleTitle("Spotify pre-ALPHA (0.15a)");
    #else
        printf("\033];Spotify pre-ALPHA (0.15a)\007");
    #endif

    do {
        int i;
        clear();  // Limpa o terminal
        for (i = 0; i < 6; i++) {
            printf("%s\n", menus[i]);  // Imprime o menu principal
        }
        while (scanf("%d", &op) != 1) {  // Scanf retorna +1 para cada operação bem-sucedida, pode ser usado para garantir entrada de int
            printf("Insira apenas um numero: ");
            while ((getchar()) != '\n')  // Limpa o buffer do stdin
                ;
        }

        if (op >= 1 && op <= 3) {
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
                printf("%s\n", menuCrud[i]);  // Imprime o menu dos CRUDs
            }
            while (scanf("%d", &subop) != 1) {
                printf("Insira apenas um numero: ");
                while ((getchar()) != '\n')
                    ;
            }
        }
        clear();
        while (getchar() != '\n')
            ;
        switch (op) {
            case 1:  // Gerenciamento de artistas
                switch (subop) {
                    case 1:  // Cadastrar artista
                        printf("Cadastrar artista\n");
                        printf("Nome: ");
                        scanf(" %[^\n]%*c", nome);  // " %[^\n]%*c" garante que espaços sejam incluídos na string e limpa o \n do buffer
                        registrar_artista(construtor_artista(nome), &repositorio);
                        break;
                    case 2:  // Buscar artista
                        printf("Buscar artista\n");
                        printf("Id: ");
                        while (scanf("%d", &id) != 1) {
                            printf("Insira apenas um numero: ");
                            while ((getchar()) != '\n')
                                ;
                        }
                        while (getchar() != '\n')
                            ;
                        index = buscar_artista(id, &repositorio);
                        clear();
                        if (index != -1) {                        // buscar_{struct} retorna -1 caso não encontre nenhum
                            exibir_artista(index, &repositorio);  // Imprime as informações do artista
                            // listar_{struct}_por_{dado} retorna -1 caso não encontre nenhum {struct} correspondente no repositório
                            albuns = listar_albuns_por_artista(id, &repositorio);
                            if (albuns[0] != -1) {
                                printf("---Albuns---\n");
                                for (i = 0; albuns[i] != -1; i++) {
                                    album = repositorio.albuns.albuns[albuns[i]];
                                    printf("%d - %s (%d)\n", album.id, album.titulo, album.ano);
                                    // Imprime o id, título e ano dos albuns pertencentes ao artista
                                };
                                printf("------------\n");
                                free(albuns);  // Libera o malloc - IMPORTANTE
                            }
                        } else {
                            printf("Artista nao encontrado!\n");
                        }
                        break;
                    case 3:  // Listar artistas
                        if (repositorio.artistas.index > 0) {
                            for (i = 0; i < 5; i++) {
                                printf("%s\n", menuFiltrarArtista[i]);  // Imprime o menu de filtros
                            }
                            while (scanf("%d", &filtrarop) != 1) {
                                printf("Insira apenas um numero: ");
                                while ((getchar()) != '\n')
                                    ;
                            }
                            while (getchar() != '\n')
                                ;
                            switch (filtrarop) {
                                case 1:  // Listar todos
                                    clear();
                                    printf("---Artistas---\n");
                                    for (i = 0; i < repositorio.artistas.index; i++) {
                                        exibir_artista(i, &repositorio);
                                        printf("--------------\n");
                                    };
                                    break;
                                case 2:  // Listar por nome
                                    printf("Nome: ");
                                    scanf(" %[^\n]%*c", nome);
                                    artistas = listar_artistas_por_nome(nome, &repositorio);
                                    clear();
                                    if (artistas[0] != -1) {
                                        printf("---Artistas---\n");
                                        for (i = 0; artistas[i] != -1; i++) {
                                            exibir_artista(artistas[i], &repositorio);
                                            printf("--------------\n");
                                        };
                                    } else {
                                        printf("Nenhum artista encontrado\n");
                                    }
                                    free(artistas);  // IMPORTANTE
                                    break;
                                case 3:
                                    continue;
                                default:
                                    printf("Operacao invalida\n");
                                    break;
                            }
                        } else {
                            printf("Nao ha artistas cadastrados\n");
                        }
                        break;
                    case 4:  // Alterar artista
                        printf("Alterar artista\n");
                        printf("Id: ");
                        while (scanf("%d", &id) != 1) {
                            printf("Insira apenas um numero: ");
                            while ((getchar()) != '\n')
                                ;
                        }
                        while (getchar() != '\n')
                            ;
                        index = buscar_artista(id, &repositorio);
                        if (index != -1) {
                            artista = repositorio.artistas.artistas[index];  // Cria um artista temporário para edição
                            printf("Novo nome: ");
                            scanf(" %[^\n]%*c", artista.nome);
                            atualizar_artista(artista, &repositorio);  // Troca o artista no repositório pelo temporário com base em artista.id
                        } else {
                            printf("Artista nao encontrado!\n");
                        }
                        break;
                    case 5:
                        printf("Remover artista\n");
                        printf("Id: ");
                        while (scanf("%d", &id) != 1) {
                            printf("Insira apenas um numero: ");
                            while ((getchar()) != '\n')
                                ;
                        }
                        while (getchar() != '\n')
                            ;
                        // Impede que o usuário remova um artista se ele contém álbuns
                        if (listar_albuns_por_artista(id, &repositorio)[0] == -1) {
                            // remover_{struct} retorna 0 caso não exista {struct} com esse id no repositório
                            if (!remover_artista(id, &repositorio)) {
                                printf("Artista nao encontrado!\n");
                            }
                        } else {
                            printf("Nao e possivel remover artistas com albuns cadastrados!\n");
                        }

                        break;
                    case 6:
                        continue;
                    default:
                        printf("Opcao invalida!\n");
                        break;
                }
                break;
            case 2:  // Gerenciamento de álbuns
                switch (subop) {
                    case 1:  // Cadastrar álbum
                        printf("Cadastrar album\n");
                        printf("Titulo: ");
                        scanf(" %[^\n]%*c", titulo);
                        printf("Ano: ");
                        while (scanf("%d", &ano) != 1) {
                            printf("Insira apenas um numero: ");
                            while ((getchar()) != '\n')
                                ;
                        }
                        while (getchar() != '\n')
                            ;
                        printf("Id do Artista: ");
                        while (scanf("%d", &id_artista) != 1) {
                            printf("Insira apenas um numero: ");
                            while ((getchar()) != '\n')
                                ;
                        }
                        while (getchar() != '\n')
                            ;
                        // registrar_album retorna -1 caso não exista artista com o id_artista provido
                        if (registrar_album(construtor_album(titulo, ano, id_artista), &repositorio) == -1) {
                            printf("Artista invalido\n");
                        }
                        break;
                    case 2:  // Buscar álbum
                        printf("Buscar album\n");
                        printf("Id: ");
                        while (scanf("%d", &id) != 1) {
                            printf("Insira apenas um numero: ");
                            while ((getchar()) != '\n')
                                ;
                        }
                        while (getchar() != '\n')
                            ;
                        index = buscar_album(id, &repositorio);
                        clear();
                        if (index != -1) {
                            exibir_album(index, &repositorio);  // Imprime os dados do álbum
                            musicas = listar_musicas_por_album(repositorio.albuns.albuns[index].id, &repositorio);
                            if (musicas[0] != -1) {
                                printf("---Musicas---\n");
                                for (i = 0; musicas[i] != -1; i++) {
                                    musica = repositorio.musicas.musicas[musicas[i]];
                                    printf("%d - %s\n", musica.faixa, musica.titulo);
                                    // Imprime o nº da faixa e o título das músicas contidas no álbum
                                };
                                printf("-----------\n");
                            }
                            free(musicas);  // IMPORTANTE
                        } else {
                            printf("Album nao encontrado!\n");
                        }
                        break;
                    case 3:  // Listar álbuns
                        if (repositorio.albuns.index > 0) {
                            for (i = 0; i < 7; i++) {
                                printf("%s\n", menuFiltrarAlbum[i]);
                            }
                            while (scanf("%d", &filtrarop) != 1) {
                                printf("Insira apenas um numero: ");
                                while ((getchar()) != '\n')
                                    ;
                            }
                            while (getchar() != '\n')
                                ;
                            switch (filtrarop) {
                                case 1:  // Listar todos os álbuns
                                    clear();
                                    printf("---Albuns---\n");
                                    for (i = 0; i < repositorio.albuns.index; i++) {
                                        exibir_album(i, &repositorio);
                                        printf("------------\n");
                                    };
                                    break;
                                case 2:  // Filtrar por título
                                    printf("Titulo: ");
                                    scanf(" %[^\n]%*c", titulo);
                                    albuns = listar_albuns_por_titulo(titulo, &repositorio);
                                    break;
                                case 3:  // Filtrar por ano
                                    printf("Ano: ");
                                    while (scanf("%d", &ano) != 1) {
                                        printf("Insira apenas um numero: ");
                                        while ((getchar()) != '\n')
                                            ;
                                    }
                                    while (getchar() != '\n')
                                        ;
                                    albuns = listar_albuns_por_ano(ano, &repositorio);
                                    break;
                                case 4:  // Filtrar por artista
                                    printf("Id do Artista: ");
                                    while (scanf("%d", &id_artista) != 1) {
                                        printf("Insira apenas um numero: ");
                                        while ((getchar()) != '\n')
                                            ;
                                    }
                                    while (getchar() != '\n')
                                        ;
                                    albuns = listar_albuns_por_artista(id_artista, &repositorio);
                                    break;
                                case 5:
                                    continue;
                                default:
                                    printf("Opcao invalida!\n");
                                    break;
                            }
                            if (filtrarop >= 2 && filtrarop <= 4) {
                                clear();
                                if (albuns[0] != -1) {
                                    printf("---Albuns---\n");
                                    for (i = 0; albuns[i] != -1; i++) {
                                        exibir_album(albuns[i], &repositorio);  // Imprime o resultado dos filtros
                                        printf("------------\n");
                                    };
                                } else {
                                    printf("Nenhum album encontrado\n");
                                }
                                free(albuns);  // IMPORTANTE
                            }
                        } else {
                            printf("Nao ha albuns cadastrados!\n");
                        }
                        break;
                    case 4:  // Alterar álbum
                        printf("Alterar album\n");
                        printf("Id: ");
                        while (scanf("%d", &id) != 1) {
                            printf("Insira apenas um numero: ");
                            while ((getchar()) != '\n')
                                ;
                        }
                        while (getchar() != '\n')
                            ;
                        index = buscar_album(id, &repositorio);
                        if (index != -1) {
                            album = repositorio.albuns.albuns[index];  // Cria um álbum temporário para alterações
                            printf("Novo titulo: ");
                            scanf(" %[^\n]%*c", album.titulo);
                            printf("Novo ano: ");
                            while (scanf("%d", &album.ano) != 1) {
                                printf("Insira apenas um numero: ");
                                while ((getchar()) != '\n')
                                    ;
                            }
                            while (getchar() != '\n')
                                ;
                            atualizar_album(album, &repositorio);  // Substitui o álbum do repositório pelo temporário
                        } else {
                            printf("Album nao encontrado!\n");
                        }
                        break;
                    case 5:  // Remover álbum
                        printf("Remover album\n");
                        printf("Id: ");
                        while (scanf("%d", &id) != 1) {
                            printf("Insira apenas um numero: ");
                            while ((getchar()) != '\n')
                                ;
                        }
                        while (getchar() != '\n')
                            ;
                        // Impede que o usuário remova um álbum sem antes remover suas músicas
                        if (listar_musicas_por_album(id, &repositorio)[0] == -1) {
                            if (!remover_album(id, &repositorio)) {
                                printf("Album nao encontrado!\n");
                            }
                        } else {
                            printf("Nao e possivel remover albuns com musicas cadastradas!\n");
                        }
                        break;
                    case 6:
                        continue;
                    default:
                        printf("Opcao invalida!\n");
                        break;
                }
                break;
            case 3:  // Gerenciar músicas
                switch (subop) {
                    case 1:  // Cadastrar música
                        printf("Cadastrar musica\n");
                        printf("Titulo: ");
                        scanf(" %[^\n]%*c", titulo);
                        printf("Genero: ");
                        scanf(" %[^\n]%*c", genero);
                        printf("Duracao (hh:mm:ss): ");
                        while (scanf("%d:%d:%d", &h, &m, &s) != 3) {  // Duração das músicas é inserida no formato hh:mm:ss
                            printf("Insira um horario em formato valido (hh:mm:ss): ");
                            while ((getchar()) != '\n')
                                ;
                        }
                        while (getchar() != '\n')
                            ;
                        printf("Numero da faixa: ");
                        // Número da faixa não é definida automaticamente. Duas músicas podem ter o mesmo número de faixa caso o usuário o deseje.
                        while (scanf("%d", &faixa) != 1) {
                            printf("Insira apenas um numero: ");
                            while ((getchar()) != '\n')
                                ;
                        }
                        while (getchar() != '\n')
                            ;
                        printf("Id do Album: ");
                        while (scanf("%d", &id_album) != 1) {
                            printf("Insira apenas um numero: ");
                            while ((getchar()) != '\n')
                                ;
                        }
                        while (getchar() != '\n')
                            ;
                        // registrar_musica irá retornar -1 caso o id_album provido não esteja associado a nenhum álbum no repositório
                        // Note que h é multiplicado por 3600 e m por 60, isso ocorre pois a duração é armazenada em segundos
                        if (registrar_musica(construtor_musica(titulo, genero, id_album, h * 60 * 60 + m * 60 + s, faixa), &repositorio) == -1) {
                            printf("Album invalido\n");
                        }
                        break;
                    case 2:  // Buscar música
                        printf("Buscar musica\n");
                        printf("Id: ");
                        while (scanf("%d", &id) != 1) {
                            printf("Insira apenas um numero: ");
                            while ((getchar()) != '\n')
                                ;
                        }
                        while (getchar() != '\n')
                            ;
                        index = buscar_musica(id, &repositorio);
                        clear();
                        if (index != -1) {
                            int index_album = buscar_album(repositorio.musicas.musicas[index].id_album, &repositorio);
                            int index_artista = buscar_artista(repositorio.albuns.albuns[index].id_artista, &repositorio);
                            exibir_musica(index, &repositorio);
                            repositorio.artistas.artistas[index_artista].ouvintes++;
                            // Funcionalidade que pode passar despercebida, ao buscar uma música em específico o valor
                            // de ouvintes do artista é acrescido de 1, como se alguém tivesse escutado sua música
                        } else {
                            printf("Musica nao encontrado!\n");
                        }
                        break;
                    case 3:  // Listar músicas
                        if (repositorio.musicas.index > 0) {
                            for (i = 0; i < 8; i++) {
                                printf("%s\n", menuFiltrarMusica[i]);
                            }
                            while (scanf("%d", &filtrarop) != 1) {
                                printf("Insira apenas um numero: ");
                                while ((getchar()) != '\n')
                                    ;
                            }
                            while (getchar() != '\n')
                                ;
                            switch (filtrarop) {
                                case 1:  // Listar todas as músicas
                                    clear();
                                    printf("---Musicas---\n");
                                    for (i = 0; i < repositorio.musicas.index; i++) {
                                        exibir_musica(i, &repositorio);
                                        printf("-------------\n");
                                    };
                                    break;
                                case 2:  // Filtrar por título
                                    printf("Titulo: ");
                                    scanf(" %[^\n]%*c", titulo);
                                    musicas = listar_musicas_por_titulo(titulo, &repositorio);
                                    break;
                                case 3:  // Filtrar por artista
                                    printf("Id do artista: ");
                                    while (scanf("%d", &id_artista) != 1) {
                                        printf("Insira apenas um numero: ");
                                        while ((getchar()) != '\n')
                                            ;
                                    }
                                    while (getchar() != '\n')
                                        ;
                                    musicas = listar_musicas_por_artista(id_artista, &repositorio);
                                    break;
                                case 4:  // Filtrar por álbum
                                    printf("Id do Album: ");
                                    while (scanf("%d", &id_album) != 1) {
                                        printf("Insira apenas um numero: ");
                                        while ((getchar()) != '\n')
                                            ;
                                    }
                                    while (getchar() != '\n')
                                        ;
                                    musicas = listar_musicas_por_album(id_album, &repositorio);
                                    break;
                                case 5:  // Filtrar por gênero
                                    printf("Genero: ");
                                    scanf(" %[^\n]%*c", genero);
                                    musicas = listar_musicas_por_genero(genero, &repositorio);
                                    break;
                                case 6:
                                    continue;
                                default:
                                    break;
                            }
                            if (filtrarop >= 2 && filtrarop <= 5) {
                                clear();
                                if (musicas[0] != -1) {
                                    printf("---Musicas---\n");
                                    for (i = 0; musicas[i] != -1; i++) {
                                        exibir_musica(musicas[i], &repositorio);  // Imprime as músicas encontradas
                                        printf("-----------\n");
                                    };
                                } else {
                                    printf("Nenhuma musica encontrada\n");
                                }
                                free(musicas);
                            }
                        } else {
                            printf("Nao ha musicas cadastradas\n");
                        }
                        break;
                    case 4:  // Alterar música
                        printf("Alterar musica\n");
                        printf("Id: ");
                        while (scanf("%d", &id) != 1) {
                            printf("Insira apenas um numero: ");
                            while ((getchar()) != '\n')
                                ;
                        }
                        while (getchar() != '\n')
                            ;
                        index = buscar_musica(id, &repositorio);
                        if (index != -1) {
                            musica = repositorio.musicas.musicas[index];  // Cria uma música temporária para alterações
                            printf("Novo titulo: ");
                            scanf(" %[^\n]%*c", musica.titulo);
                            printf("Novo genero: ");
                            scanf(" %[^\n]%*c", musica.genero);
                            printf("Nova duracao (hh:mm:ss): ");
                            while (scanf("%d:%d:%d", &h, &m, &s) != 3) {
                                printf("Insira um horario em formato valido (hh:mm:ss): ");
                                while ((getchar()) != '\n')
                                    ;
                            }
                            while (getchar() != '\n')
                                ;
                            musica.duracao = h * 60 * 60 + m * 60 + s;
                            printf("Novo numero da faixa: ");
                            while (scanf("%d", &musica.faixa) != 1) {
                                printf("Insira apenas um numero: ");
                                while ((getchar()) != '\n')
                                    ;
                            }
                            while (getchar() != '\n')
                                ;
                            atualizar_musica(musica, &repositorio);
                        } else {
                            printf("Musica nao encontrada!\n");
                        }
                        break;
                    case 5:  // Remover música
                        printf("Remover musica\n");
                        printf("Id: ");
                        while (scanf("%d", &id) != 1) {
                            printf("Insira apenas um numero: ");
                            while ((getchar()) != '\n')
                                ;
                        }
                        while (getchar() != '\n')
                            ;
                        if (!remover_musica(id, &repositorio)) {
                            printf("Musica nao encontrada!\n");
                        }
                        break;
                    case 6:
                        continue;
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
        printf("Pressione ENTER para continuar...");
        while (getchar() != '\n')  // Caso o buffer do stdin tenha sido previamente limpo, irá aguardar a entrada do usuário
            ;
    } while (op != 4);

    return 0;
}

void clear() {
#ifdef _WIN32
    system("cls");  // O terminal windows é limpo com cls
#else
    system("clear");  // O terminal unix é limpo com clear
#endif
}

// Recebe os dados de um artista e retorna um artista preenchido
Artista construtor_artista(char *nome) {
    Artista temp;
    strcpy(temp.nome, nome);
    temp.ouvintes = 0;  // ouvintes não precisa ser passado por parâmetro por sempre iniciar com 0
    return temp;
}

// Recebe os dados de um álbum e retorna um álbum preenchido
Album construtor_album(char *titulo, int ano, int id_artista) {
    Album temp;

    strcpy(temp.titulo, titulo);
    temp.ano = ano;

    temp.id_artista = id_artista;
    temp.duracao = 0;  // A duração começa com zero e é acrescida pela duração das músicas que são atribuidas ao álbum
    return temp;
}

// Recebe os dados de uma música e retorna uma música preenchida
Musica construtor_musica(char *titulo, char *genero, int id_album, int duracao, int faixa) {
    Musica temp;
    strcpy(temp.titulo, titulo);
    strcpy(temp.genero, genero);
    temp.id_album = id_album;
    temp.duracao = duracao;
    temp.faixa = faixa;
    return temp;
}

// Inicializa um repositório geral e o retorna
RepMusica construtor_rep() {
    RepMusica temp;

    // Aloca 0 espaços de memória para as listas de structs presente nesse repositório
    temp.artistas.artistas = (Artista *)malloc(0);
    temp.albuns.albuns = (Album *)malloc(0);
    temp.musicas.musicas = (Musica *)malloc(0);

    // Inicializa os valores dos índices e ids dos próximo struct a ser cadastrado com 0 e 1, respectivamente
    temp.artistas.index = temp.albuns.index = temp.musicas.index = 0;
    temp.artistas.next_id = temp.albuns.next_id = temp.musicas.next_id = 1;

    return temp;
}

// Armazena o artista recebido na lista de artistas do repositório geral
void registrar_artista(Artista artista, RepMusica *rep) {
    // Reloca o tamanho da lista de artistas para comportar o próximo artista a ser cadastrado
    rep->artistas.artistas = (Artista *)realloc(rep->artistas.artistas, (rep->artistas.index + 1) * sizeof(Artista));

    // Atribui ao artista os próximos valores de índice e id disponiveis
    artista.id = rep->artistas.next_id;
    rep->artistas.artistas[rep->artistas.index] = artista;

    // Aumenta mais 1 aos próximos valores de id e índice
    rep->artistas.next_id++;
    rep->artistas.index++;
}

// Armazena o álbum recebido na lista de álbuns do repositório geral e retorna o seu índice
int registrar_album(Album album, RepMusica *rep) {
    // Busca na lista de artistas o artista com o id passado junto com o álbum e retorna seu índice
    int artista_index = buscar_artista(album.id_artista, rep);
    // Se o índice recebido é -1, o artista não foi encontrado e o álbum não pode ser armazenado
    if (artista_index == -1) {
        return artista_index;  // Retorna -1 informando o erro durante o armazenamento
    }
    rep->albuns.albuns = (Album *)realloc(rep->albuns.albuns, (rep->albuns.index + 1) * sizeof(Album));

    album.id = rep->albuns.next_id;
    rep->albuns.albuns[rep->albuns.index] = album;

    rep->albuns.next_id++;
    rep->albuns.index++;

    return rep->albuns.index - 1;
}

// Armazena a música recebida na lista de músicas do repositório geral e retorna o seu índice
int registrar_musica(Musica musica, RepMusica *rep) {
    // Busca na lista de álbuns o álbum com o id passado junto com a música e retorna seu índice
    int album_index = buscar_album(musica.id_album, rep);
    // Se o índice recebido é -1, o álbum não foi encontrado e a música não pode ser armazenada
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

// Retorna o índice do artista com o id recebido
int buscar_artista(int id, RepMusica *rep) {
    int i, index = -1;  // Se o artista não for encontrado o índice continuará -1
    for (i = 0; i < rep->artistas.index; i++) {
        if (rep->artistas.artistas[i].id == id) {
            index = i;
            break;
        }
    }
    return index;
}

// Retorna o índice do álbum com o id recebido
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

// Retorna o índice da música com o id recebido
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

// Substitui o artista com o mesmo id do artista recebido e retorna se houve êxito na operação
int atualizar_artista(Artista artista, RepMusica *rep) {
    int index = buscar_artista(artista.id, rep);
    if (index == -1) {
        return 0;  // Se o artista não foi encontrado retorna zero
    }
    rep->artistas.artistas[index] = artista;  // Armazena o artista recebido na posição do outro com o mesmo id
    return 1;                                 // Se o artista foi alterado com êxito retorna 1
}

// Substitui o álbum com o mesmo id do álbum recebido e retorna se houve êxito na operação
int atualizar_album(Album album, RepMusica *rep) {
    int index = buscar_album(album.id, rep);
    if (index == -1) {
        return 0;
    }
    rep->albuns.albuns[index] = album;
    return 1;
}

// Substitui a música com o mesmo id da música recebida e retorna se houve êxito na operação
int atualizar_musica(Musica musica, RepMusica *rep) {
    int index = buscar_musica(musica.id, rep), album_index = buscar_album(musica.id_album, rep);
    if (index == -1) {
        return 0;
    }
    // Corrige a duração do álbum com base na nova duração da música
    rep->albuns.albuns[album_index].duracao += musica.duracao - rep->musicas.musicas[index].duracao;
    rep->musicas.musicas[index] = musica;

    return 1;
}

// Remove o artista com o id recebido e retorna se houve êxito na operação
int remover_artista(int id, RepMusica *rep) {
    int i, index = buscar_artista(id, rep);
    if (index == -1) {
        return 0;
    }
    for (i = index; i < rep->artistas.index - 1; i++) {             // Começa o laço de repetição com o índice do artista com o id recebido
        rep->artistas.artistas[i] = rep->artistas.artistas[i + 1];  // Recua todos os artistas em uma posição a partir do índice do artista com o id recebido
    }
    rep->artistas.index--;                                                                                       // Diminui em 1 o índice do próximo artista cadastrado
    rep->artistas.artistas = (Artista *)realloc(rep->artistas.artistas, rep->artistas.index * sizeof(Artista));  // Realoca o tamanho da lista de artistas com base no atual número de artistas
    return 1;
}

// Remove o álbum com o id recebido e retorna se houve êxito na operação
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

// Remove a música com o id recebido e retorna se houve êxito na operação
int remover_musica(int id, RepMusica *rep) {
    int i, index = buscar_musica(id, rep);
    int album_index = buscar_album(rep->musicas.musicas[index].id_album, rep);
    if (index == -1) {
        return 0;
    }
    rep->albuns.albuns[album_index].duracao -= rep->musicas.musicas[index].duracao;  // Atualiza a duração do álbum atribuido a essa música
    for (i = index; i < rep->musicas.index - 1; i++) {
        rep->musicas.musicas[i] = rep->musicas.musicas[i + 1];
    }
    rep->musicas.index--;
    rep->musicas.musicas = (Musica *)realloc(rep->musicas.musicas, rep->musicas.index * sizeof(Musica));
    return 1;
}

// Imprime os dados do artista
void exibir_artista(int index, RepMusica *rep) {
    Artista artista = rep->artistas.artistas[index];  // Coleta o artista a ser exibido
    printf("Id: %d\n", artista.id);                   // Imprime o id
    printf("Nome: %s\n", artista.nome);               // Imprime o nome
    printf("Ouvintes: %d\n", artista.ouvintes);       // Imprime a quantidade de ouvintes
}

// Imprime os dados do álbum
void exibir_album(int index, RepMusica *rep) {
    int h, m, s;
    Album album = rep->albuns.albuns[index];  // Coleta o álbum a ser exibido
    printf("Id: %d\n", album.id);             // Imprime o id
    printf("Titulo: %s\n", album.titulo);     // Imprime o título
    printf("Ano: %d\n", album.ano);           // Imprime o ano
    h = album.duracao / 3600;
    m = (album.duracao - h * 3600) / 60;
    s = album.duracao - h * 3600 - m * 60;                                                        // Faz o cálculo reverso de segundos para horas e minutos
    printf("Duracao: %02d:%02d:%02d\n", h, m, s);                                                 // Imprime a duração com no mínimo dois algarísmos (exemplo: 1 -> 01, 2 -> 02, 123 -> 123)
    printf("Artista: %s\n", rep->artistas.artistas[buscar_artista(album.id_artista, rep)].nome);  // Imprime o nome do artista
}

// Imprime os dados da música
void exibir_musica(int index, RepMusica *rep) {
    int h, m, s;
    Musica musica = rep->musicas.musicas[index];                           // Coleta a música a ser exibida
    Album album = rep->albuns.albuns[buscar_album(musica.id_album, rep)];  // Coleta o album que contém a música
    Artista artista = rep->artistas.artistas[buscar_artista(album.id_artista, rep)];
    printf("Id: %d\n", musica.id);                                         // Imprime o id da música
    printf("Titulo: %s\n", musica.titulo);                                 // Imprime o título
    printf("Genero: %s\n", musica.genero);                                 // Imprime o gênero
    h = musica.duracao / 3600;
    m = (musica.duracao - h * 3600) / 60;
    s = musica.duracao - h * 3600 - m * 60;                                                     // Faz o cálculo reverso de segundos para horas e minutos
    printf("Duracao: %02d:%02d:%02d\n", h, m, s);                                               // Imprime a duração com no mínimo dois algarísmos
    printf("Numero da faixa: %d\n", musica.faixa);                                              // Imprime o número da faixa
    printf("Album: %s\n", album.titulo);                                                        // Imprime o título do álbum que contém a música
    printf("Artista: %s\n", artista.nome);  // Imprime o nome do artista
}

// Lista os índices dos artistas do repositório cujo nome contém a string nome fornecida
int *listar_artistas_por_nome(char *nome, RepMusica *rep) {
    int i, counter = 0;
    int *artistas;
    artistas = (int *)malloc(0);  // Aloca 0 bits para artistas (apenas para permitir realocação dinâmica)

    for (i = 0; i < rep->artistas.index; i++) {                                // Loopa por todos os artistas do repositório
        if (strstr(rep->artistas.artistas[i].nome, nome) != NULL) {            // Checa se a string nome aparece em qualquer posição no nome do artista
            artistas = (int *)realloc(artistas, (counter + 1) * sizeof(int));  // Realoca espaço suficiente para mais um int
            artistas[counter] = i;                                             // Armazena o index do artista encontrado
            counter++;
        }
    }

    artistas = (int *)realloc(artistas, (counter + 1) * sizeof(int));  // Realoca mais um espaço pra int
    artistas[counter] = -1;                                            // Armazena -1, que simboliza a finalização da lista

    return artistas;
}

// Lista os índices dos álbuns do repositório cujo id_artista corresponde ao fornecido
int *listar_albuns_por_artista(int id_artista, RepMusica *rep) {
    int i, counter = 0;
    int *albuns;
    albuns = (int *)malloc(0);  // Alocação dinâmica

    for (i = 0; i < rep->albuns.index; i++) {                              // Loopa por todos os álbuns do repositório
        if (rep->albuns.albuns[i].id_artista == id_artista) {              // Checa se o id_artista provido é igual ao do álbum
            albuns = (int *)realloc(albuns, (counter + 1) * sizeof(int));  // Realoca espaço pra uma int a mais
            albuns[counter] = i;                                           // Armazena o index do álbum
            counter++;
        }
    }

    albuns = (int *)realloc(albuns, (counter + 1) * sizeof(int));  // Realoca
    albuns[counter] = -1;                                          // Armazena -1 no final

    return albuns;
}

// Lista os índices dos álbuns do repositório cujo ano corresponda ao ano fornecido
int *listar_albuns_por_ano(int ano, RepMusica *rep) {
    int i, counter = 0;
    int *albuns;
    albuns = (int *)malloc(0);  // Armazenamento dinâmico

    for (i = 0; i < rep->albuns.index; i++) {                              // Loop nos álbuns
        if (rep->albuns.albuns[i].ano == ano) {                            // Checagem lógica por ano
            albuns = (int *)realloc(albuns, (counter + 1) * sizeof(int));  // Realoca
            albuns[counter] = i;                                           // Armazena
            counter++;
        }
    }

    albuns = (int *)realloc(albuns, (counter + 1) * sizeof(int));  // Realoca
    albuns[counter] = -1;                                          // Finaliza

    return albuns;
}

// Lista os índices dos álbuns do repositório cujo título contém a string titulo fornecida
int *listar_albuns_por_titulo(char *titulo, RepMusica *rep) {
    int i, counter = 0;
    int *albuns;
    albuns = (int *)malloc(0);  // Armazenamento dinâmico

    for (i = 0; i < rep->albuns.index; i++) {                              // Loop
        if (strstr(rep->albuns.albuns[i].titulo, titulo) != NULL) {        // Checa se a string titulo aparece em qualquer posição no título do álbum
            albuns = (int *)realloc(albuns, (counter + 1) * sizeof(int));  // Realoca
            albuns[counter] = i;                                           // Armazena index
            counter++;
        }
    }

    albuns = (int *)realloc(albuns, (counter + 1) * sizeof(int));  // Realoca
    albuns[counter] = -1;                                          // Finaliza

    return albuns;
}

// Lista os índices das músicas do repositório cujo id_artista corresponda ao fornecido
int *listar_musicas_por_artista(int id_artista, RepMusica *rep) {
    int i, j, counter = 0;
    int *musicas;
    musicas = (int *)malloc(0);  // Armazenamento dinâmica
    // Não há ligação direta entre música e artista, portanto é necessário primeiro a checagem entre música e álbum
    int *albuns = listar_albuns_por_artista(id_artista, rep);  // Lista os álbuns pertencentes ao artista
    if (albuns[0] != -1) {                                     // resultado[0] == -1 indica que não foram encontrados dados correspondentes
        for (i = 0; i < rep->musicas.index; i++) {             // Loop nas músicas do repositório
            for (int j = 0; albuns[j] != -1; j++) {            // Loop nos álbuns encontrados
                if (rep->musicas.musicas[i].id_album == rep->albuns.albuns[j].id) {
                    // Checa se música pertence ao álbum, se sim ela também pertence ao artista, já que o álbum pertence ao artista
                    musicas = (int *)realloc(musicas, (counter + 1) * sizeof(int));  // Realoca
                    musicas[counter] = i;                                            // Armazena index
                    counter++;
                    break;
                }
            }
        }
    }
    musicas = (int *)realloc(musicas, (counter + 1) * sizeof(int));  // Realoca
    musicas[counter] = -1;                                           // Finaliza

    return musicas;
}

// Lista os índices das músicas do repositório cujo título contém a string titulo fornecida
int *listar_musicas_por_titulo(char *titulo, RepMusica *rep) {
    int i, counter = 0;
    int *musicas;
    musicas = (int *)malloc(0);  // Armazenamento dinâmico

    for (i = 0; i < rep->musicas.index; i++) {                               // Loop
        if (strstr(rep->musicas.musicas[i].titulo, titulo) != NULL) {        // Checa se a string título fornecida está presente no título da música
            musicas = (int *)realloc(musicas, (counter + 1) * sizeof(int));  // Realoca
            musicas[counter] = i;                                            // Armazena index
            counter++;
        }
    }

    musicas = (int *)realloc(musicas, (counter + 1) * sizeof(int));  // Realoca
    musicas[counter] = -1;                                           // Finaliza

    return musicas;
}

// Lista os índices das músicas do repositório cujo id_album corresponda ao fornecido
int *listar_musicas_por_album(int id_album, RepMusica *rep) {
    int i, counter = 0;
    int *musicas;
    musicas = (int *)malloc(0);  // Armazenamento dinâmico

    for (i = 0; i < rep->musicas.index; i++) {                               // Loop
        if (rep->musicas.musicas[i].id_album == id_album) {                  // Checagem lógica por id
            musicas = (int *)realloc(musicas, (counter + 1) * sizeof(int));  // Realoca
            musicas[counter] = i;                                            // Armazena
            counter++;
        }
    }

    musicas = (int *)realloc(musicas, (counter + 1) * sizeof(int));  // Realoca
    musicas[counter] = -1;                                           // Finaliza

    return musicas;
}

// Lista os índices das músicas do repositório cujo gênero contém a string genero fornecida
int *listar_musicas_por_genero(char *genero, RepMusica *rep) {
    int i, counter = 0;
    int *musicas;
    musicas = (int *)malloc(0);  // Armazenamento dinâmico

    for (i = 0; i < rep->musicas.index; i++) {                               // Loop
        if (strstr(rep->musicas.musicas[i].genero, genero) != NULL) {        // Checa se a string genero aparece no gênero da música
            musicas = (int *)realloc(musicas, (counter + 1) * sizeof(int));  // Realoca
            musicas[counter] = i;                                            // Armazena
            counter++;
        }
    }

    musicas = (int *)realloc(musicas, (counter + 1) * sizeof(int));  // Realoca
    musicas[counter] = -1;                                           // Finaliza

    return musicas;
}