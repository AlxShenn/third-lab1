#ifndef QUEUE_H
#define QUEUE_H

#include <string>

using namespace std;

struct QueueNode{
    string text;
    QueueNode* next;
};

struct Queue{
    QueueNode* head;
    QueueNode* tail;
};

void QInitializeQueue(Queue* queue);
bool QIsEmptyQueue(Queue* queue);
void QPush(Queue* queue, const string& value);
void QPop(Queue* queue);
void QPrint(const Queue& queue);
void QFree(Queue& queue);

#endif