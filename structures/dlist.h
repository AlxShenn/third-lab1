#ifndef DLIST_H
#define DLIST_H

#include <string>

using namespace std;

struct DlistNode {
    string text;
    DlistNode* next;
    DlistNode* prev;
};

struct Dlist {
    DlistNode* head;
    DlistNode* tail;
};

void DPushHead(Dlist& dlist, const string& value);
void DPushTail(Dlist& dlist, const string& value);
void DPushAfter(Dlist& dlist, const string& value, const string& target);
void DPushBefore(Dlist& dlist, const string& value, const string& target);

void DDeleteHead(Dlist& dlist);
void DDeleteTail(Dlist& dlist);
void DDeleteAfter(Dlist& dlist, const string& target);
void DDeleteBefore(Dlist& dlist, const string& target);

void DPrintForward(Dlist& dlist);
void DPrintBackward(Dlist& dlist);

bool DFind(Dlist& dlist, const string& value);
void DDeleteValue(Dlist& dlist, const string& value);

void DFree(Dlist& dlist);

#endif
