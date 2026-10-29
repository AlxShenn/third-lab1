package structures

import "fmt"

type QueueNode struct {
	Text string
	Next *QueueNode
}

type Queue struct {
	Head *QueueNode
	Tail *QueueNode
}

func QInitializeQueue(queue *Queue) {
	queue.Head = nil
	queue.Tail = nil
}

func QIsEmptyQueue(queue *Queue) bool {
	return queue.Head == nil
}

func QPush(queue *Queue, value string) {
	newNode := &QueueNode{Text: value, Next: nil}
	if queue.Tail == nil {
		queue.Head = newNode
		queue.Tail = newNode
		return
	}
	queue.Tail.Next = newNode
	queue.Tail = newNode
}

func QPop(queue *Queue) (string, bool) {
	if QIsEmptyQueue(queue) {
		return "", false
	}
	node := queue.Head
	queue.Head = node.Next
	if queue.Head == nil {
		queue.Tail = nil
	}
	return node.Text, true
}

func QPrint(queue *Queue) {
	if queue.Head == nil {
		return
	}
	for current := queue.Head; current != nil; current = current.Next {
		fmt.Print(current.Text)
		if current.Next != nil {
			fmt.Print(" -> ")
		}
	}
	fmt.Println()
}

func QFree(queue *Queue) {
	queue.Head = nil
	queue.Tail = nil
}