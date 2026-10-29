#include <iostream>
#include "queue.h"

using namespace std;

void QInitializeQueue(Queue* queue) {
    queue->head = nullptr;
    queue->tail = nullptr;
}

bool QIsEmptyQueue(Queue* queue) {
    return queue->head == nullptr;
}

void QPush(Queue* queue, const string& value) {
    QueueNode* newNode = new QueueNode{value, nullptr};
    if (queue->tail == nullptr) {
        queue->head = newNode;
        queue->tail = newNode;

        return;
    } else {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
}

void QPop(Queue* queue) {
    if (QIsEmptyQueue(queue)) {
        cout << "No" << endl;
        return;
    }
    
    QueueNode* nodeToDelete = queue->head;
    string out = nodeToDelete->text;
    queue->head = nodeToDelete->next;
    if (queue->head == nullptr) {
        queue->tail = nullptr;
    }
    delete nodeToDelete;
    
    cout << "-> " << out << endl;
}

void QPrint(const Queue& queue) {
    if (queue.head == nullptr) {
        return;
    }
    for (const QueueNode* currentNode = queue.head; currentNode != nullptr; currentNode = currentNode->next) {
        cout << currentNode->text;
        if (currentNode->next != nullptr) {
            cout << " -> ";
        }
    }
    cout << endl;
}

void QFree(Queue& queue) {
    while (queue.head != nullptr) {
        QueueNode* nodeToDelete = queue.head;
        queue.head = nodeToDelete->next;
        delete nodeToDelete;
    }
    queue.tail = nullptr;
}