#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../include/type.h"
#include "circularQueue.h" 

// Enquanto o numerador for menor que o denominador(MAX), o resto sempre será o próprio numerador. Quando o numerador for igual ao denominador, o resto será 0. E quando o numerador for maior que o denominador, o resto será o valor do numerador menos o denominador.

void initializeCircularQueue(CircularQueue *queue) {
    queue->front = -1;
    queue->rear = -1;
}

bool isCircularFull(CircularQueue *queue) {
    // A fila circular está cheia se o próximo passo do rear encontrar o front // top ser 0
    return ((queue->rear + 1) % MAX == queue->front);
}

bool isCircularEmpty(CircularQueue *queue) {
    return (queue->front == -1);
}

void enqueueCircular(CircularQueue *queue, StructPassword element) {
    if (isCircularFull(queue)) {
        printf("Erro: A fila circular está cheia!\n");
        return;
    }

    if (isCircularEmpty(queue)) {
        queue->front = 0;
    }

    queue->rear = (queue->rear + 1) % MAX;
    queue->itens[queue->rear] = element;

    printf("Senha %d (%c) enfileirada na posicao [%d]!\n", element.password, element.priority[0], queue->rear);
}

StructPassword dequeueCircular(CircularQueue *queue) {
    if (isCircularEmpty(queue)) {
        printf("Erro: A fila circular está vazia!!\n");
        StructPassword erro = {-1, {'E'}};
        return erro;
    }

    StructPassword frontElement = queue->itens[queue->front];

    // Se a fila tinha apenas um único elemento, ela volta ao estado inicial
    if (queue->front == queue->rear) {
        queue->front = -1;
        queue->rear = -1;
    } else {
        // Avanço circular do ponteiro front
        queue->front = (queue->front + 1) % MAX;
    }

    return frontElement;
}

void showCircularQueue(CircularQueue *queue) {
    if (isCircularEmpty(queue)) {
        printf("A fila circular está vazia!\n");
        return;
    }

    printf("Fila Circular Atual:\n");
    int i = queue->front;
    while (true) {
        printf("  [%d] Senha: %d | Prioridade: %c\n", 
                i, queue->itens[i].password, queue->itens[i].priority[0]);
        
        if (i == queue->rear) {
            break;
        }
        i = (i + 1) % MAX; // Avanço circular para a varredura do print
    }
    printf("\n");
}