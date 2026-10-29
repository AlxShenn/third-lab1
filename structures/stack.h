#ifndef STACK_H
#define STACK_H

#include <string>

using namespace std;

struct StackNode {
    string text;
    StackNode* next;
};

struct Stack {
    StackNode* head;
};

void SInitializeStack(Stack* stack);
bool SIsEmptyStack(Stack* stack);
void SPush(Stack* stack, const string& value);
void SPop(Stack& stack);
void SPrint(const Stack& stack);
void SFree(Stack& stack);

#endif
