#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // Para usar a função toupper()
#include <stdbool.h>
#include <unistd.h>
#include <string.h> 

#include "./passwordGenerate.h"
#include "../linearQueue/linearQueue.h"
#include "../circularQueue/circularQueue.h"

#define FILENAME "queue_data.csv"

void saveToCSV(int passCounter, LinearQueue *linearQueue, CircularQueue *circularQueue) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Erro: Não foi possível abrir o arquivo para salvar os dados.\n");
        return;
    }

    // 1. Salva o estado do contador global na primeira linha
    fprintf(file, "METADATA,%d,0\n", passCounter);

    // 2. Salva os elementos ativos da Fila Linear
    // Nota: Como os itens são removidos avançando o 'front', salvamos apenas os válidos
    for (int i = linearQueue->front; i <= linearQueue->rear; i++) {
        if (linearQueue->front <= linearQueue->rear) { // Garante que não está vazia
            fprintf(file, "LINEAR,%d,%c\n", linearQueue->itens[i].password, linearQueue->itens[i].priority[0]);
        }
    }

    // 3. Salva os elementos ativos da Fila Circular
    if (circularQueue->front != -1) { // Se não estiver vazia
        int i = circularQueue->front;
        while (1) {
            fprintf(file, "CIRCULAR,%d,%c\n", circularQueue->itens[i].password, circularQueue->itens[i].priority[0]);
            if (i == circularQueue->rear) break;
            i = (i + 1) % MAX;
        }
    }

    fclose(file);
    printf("\n[System] Dados salvos em %s!\n", FILENAME);
    sleep(2);
}

void loadFromCSV(int *passCounter, LinearQueue *linearQueue, CircularQueue *circularQueue) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("\n[System] Nenhum dado salvo encontrado (%s). Iniciando do zero.\n", FILENAME);
        sleep(2);
        return;
    }

    // Reinicializa as filas antes de carregar os dados do arquivo
    initializeQueue(linearQueue);
    initializeCircularQueue(circularQueue);

    char type[20];
    int password;
    char priority;

    // Lê o arquivo linha por linha
    while (fscanf(file, "%[^,],%d,%c\n", type, &password, &priority) != EOF) {
        if (strcmp(type, "METADATA") == 0) {
            *passCounter = password; // Restaura o contador global de senhas
        } 
        else if (strcmp(type, "LINEAR") == 0) {
            StructPassword temp;
            temp.password = password;
            temp.priority[0] = priority;
            
            // Insere direto no array para manter os índices originais simplificados
            linearQueue->rear++;
            linearQueue->itens[linearQueue->rear] = temp;
        } 
        else if (strcmp(type, "CIRCULAR") == 0) {
            StructPassword temp;
            temp.password = password;
            temp.priority[0] = priority;

            if (circularQueue->front == -1) circularQueue->front = 0;
            circularQueue->rear = (circularQueue->rear + 1) % MAX;
            circularQueue->itens[circularQueue->rear] = temp;
        }
    }

    fclose(file);
    printf("\n[System] Dados carregados com sucesso de %s!\n", FILENAME);
    sleep(2);
}

StructPassword createNewTicket(int *passCounter, LinearQueue *linearQueue, CircularQueue *circularQueue) {
    StructPassword novaSenha;
    char option;

    while (true) {
        system("clear");
        printf("\n--- GERADOR DE SENHAS ---\n");
        printf("Selecione o tipo de atendimento:\n");
        printf("[N] - Normal\n");
        printf("[P] - Preferencial\n");
        printf("Escolha uma opcao: ");
        
        scanf(" %c", &option); // O espaço antes do %c limpa quebras de linha anteriores
        option = toupper(option); // Transforma em maiúsculo para facilitar a validação

        switch (option) {
            case 'P':
                (*passCounter)++;
                novaSenha.password = *passCounter;
                novaSenha.priority[0] = 'P';
                enqueueCircular(circularQueue, novaSenha);
                sleep(2); 
                return novaSenha;
            case 'N':
                (*passCounter)++;
                novaSenha.password = *passCounter;
                novaSenha.priority[0] = 'N';
                enqueueLinear(linearQueue, novaSenha);
                sleep(2); 
                return novaSenha;
            default:
                printf("\nOpcao invalida! Por favor, digite apenas 'N' ou 'P'.\n");
                sleep(2); 
        }
    }
}

void callNextTicket(LinearQueue *linearQueue, CircularQueue *circularQueue) {
    static int normalCallsCounter = 0; 

    if (isQueueEmpty(linearQueue) && isCircularEmpty(circularQueue)) {
        printf("\n[Panel] No tickets waiting for service.\n");
        return;
    }

    StructPassword called;

    // Regra: A cada 2 chamadas de tickets normais, se houver tickets preferenciais na fila circular, chamar um ticket preferencial.
    if (normalCallsCounter >= 2) {
        if (!isCircularEmpty(circularQueue)) {
            called = dequeueCircular(circularQueue);
            printf("\n>>> PAINEL: Chamada para ticket Preferential %d (%c), apresente-se no balcão! <<<\n", called.password, called.priority[0]);
            normalCallsCounter = 0; 
            return;
        } else {
            printf("[Notice] Ticket não preferencial disponível. Chamando da fila normal...\n");
        }
    }

    if (!isQueueEmpty(linearQueue)) {
        called = dequeueLinear(linearQueue);
        printf("\n>>> PAINEL: Chamada para ticket Normal %d (%c), apresente-se no balcão! <<<\n", called.password, called.priority[0]);
        normalCallsCounter++; 
    } else {
        called = dequeueCircular(circularQueue);
        printf("\n>>> PANEL: Preferential Ticket %d (%c) go to counter! <<<\n", called.password, called.priority[0]);
        normalCallsCounter = 0; 
    }
}

