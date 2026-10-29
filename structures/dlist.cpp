#include "dlist.h"

#include <iostream>

void DInitialize(Dlist& dlist) {
    dlist.head = nullptr;
    dlist.tail = nullptr;
}

void DPushHead(Dlist& dlist, const string& value) {
    DlistNode* newNode = new DlistNode{value, dlist.head, nullptr};
    if (dlist.head == nullptr) {
        dlist.head = newNode;
        dlist.tail = newNode;
        return;
    }
    dlist.head->prev = newNode;
    dlist.head = newNode;
}

void DPushTail(Dlist& dlist, const string& value) {
    DlistNode* newNode = new DlistNode{value, nullptr, dlist.tail};
    if (dlist.tail == nullptr) {
        dlist.head = newNode;
        dlist.tail = newNode;
        return;
    }
    dlist.tail->next = newNode;
    dlist.tail = newNode;
}

void DPushAfter(Dlist& dlist, const string& value, const string& target) {
    if (dlist.head == nullptr) return;

    DlistNode* current = dlist.head;
    while (current != nullptr && current->text != target) {
        current = current->next;
    }
    if (current == nullptr) return;

    DlistNode* nxt = current->next;
    DlistNode* newNode = new DlistNode{value, nxt, current};
    current->next = newNode;
    if (nxt != nullptr) {
        nxt->prev = newNode;
    } else {
        dlist.tail = newNode;
    }
}

void DPushBefore(Dlist& dlist, const string& value, const string& target) {
    if (dlist.head == nullptr) return;

    DlistNode* current = dlist.head;
    while (current != nullptr && current->text != target) {
        current = current->next;
    }
    if (current == nullptr) return;


    DlistNode* prv = current->prev;
    DlistNode* newNode = new DlistNode{value, current, prv};
    current->prev = newNode;
    if (prv != nullptr) {
        prv->next = newNode;
    } else {
        dlist.head = newNode;
    }
}

void DDeleteHead(Dlist& dlist) {
    if (dlist.head == nullptr) return;

    DlistNode* delNode = dlist.head;
    dlist.head = delNode->next;

    if (dlist.head != nullptr) {
        dlist.head->prev = nullptr;
    } else {
        dlist.tail = nullptr;
    }
    delete delNode;
}

void DDeleteTail(Dlist& dlist) {
    if (dlist.tail == nullptr) return;

    DlistNode* delNode = dlist.tail;
    dlist.tail = delNode->prev;
    if (dlist.tail != nullptr) {
        dlist.tail->next = nullptr;
    } else {
        dlist.head = nullptr;
    }
    delete delNode;
}

void DDeleteAfter(Dlist& dlist, const string& target) {
    if (dlist.head == nullptr) return;

    DlistNode* current = dlist.head;
    while (current != nullptr && current->text != target) {
        current = current->next;
    }
    if (current == nullptr || current->next == nullptr) return;

    DlistNode* delNode = current->next;
    DlistNode* nxt = delNode->next;
    current->next = nxt;
    if (nxt != nullptr) {
        nxt->prev = current;
    } else {
        dlist.tail = current;
    }
    delete delNode;
}

void DDeleteBefore(Dlist& dlist, const string& target) {
    if (dlist.head == nullptr) return;

    DlistNode* current = dlist.head;
    while (current != nullptr && current->text != target) {
        current = current->next;
    }
    if (current == nullptr || current->prev == nullptr) return;

    DlistNode* delNode = current->prev;
    DlistNode* prv = delNode->prev;
    current->prev = prv;
    if (prv != nullptr) {
        prv->next = current;
    } else {
        dlist.head = current;
    }
    delete delNode;
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
    if (dlist.tail == nullptr) {
        cout << "Dlist is empty." << endl;
        return;
    }
    for (DlistNode* currentNode = dlist.tail; currentNode != nullptr; currentNode = currentNode->prev) {
        cout << currentNode->text << " ";
    }
    cout << "\n";
}

bool DFind(Dlist& dlist, const string& value) {
    for (DlistNode* currentNode = dlist.head; currentNode != nullptr; currentNode = currentNode->next) {
        if (currentNode->text == value) return true;
    }
    return false;
}

void DDeleteValue(Dlist& dlist, const string& value) {
    if (dlist.head == nullptr) return;

    DlistNode* current = dlist.head;
    while (current != nullptr && current->text != value) {
        current = current->next;
    }
    if (current == nullptr) return;

    if (current->prev != nullptr) {
        current->prev->next = current->next;
    } else {
        dlist.head = current->next;
    }
    if (current->next != nullptr) {
        current->next->prev = current->prev;
    } else {
        dlist.tail = current->prev;
    }
    delete current;
}

void DFree(Dlist& dlist) {
    DlistNode* current = dlist.head;
    while (current != nullptr) {
        DlistNode* nodeToDelete = current;
        current = current->next;
        delete nodeToDelete;
    }
    dlist.head = nullptr;
    dlist.tail = nullptr;
}