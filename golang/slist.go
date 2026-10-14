package main

import "fmt"

type SlistNode struct {
	text string
	next *SlistNode
}

type Slist struct {
	head *SlistNode
}

func FInitializeSlist(s *Slist) {
	s.head = nil
}

func FPushHead(s *Slist, value string) {
	s.head = &SlistNode{text: value, next: s.head}
}

func FPushTail(s *Slist, value string) {
	newNode := &SlistNode{text: value}
	if s.head == nil {
		s.head = newNode
		return
	}
	current := s.head
	for current.next != nil {
		current = current.next
	}
	current.next = newNode
}

func FPushBefore(previousNode *SlistNode, value string) {
	previousNode.next = &SlistNode{text: value, next: previousNode.next}
}

func FPushAfter(currentNode *SlistNode, value string) {
	currentNode.next = &SlistNode{text: value, next: currentNode.next}
}

func FDeleteBefore(previousNode *SlistNode) {
	if previousNode.next == nil {
		return
	}
	previousNode.next = previousNode.next.next
}

func FDeleteAfter(currentNode *SlistNode) {
	if currentNode.next == nil {
		return
	}
	currentNode.next = currentNode.next.next
}

func FDeleteHead(s *Slist) {
	if s.head == nil {
		return
	}
	s.head = s.head.next
}

func FDeleteTailForSlist(s *Slist) {
	if s.head == nil {
		return
	}
	if s.head.next == nil {
		FDeleteHead(s)
		return
	}
	current := s.head
	for current.next.next != nil {
		current = current.next
	}
	FDeleteAfter(current)
}

func FDeleteValue(s *Slist, value string) {
	if s.head == nil {
		return
	}
	if s.head.text == value {
		FDeleteHead(s)
		return
	}
	current := s.head
	for current.next != nil && current.next.text != value {
		current = current.next
	}
	if current.next != nil {
		FDeleteAfter(current)
	}
}

func FFind(s *Slist, value string) {
	for current := s.head; current != nil; current = current.next {
		if current.text == value {
			fmt.Printf("%v' index is %p\n", value, current)
			return
		}
	}
	fmt.Println("Couldn't find", value)
}

func FFree(s *Slist) {
	for s.head != nil {
		FDeleteHead(s)
	}
}
