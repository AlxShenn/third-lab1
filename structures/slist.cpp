#include "slist.h"

#include <iostream>

void FInitializeSlist(Slist* slist) {
    slist->head = nullptr;
}

void FPushHead(Slist* slist, const string& value) {
    SlistNode* newNode = new SlistNode{value, slist->head};
    slist->head = newNode;

}

void FPushTail(Slist* slist, const string& value) {
    SlistNode* newNode = new SlistNode{value, nullptr};
    SlistNode* currentNode = slist->head;
    if (slist == nullptr) {
        slist->head = newNode;
        return;
    }
    while(currentNode->next != nullptr) {
        currentNode = currentNode->next;
    }

    currentNode->next = newNode;

}

void FPushAfter(SlistNode* currentNode, const string& value) {
    SlistNode* newNode = new SlistNode{value, currentNode->next};
    currentNode->next = newNode;
}

void FPushBefore(Slist* slist, SlistNode* target, const string& value) {
    if (target == nullptr || slist == nullptr) return;
    if (slist->head == target) {
        FPushHead(slist, value);
        return;
    }
    SlistNode* prev = slist->head;
    while (prev != nullptr && prev->next != target) {
        prev = prev->next;
    }
    if (prev == nullptr) return;
    FPushAfter(prev, value);
}

void FDeleteBefore(Slist* slist, SlistNode* target) {
    if (slist == nullptr || slist->head == nullptr || slist->head == target) return;
    if (slist->head->next == target) {
        FDeleteHead(slist);
        return;
    }
    SlistNode* prev = slist->head;
    while (prev->next != nullptr && prev->next->next != target) {
        prev = prev->next;
    }
    if (prev->next == nullptr || prev->next->next != target) return;
    FDeleteAfter(prev);
}

void FDeleteAfter(SlistNode* currentNode) {
    SlistNode* nodeToDelete = currentNode->next;
    currentNode->next = nodeToDelete->next;
    delete nodeToDelete;
}

void FDeleteHead( Slist* slist) {
    if (slist->head == nullptr) {
        return;
    }
    SlistNode* nodeToDelete = slist->head;
    slist->head = slist->head->next;
    delete nodeToDelete;
}

void FDeleteTail(Slist* slist) {
    if (slist->head->next == nullptr) {
        FDeleteHead(slist);
        return;
    }
    SlistNode* currentNode = slist->head;
    while (currentNode->next->next != nullptr) {
        currentNode = currentNode->next;
    }
    FDeleteAfter(currentNode);
}

void FDeleteValue(Slist* slist, const string& value) {
    if (slist->head == nullptr) return;
    if (slist->head->text == value) {
        FDeleteHead(slist);
        return;
    }
    SlistNode* currentNode = slist->head;
    while (currentNode->next != nullptr && currentNode->next->text != value) {
        currentNode = currentNode->next;
    }
    if (currentNode->next != nullptr) {
        FDeleteAfter(currentNode);
    }
}

void FFind(Slist* slist, const string& value) {
    SlistNode* currentNode = slist->head;
    while (currentNode != nullptr) {
        if (currentNode->text == value) {
            cout << value << "' index is " << currentNode << "\n";
            return;
        }
        currentNode = currentNode->next;
    }
    cout << "Couldn't find " << value << endl;
}

void FFree(Slist* slist) {
    while (slist->head != nullptr) {
        FDeleteHead(slist);
    }
}