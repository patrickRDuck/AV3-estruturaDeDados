#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <stdbool.h>
#include "../../include/type.h"

#define MAX 5

typedef struct {
    StructPassword itens[MAX];
    int front;
    int rear;
} CircularQueue;


void initializeCircularQueue(CircularQueue *queue);
bool isCircularFull(CircularQueue *queue);
bool isCircularEmpty(CircularQueue *queue);
void enqueueCircular(CircularQueue *queue, StructPassword element);
StructPassword dequeueCircular(CircularQueue *queue);
void showCircularQueue(CircularQueue *queue);

#endif