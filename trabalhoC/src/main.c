#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "./linearQueue/linearQueue.h"
#include "./circularQueue/circularQueue.h"
#include "../include/type.h"
#include "./ticketManager/passwordGenerate.h"

// gcc src/main.c src/circularQueue/index.c src/linearQueue/index.c src/ticketManager/index.c -I include -I src/circularQueue -I src/linearQueue -I src/ticketManager -o sistema

int main() {
    LinearQueue normalQueue;
    CircularQueue preferentialQueue;
    
    initializeQueue(&normalQueue);
    initializeCircularQueue(&preferentialQueue);
    
    int globalCounter = 0;
    int option;

    // Tenta carregar dados salvos automaticamente ao iniciar o sistema
    loadFromCSV(&globalCounter, &normalQueue, &preferentialQueue);

    do {
        system("clear");
        printf("\n======= SISTEMA DE FILAS =======\n");
        printf("1. Emitir Nova Senha\n");
        printf("2. Chamar Próxima Senha\n");
        printf("3. Exibir filas\n");
        printf("4. Salvar em CSV\n");
        printf("5. Carregar dados do CSV\n");
        printf("0. Encerrar programa\n");
        printf("Escolha: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                system("clear");
                createNewTicket(&globalCounter, &normalQueue, &preferentialQueue);
                sleep(3);
                break;
            case 2:
                system("clear");
                callNextTicket(&normalQueue, &preferentialQueue);
                sleep(3);
                break;
            case 3:
                system("clear");
                printf("\n--- FILAS ---\n");
                showQueue(&normalQueue);
                showCircularQueue(&preferentialQueue);
                sleep(3);
                break;
            case 4:
                saveToCSV(globalCounter, &normalQueue, &preferentialQueue);
                break;
            case 5:
                loadFromCSV(&globalCounter, &normalQueue, &preferentialQueue);
                break;
            case 0:
                system("clear");
                printf("Encerrando o sistema...\n");
                sleep(1);
                break;
            default:
                printf("Escolha inválida.\n");
        }
    } while (option != 0);

    return 0;
}