#ifndef SlIST_H
#define SlIST_H

#include <string>

using namespace std;

struct SlistNode {
    string text;
    SlistNode* next;
};

struct Slist {
    SlistNode* head;
};

void FInitializeSlist( Slist* slist);
void FPushHead( Slist* slist, const string& value);
void FPushTail(Slist* slist, const string& value);
void FPushBefore( Slist* slist, SlistNode* target, const string& value);
void FPushAfter( SlistNode* currentNode, const string& value);

void FDeleteHead( Slist* slist);
void FDeleteTail(Slist* slist);
void FDeleteBefore(Slist* slist, SlistNode* target);
void FDeleteAfter(SlistNode* currentNode);
void FDeleteValue(Slist* slist, const string& value);

void FPrint(Slist* slist);
void FFree(Slist* slist);

#endif