#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MUSICAS 100

struct Musica {
    int id;
    char nome[50];
    char artista[50];
};


void cadastrarMusica(struct Musica **playlist, int *contador);
void listarMusicas(struct Musica *playlist, int contador);
void buscarMusica(struct Musica *playlist, int contador, int id);
void editarMusica(struct Musica *playlist, int contador, int id);
void excluirMusica(struct Musica **playlist, int *contador, int id);

int main() {
    struct Musica *playlist = malloc(MAX_MUSICAS * sizeof(struct Musica)); 
    int contador = 0;
    int opcao, id;

    do {
        system("clear"); 
        printf("1. Cadastrar Música\n");
        printf("2. Listar Músicas\n");
        printf("3. Buscar Música por ID\n");
        printf("4. Editar Música\n");
        printf("5. Excluir Música\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        switch(opcao) {
            case 1:
                cadastrarMusica(&playlist, &contador);
                break;
            case 2:
                listarMusicas(playlist, contador);
                break;
            case 3:
                printf("Digite o ID da música a buscar: ");
                scanf("%d", &id);
                getchar(); 
                buscarMusica(playlist, contador, id);
                break;
            case 4:
                printf("Digite o ID da música a editar: ");
                scanf("%d", &id);
                editarMusica(playlist, contador, id);
                break;
            case 5:
                printf("Digite o ID da música a excluir: ");
                scanf("%d", &id);
                excluirMusica(&playlist, &contador, id);
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 6);

    free(playlist); 
    return 0;
}

void cadastrarMusica(struct Musica **playlist, int *contador) {
    if (*contador < MAX_MUSICAS) {
        printf("Digite o nome da música: ");
        getchar();  
        fgets((*playlist)[*contador].nome, sizeof((*playlist)[*contador].nome), stdin);
        (*playlist)[*contador].nome[strcspn((*playlist)[*contador].nome, "\n")] = 0; // Remove newline

        printf("Digite o artista: ");
        fgets((*playlist)[*contador].artista, sizeof((*playlist)[*contador].artista), stdin);
        (*playlist)[*contador].artista[strcspn((*playlist)[*contador].artista, "\n")] = 0; // Remove newline

        (*playlist)[*contador].id = *contador + 1; 
        (*contador)++;
        printf("Música cadastrada com sucesso!\n");
        getchar(); 
        system("clear"); 
    } else {
        printf("Playlist cheia!\n");
        getchar(); 
        system("clear"); 
    }
}

void listarMusicas(struct Musica *playlist, int contador) {
    for (int i = 0; i < contador; i++) {
        printf("ID: %d | Nome: %s | Artista: %s\n", playlist[i].id, playlist[i].nome, playlist[i].artista);
    }
    printf("Pressione Enter para continuar...");
    getchar(); 
    getchar(); 
    system("clear"); 
}

void buscarMusica(struct Musica *playlist, int contador, int id) {
    for (int i = 0; i < contador; i++) {
        if (playlist[i].id == id) {
            printf("Música encontrada:\nID: %d | Nome: %s | Artista: %s\n", playlist[i].id, playlist[i].nome, playlist[i].artista);
            return;
        }
    }
    printf("Música com ID %d não encontrada.\n", id);
}

void editarMusica(struct Musica *playlist, int contador, int id) {
    for (int i = 0; i < contador; i++) {
        if (playlist[i].id == id) {
            printf("Editando Música:\n");
            printf("Digite o novo nome da música: ");
            getchar();  
            fgets(playlist[i].nome, sizeof(playlist[i].nome), stdin);
            playlist[i].nome[strcspn(playlist[i].nome, "\n")] = 0; 

            printf("Digite o novo artista: ");
            fgets(playlist[i].artista, sizeof(playlist[i].artista), stdin);
            playlist[i].artista[strcspn(playlist[i].artista, "\n")] = 0; 

            printf("Música editada com sucesso!\n");
            getchar(); 
            system("clear"); 
            return;
        }
    }
    printf("Música com ID %d não encontrada.\n", id);
    getchar(); 
    system("clear"); 
}

void excluirMusica(struct Musica **playlist, int *contador, int id) {
    for (int i = 0; i < *contador; i++) {
        if ((*playlist)[i].id == id) {
            
            for (int j = i; j < *contador - 1; j++) {
                (*playlist)[j] = (*playlist)[j + 1];
            }
            (*contador)--; 
            printf("Música com ID %d excluída com sucesso!\n", id);
            getchar(); 
            system("clear"); 
            return;
        }
    }
    printf("Música com ID %d não encontrada.\n", id);
    getchar(); 
    system("clear"); 
}
