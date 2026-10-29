package structures

import "fmt"

type StackNode struct {
	Text string
	Next *StackNode
}

type Stack struct {
	Head *StackNode
}

func SInitializeStack(stack *Stack) {
	stack.Head = nil
}

func SIsEmptyStack(stack *Stack) bool {
	return stack.Head == nil
}

func SPush(stack *Stack, value string) {
	newNode := &StackNode{Text: value, Next: stack.Head}
	stack.Head = newNode
}

// SPop возвращает (значение, true) если был элемент, иначе ("", false)
func SPop(stack *Stack) (string, bool) {
	if SIsEmptyStack(stack) {
		return "", false
	}
	node := stack.Head
	stack.Head = node.Next
	return node.Text, true
}

func SPrint(stack *Stack) {
	if stack.Head == nil {
		return
	}
	for current := stack.Head; current != nil; current = current.Next {
		fmt.Print(current.Text)
		if current.Next != nil {
			fmt.Print(" -> ")
		}
	}
	fmt.Println()
}

func SFree(stack *Stack) {
	stack.Head = nil
}