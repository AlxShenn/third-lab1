#ifndef DLIST_H
#define DLIST_H

#include <string>

using namespace std;

struct DlistNode {
    string text;
    DlistNode* next;
    DlistNode* prev;
};

void DPushHead(DlistNode*& head, const string& value);
void DPushTail(DlistNode*& head, const string& value);
void DPushAfter(DlistNode* currentNode, const string& value);
void DPushBefore(DlistNode* currentNode, const string& value);

void DDeleteHead(DlistNode*& head);
void DDeleteTail(DlistNode*& head);
void DDeleteAfter(DlistNode* currentNode);
void DDeleteBefore(DlistNode* currentNode);

void DPrintForward(DlistNode* head);
void DPrintBackward(DlistNode* head);

DlistNode* DFind(DlistNode* head, const string& value);
void DDeleteValue(DlistNode*& head, const string& value);

void DFree(DlistNode*& head);

#endif
