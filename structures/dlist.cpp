#include "dlist.h"

#include <iostream>

void DPushHead(DlistNode*& head, const string& value) {
    DlistNode* newNode = new DlistNode{value, head, nullptr};
    if (head != nullptr) head->prev = newNode;
    head = newNode;
}

void DPushTail(DlistNode*& head, const string& value) {
    DlistNode* newNode = new DlistNode{value, nullptr, nullptr};
    if (head == nullptr) {
        head = newNode;
        return;
    }
    DlistNode* currentNode = head;
    while (currentNode->next != nullptr) {
        currentNode = currentNode->next;
    }
    currentNode->next = newNode;
    newNode->prev = currentNode;
}

void DPushAfter(DlistNode* currentNode, const string& value) {
    DlistNode* newNode = new DlistNode{value, currentNode->next, currentNode};
    if (currentNode->next != nullptr) currentNode->next->prev = newNode;
    currentNode->next = newNode;
}

void DPushBefore(DlistNode* currentNode, const string& value) {
    DlistNode* newNode = new DlistNode{value, currentNode, currentNode->prev};
    if (currentNode->prev != nullptr) currentNode->prev->next = newNode;
    currentNode->prev = newNode;
}




void DDeleteHead(DlistNode*& head) {
    if (head == nullptr) return;
    DlistNode* nodeToDelete = head;
    head = head->next;
    if (head != nullptr) head->prev = nullptr;
    delete nodeToDelete;
}

void DDeleteTail(DlistNode*& head) {
    if (head == nullptr) return;
    if (head->next == nullptr) {
        DDeleteHead(head);
        return;
    }
    DlistNode* currentNode = head;
    while (currentNode->next != nullptr) {
        currentNode = currentNode->next;
    }
    currentNode->prev->next = nullptr;
    delete currentNode;
}

void DDeleteAfter(DlistNode* currentNode) {
    DlistNode* nodeToDelete = currentNode->next;
    if (nodeToDelete == nullptr) return;
    currentNode->next = nodeToDelete->next;
    if (nodeToDelete->next != nullptr) nodeToDelete->next->prev = currentNode;
    delete nodeToDelete;
}

void DDeleteBefore(DlistNode* currentNode) {
    DlistNode* nodeToDelete = currentNode->prev;
    if (nodeToDelete == nullptr) return;
    currentNode->prev = nodeToDelete->prev;
    if (nodeToDelete->prev != nullptr) nodeToDelete->prev->next = currentNode;
    delete nodeToDelete;
}





void DPrintForward(DlistNode* head) {
    for (DlistNode* currentNode = head; currentNode != nullptr; currentNode = currentNode->next) {
        cout << currentNode->text << " ";
    }
    cout << "\n";
}

void DPrintBackward(DlistNode* head) {
    if (head == nullptr) return;
    DlistNode* currentNode = head;
    while (currentNode->next != nullptr) {
        currentNode = currentNode->next;
    }
    for (; currentNode != nullptr; currentNode = currentNode->prev) {
        cout << currentNode->text << " ";
    }
    cout << "\n";
}





DlistNode* DFind(DlistNode* head, const string& value) {
    for (DlistNode* currentNode = head; currentNode != nullptr; currentNode = currentNode->next) {
        if (currentNode->text == value) return currentNode;
    }
    return nullptr;
}

void DDeleteValue(DlistNode*& head, const string& value) {
    DlistNode* target = DFind(head, value);
    if (target == nullptr) return;
    if (target->prev == nullptr) {
        DDeleteHead(head);
        return;
    }
    DDeleteAfter(target->prev);
}

void DFree(DlistNode*& head) {
    while (head != nullptr) {
        DlistNode* nodeToDelete = head;
        head = head->next;
        delete nodeToDelete;
    }
}