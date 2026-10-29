package structures

import "fmt"

type DlistNode struct {
	Text string
	Next *DlistNode
	Prev *DlistNode
}

type Dlist struct {
	Head *DlistNode
	Tail *DlistNode
}

func DInitialize(dlist *Dlist) {
	dlist.Head = nil
	dlist.Tail = nil
}

func DPushHead(dlist *Dlist, value string) {
	newNode := &DlistNode{Text: value, Next: dlist.Head, Prev: nil}
	if dlist.Head == nil {
		dlist.Head = newNode
		dlist.Tail = newNode
		return
	}
	dlist.Head.Prev = newNode
	dlist.Head = newNode
}

func DPushTail(dlist *Dlist, value string) {
	newNode := &DlistNode{Text: value, Next: nil, Prev: dlist.Tail}
	if dlist.Tail == nil {
		dlist.Head = newNode
		dlist.Tail = newNode
		return
	}
	dlist.Tail.Next = newNode
	dlist.Tail = newNode
}

func DPushAfter(dlist *Dlist, value, target string) {
	current := dlist.Head
	for current != nil && current.Text != target {
		current = current.Next
	}
	if current == nil {
		return
	}
	nxt := current.Next
	newNode := &DlistNode{Text: value, Next: nxt, Prev: current}
	current.Next = newNode
	if nxt != nil {
		nxt.Prev = newNode
	} else {
		dlist.Tail = newNode
	}
}

func DPushBefore(dlist *Dlist, value, target string) {
	current := dlist.Head
	for current != nil && current.Text != target {
		current = current.Next
	}
	if current == nil {
		return
	}
	prv := current.Prev
	newNode := &DlistNode{Text: value, Next: current, Prev: prv}
	current.Prev = newNode
	if prv != nil {
		prv.Next = newNode
	} else {
		dlist.Head = newNode
	}
}

func DDeleteHead(dlist *Dlist) {
	if dlist.Head == nil {
		return
	}
	dlist.Head = dlist.Head.Next
	if dlist.Head != nil {
		dlist.Head.Prev = nil
	} else {
		dlist.Tail = nil
	}
}

func DDeleteTail(dlist *Dlist) {
	if dlist.Tail == nil {
		return
	}
	dlist.Tail = dlist.Tail.Prev
	if dlist.Tail != nil {
		dlist.Tail.Next = nil
	} else {
		dlist.Head = nil
	}
}

func DDeleteAfter(dlist *Dlist, target string) {
	current := dlist.Head
	for current != nil && current.Text != target {
		current = current.Next
	}
	if current == nil || current.Next == nil {
		return
	}
	delNode := current.Next
	nxt := delNode.Next
	current.Next = nxt
	if nxt != nil {
		nxt.Prev = current
	} else {
		dlist.Tail = current
	}
}

func DDeleteBefore(dlist *Dlist, target string) {
	current := dlist.Head
	for current != nil && current.Text != target {
		current = current.Next
	}
	if current == nil || current.Prev == nil {
		return
	}
	delNode := current.Prev
	prv := delNode.Prev
	current.Prev = prv
	if prv != nil {
		prv.Next = current
	} else {
		dlist.Head = current
	}
}

func DDeleteValue(dlist *Dlist, value string) {
	current := dlist.Head
	for current != nil && current.Text != value {
		current = current.Next
	}
	if current == nil {
		return
	}
	if current.Prev != nil {
		current.Prev.Next = current.Next
	} else {
		dlist.Head = current.Next
	}
	if current.Next != nil {
		current.Next.Prev = current.Prev
	} else {
		dlist.Tail = current.Prev
	}
}

func DFind(dlist *Dlist, value string) bool {
	for current := dlist.Head; current != nil; current = current.Next {
		if current.Text == value {
			return true
		}
	}
	return false
}

func DPrintForward(dlist *Dlist) {
	if dlist.Head == nil {
		fmt.Println("Dlist is empty.")
		return
	}
	for current := dlist.Head; current != nil; current = current.Next {
		fmt.Print(current.Text, " ")
	}
	fmt.Print("\n")
}

func DPrintBackward(dlist *Dlist) {
	if dlist.Tail == nil {
		fmt.Println("Dlist is empty.")
		return
	}
	for current := dlist.Tail; current != nil; current = current.Prev {
		fmt.Print(current.Text, " ")
	}
	fmt.Print("\n")
}

func DFree(dlist *Dlist) {
	dlist.Head = nil
	dlist.Tail = nil
}