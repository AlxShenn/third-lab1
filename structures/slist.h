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

void FInitializeSlist( Slist& slist);
void FPushHead( Slist& slist, const string& value);
void FPushTail(Slist& slist, const string& value);
void FPushBefore( Slist& slist, const string& target, const string& value);
void FPushAfter( Slist& slist, const string& target, const string& value);

void FDeleteHead( Slist& slist);
void FDeleteTail(Slist& slist);
void FDeleteBefore(Slist& slist, const string& target);
void FDeleteAfter(Slist& slist, const string& target);
void FDeleteValue(Slist& slist, const string& value);

bool FGet(Slist& slist, const string& value);
void FPrint(Slist& slist);
void FFree(Slist& slist);

#endif