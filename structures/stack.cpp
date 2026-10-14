#include <iostream>
#include "stack.h"

using namespace std;

void SInitializeStack(Stack* stack) {
	stack->head = nullptr;
}

bool SIsEmptyStack(Stack* stack) {
	return stack-> head == nullptr;
}

void SPush( Stack* stack, const string& value) {
	StackNode* newNode = new StackNode{value, nullptr};
	newNode->next = stack->head;
	stack->head = newNode;
}

void SPop(Stack& stack) {
	if (SIsEmptyStack(&stack)) {
		return;

	} else {
		StackNode* newHead = stack.head->next;
		delete stack.head;
		stack.head = newHead;
	}
}

void SPrint(const Stack& stack) {
	if (stack.head == nullptr) {
		return;
	}
	for (const StackNode* currentNode = stack.head; currentNode != nullptr; currentNode = currentNode->next) {
		cout << currentNode->text;
		if ( currentNode->next != nullptr) {
			cout << " -> ";
		}
	}

	cout << endl;

}

void SFree(Stack& stack) {
	while (stack.head != nullptr) {
		StackNode* nodeToDelete = stack.head;
		stack.head = nodeToDelete->next;
		delete nodeToDelete;
	}
}