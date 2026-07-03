#ifndef PASSWORD_H
#define PASSWORD_H

#include "../../include/type.h"
#include "../linearQueue/linearQueue.h"
#include "../circularQueue/circularQueue.h"

StructPassword createNewTicket(int *passCounter, LinearQueue *linearQueue, CircularQueue *circularQueue);
void callNextTicket(LinearQueue *linearQueue, CircularQueue *circularQueue);

void saveToCSV(int passCounter, LinearQueue *linearQueue, CircularQueue *circularQueue);
void loadFromCSV(int *passCounter, LinearQueue *linearQueue, CircularQueue *circularQueue);

#endif 