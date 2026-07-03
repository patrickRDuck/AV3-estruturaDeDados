#ifndef FILA_H
#define FILA_H

#include <stdbool.h>
#include "../include/type.h"

#define MAX 5

typedef struct {
    StructPassword itens[MAX];
    int front;
    int rear;
} LinearQueue;

void initializeQueue(LinearQueue *queue);
bool isQueueFull(LinearQueue *queue);
bool isQueueEmpty(LinearQueue *queue);
void enqueueLinear(LinearQueue *queue, StructPassword element);
StructPassword dequeueLinear(LinearQueue *queue);
void showQueue(LinearQueue *queue);

#endif 