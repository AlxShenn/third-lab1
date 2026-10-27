#include "dlist.h"

#include <iostream>

void DPushHead(Dlist& dlist, const string& value) {
    if (dlist.head == nullptr) {
        DlistNode* newNode = new DlistNode{value, nullptr, nullptr};
        dlist.head = newNode;
        dlist.tail = newNode;
        return;
    }
    DlistNode* newNode = new DlistNode{value, dlist.head, nullptr};
    dlist.head->prev = newNode;
    dlist.head = newNode;
}

void DPushTail(Dlist& dlist, const string& value) {
    if (dlist.head == nullptr) {
        DlistNode* newNode = new DlistNode{value, nullptr, nullptr};
        dlist.head = newNode;
        dlist.tail = newNode;
        return;
    }
    DlistNode* newNode = new DlistNode{value, nullptr, dlist.tail};
    dlist.tail->next = newNode;
    dlist.tail = newNode;
}

void DPushAfter(Dlist& dlist, const string& value, const string& target) {
    if (dlist.head == nullptr) return;
    if (dlist.tail->text == target) { 
        DPushTail(dlist, value);
        return;
    }
    DlistNode* current = dlist.head;
    while (current != nullptr && current->text != target) {
        current = current->next;
    }
    if (current != nullptr) {
        DlistNode* newNode = new DlistNode{value, current->next, current};
        current->next = newNode; newNode->next->prev = newNode;
    }
}

void DPushBefore(Dlist& dlist, const string& value, const string& target) {
    if (dlist.head == nullptr) return;
    if (dlist.head->text == target) { 
        DPushHead(dlist, value);
        return;
    }
    DlistNode* current = dlist.head;
    while (current != nullptr && current->text != target) {
        current = current->next;
    }
    if (current != nullptr) {
        DlistNode* newNode = new DlistNode{value, current, current->prev};
        current->prev = newNode; newNode->prev->next = newNode;
    }
}

void DDeleteHead(Dlist& dlist) {
    if (dlist.head == nullptr) return;
    DlistNode* delNode = dlist.head;
    delNode->next->prev = nullptr;
    dlist.head = delNode->next;
    delete delNode;
}

void DDeleteTail(Dlist& dlist) {
    if (dlist.head == nullptr) return;
    DlistNode* delNode = dlist.tail;
    delNode->prev->next = nullptr;
    dlist.tail = delNode->prev;
    delete delNode;
}

void DDeleteAfter(Dlist& dlist, const string& target) {
    if (dlist.head == nullptr) return;
    if (dlist.tail->text == target) return;
    if (dlist.tail->prev->text == target) {
        DDeleteTail(dlist);
        return;
    }
    DlistNode* current = dlist.tail;
    while (current->prev != nullptr && current->prev->text != target) {
        current = current->prev;
    }
    if (current->prev != nullptr) {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
    }
}

void DDeleteBefore(Dlist& dlist, const string& target) {
    if (dlist.head == nullptr) return;
    if (dlist.head->text == target) return;
    if (dlist.head->next->text == target) {
        DDeleteHead(dlist);
        return;
    }
    DlistNode* current = dlist.head;
    while (current->next != nullptr && current->next->text != target) {
        current = current->next;
    }
    if (current->next != nullptr) {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
    }
}

void DPrintForward(Dlist& dlist) {
    if (dlist.head == nullptr) {
        cout << "Dlist is empty." << endl;
        return;
    }
    for (DlistNode* currentNode = dlist.head; currentNode != nullptr; currentNode = currentNode->next) {
        cout << currentNode->text << " ";
    }
    cout << "\n";
}

void DPrintBackward(Dlist& dlist) {
    if (dlist.head == nullptr) {
        cout << "Dlist is empty." << endl;
        return;
    }
    for (DlistNode* currentNode = dlist.tail; currentNode != nullptr; currentNode = currentNode->prev) {
        cout << currentNode->text << " ";
    }
    cout << "\n";
}

bool DFind(Dlist& dlist, const string& value) {
    if (dlist.head == nullptr) return false;
    if (dlist.head->text == value || dlist.tail->text == value) return true;
    for (DlistNode* currentNode = dlist.head; currentNode != nullptr; currentNode = currentNode->next) {
        if (currentNode->text == value) return true;
    }
    return false;
}

void DDeleteValue(Dlist& dlist, const string& value) {
    if (dlist.head == nullptr) return;
    if (dlist.head->text == value) {
        DDeleteHead(dlist); return;
    }
    if (dlist.tail->text == value) {
        DDeleteTail(dlist); return;
    }
    DlistNode* current = dlist.head;
    while (current != nullptr && current->text != value) {
        current = current->next;
    }
    if (current != nullptr) {
        current->next->prev = current->prev;
        current->prev->next = current->next;
        delete current;
    }
}

void DFree(Dlist& dlist) {
    if (dlist.head == nullptr) return;
    while (dlist.head != nullptr) {
        DlistNode* nodeToDelete = dlist.head;
        dlist.head = dlist.head->next;
        delete nodeToDelete;
    }
}