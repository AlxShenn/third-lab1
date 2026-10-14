package main

import "fmt"

type StackNode struct {
	text string
	next *StackNode
}

type Stack struct {
	head *StackNode
}

func SInitializeStack(stack *Stack) {
	stack.head = nil
}

func SIsEmptyStack(stack *Stack) bool {
	return stack.head == nil
}

func SPush(stack *Stack, value string) {
	stack.head = &StackNode{text: value, next: stack.head}
}

func SPop(stack *Stack) (string, bool) {
	if SIsEmptyStack(stack) {
		return "", false
	}
	value := stack.head.text
	stack.head = stack.head.next
	return value, true
}

func SPrint(stack *Stack) {
	if stack.head == nil {
		return
	}
	for current := stack.head; current != nil; current = current.next {
		fmt.Print(current.text)
		if current.next != nil {
			fmt.Print(" -> ")
		}
	}
	fmt.Println()
}

func SFree(stack *Stack) {
	for stack.head != nil {
		stack.head = stack.head.next
	}
}
