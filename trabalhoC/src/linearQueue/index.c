#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../include/type.h"
#include "linearQueue.h"

#define MAX 5

bool isQueueFull(LinearQueue *queue) {
    return queue->rear == MAX - 1;
}

bool isQueueEmpty(LinearQueue *queue) {
    return queue->front > queue->rear;
}

void enqueueLinear(LinearQueue *queue, StructPassword element) {
    if(isQueueFull(queue)) {
        system("clear");
        printf("Erro: A fila atingiu o limite do array!\n");
        return;
    }
    
    queue->rear++;
    queue->itens[queue->rear] = element;

    printf("Senha %d (%c) enfileirada na posicao [%d]!\n", element.password, element.priority[0], queue->rear);
}

StructPassword dequeueLinear(LinearQueue *queue) {
    if(isQueueEmpty(queue)) {
        system("clear");
        printf("Erro: A fila está vazia!!\n");
        StructPassword erro = {-1, 'E'};
        return erro;
    }
    
    StructPassword frontElement = queue->itens[queue->front];
    queue->front++;
    return frontElement;
}

void initializeQueue(LinearQueue *queue) {
    queue->front = 0;
    queue->rear = -1;
}

void showQueue(LinearQueue *queue) {
    if(isQueueEmpty(queue)) {
        printf("A fila está vazia! \n");
        return;
    }
    
    printf("Fila atual:\n");
    for(int i = queue->front; i <= queue->rear; i++) {
        printf(" [%d] Senha: %d | Prioridade: %c\n", i, queue->itens[i].password, queue->itens[i].priority[0]);
    }
    printf("\n");
}
