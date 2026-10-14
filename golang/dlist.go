package main

import "fmt"

type DlistNode struct {
	text string
	next *DlistNode
	prev *DlistNode
}

func DPushHead(head *DlistNode, value string) *DlistNode {
	newNode := &DlistNode{text: value, next: head}
	if head != nil {
		head.prev = newNode
	}
	return newNode
}

func DPushTail(head *DlistNode, value string) *DlistNode {
	newNode := &DlistNode{text: value}
	if head == nil {
		return newNode
	}
	current := head
	for current.next != nil {
		current = current.next
	}
	current.next = newNode
	newNode.prev = current
	return head
}

func DPushAfter(currentNode *DlistNode, value string) {
	newNode := &DlistNode{text: value, next: currentNode.next, prev: currentNode}
	if currentNode.next != nil {
		currentNode.next.prev = newNode
	}
	currentNode.next = newNode
}

func DPushBefore(currentNode *DlistNode, value string) {
	newNode := &DlistNode{text: value, next: currentNode, prev: currentNode.prev}
	if currentNode.prev != nil {
		currentNode.prev.next = newNode
	}
	currentNode.prev = newNode
}

func DDeleteHead(head *DlistNode) *DlistNode {
	if head == nil {
		return nil
	}
	newHead := head.next
	if newHead != nil {
		newHead.prev = nil
	}
	return newHead
}

func DDeleteTail(head *DlistNode) *DlistNode {
	if head == nil {
		return nil
	}
	if head.next == nil {
		return DDeleteHead(head)
	}
	current := head
	for current.next != nil {
		current = current.next
	}
	current.prev.next = nil
	return head
}

func DDeleteAfter(currentNode *DlistNode) {
	nodeToDelete := currentNode.next
	if nodeToDelete == nil {
		return
	}
	currentNode.next = nodeToDelete.next
	if nodeToDelete.next != nil {
		nodeToDelete.next.prev = currentNode
	}
}

func DDeleteBefore(currentNode *DlistNode) {
	nodeToDelete := currentNode.prev
	if nodeToDelete == nil {
		return
	}
	currentNode.prev = nodeToDelete.prev
	if nodeToDelete.prev != nil {
		nodeToDelete.prev.next = currentNode
	}
}

func DPrintForward(head *DlistNode) {
	for current := head; current != nil; current = current.next {
		fmt.Print(current.text, " ")
	}
	fmt.Print("\n")
}

func DPrintBackward(head *DlistNode) {
	if head == nil {
		return
	}
	current := head
	for current.next != nil {
		current = current.next
	}
	for ; current != nil; current = current.prev {
		fmt.Print(current.text, " ")
	}
	fmt.Print("\n")
}

func DFind(head *DlistNode, value string) *DlistNode {
	for current := head; current != nil; current = current.next {
		if current.text == value {
			return current
		}
	}
	return nil
}

func DDeleteValue(head *DlistNode, value string) *DlistNode {
	target := DFind(head, value)
	if target == nil {
		return head
	}
	if target.prev == nil {
		return DDeleteHead(head)
	}
	DDeleteAfter(target.prev)
	return head
}

func DFree(head *DlistNode) {
	for head != nil {
		head = head.next
	}
}
