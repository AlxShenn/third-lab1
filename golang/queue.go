package main

import "fmt"

type QueueNode struct {
	text string
	next *QueueNode
}

type Queue struct {
	head *QueueNode
	tail *QueueNode
}

func QInitializeQueue(queue *Queue) {
	queue.head = nil
	queue.tail = nil
}

func QIsEmptyQueue(queue *Queue) bool {
	return queue.head == nil
}

func QPush(queue *Queue, value string) {
	newNode := &QueueNode{text: value}
	if queue.tail == nil {
		queue.head = newNode
		queue.tail = newNode
		return
	}
	queue.tail.next = newNode
	queue.tail = newNode
}

func QPop(queue *Queue) (string, bool) {
	if QIsEmptyQueue(queue) {
		return "", false
	}
	value := queue.head.text
	queue.head = queue.head.next
	if queue.head == nil {
		queue.tail = nil
	}
	return value, true
}

func QPrint(queue *Queue) {
	if queue.head == nil {
		return
	}
	for current := queue.head; current != nil; current = current.next {
		fmt.Print(current.text)
		if current.next != nil {
			fmt.Print(" -> ")
		}
	}
	fmt.Println()
}

func QFree(queue *Queue) {
	for queue.head != nil {
		queue.head = queue.head.next
	}
	queue.tail = nil
}
