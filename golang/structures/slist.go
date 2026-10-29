package structures

import "fmt"

type SlistNode struct {
	Text string
	Next *SlistNode
}

type Slist struct {
	Head *SlistNode
}

func FInitializeSlist(slist *Slist) {
	slist.Head = nil
}

func FPushHead(slist *Slist, value string) {
	newNode := &SlistNode{Text: value, Next: slist.Head}
	slist.Head = newNode
}

func FPushTail(slist *Slist, value string) {
	newNode := &SlistNode{Text: value, Next: nil}
	if slist.Head == nil {
		slist.Head = newNode
		return
	}
	current := slist.Head
	for current.Next != nil {
		current = current.Next
	}
	current.Next = newNode
}

func FPushAfter(slist *Slist, target, value string) {
	current := slist.Head
	for current != nil && current.Text != target {
		current = current.Next
	}
	if current != nil {
		newNode := &SlistNode{Text: value, Next: current.Next}
		current.Next = newNode
	}
}

func FPushBefore(slist *Slist, target, value string) {
	if slist.Head == nil {
		return
	}
	if slist.Head.Text == target {
		FPushHead(slist, value)
		return
	}
	current := slist.Head
	for current.Next != nil && current.Next.Text != target {
		current = current.Next
	}
	if current.Next != nil {
		newNode := &SlistNode{Text: value, Next: current.Next}
		current.Next = newNode
	}
}

func FDeleteHead(slist *Slist) {
	if slist.Head == nil {
		return
	}
	slist.Head = slist.Head.Next
}

func FDeleteTail(slist *Slist) {
	if slist.Head == nil {
		return
	}
	if slist.Head.Next == nil {
		slist.Head = nil
		return
	}
	current := slist.Head
	for current.Next.Next != nil {
		current = current.Next
	}
	current.Next = nil
}

func FDeleteAfter(slist *Slist, target string) {
	current := slist.Head
	for current != nil && current.Text != target {
		current = current.Next
	}
	if current != nil && current.Next != nil {
		current.Next = current.Next.Next
	}
}

func FDeleteBefore(slist *Slist, target string) {
	if slist.Head == nil {
		return
	}
	if slist.Head.Text == target {
		FDeleteHead(slist)
		return
	}
	current := slist.Head
	for current.Next != nil && current.Next.Next != nil && current.Next.Next.Text != target {
		current = current.Next
	}
	if current.Next != nil && current.Next.Next != nil {
		current.Next = current.Next.Next
	}
}

func FDeleteValue(slist *Slist, value string) {
	if slist.Head == nil {
		return
	}
	if slist.Head.Text == value {
		FDeleteHead(slist)
		return
	}
	current := slist.Head
	for current.Next != nil && current.Next.Text != value {
		current = current.Next
	}
	if current.Next != nil {
		current.Next = current.Next.Next
	}
}

func FGet(slist *Slist, target string) bool {
	for current := slist.Head; current != nil; current = current.Next {
		if current.Text == target {
			return true
		}
	}
	return false
}

func FPrint(slist *Slist) {
	if slist.Head == nil {
		fmt.Println("Slist is empty")
		return
	}
	for current := slist.Head; current != nil; current = current.Next {
		fmt.Print(current.Text, " ")
	}
	fmt.Print("\n")
}

func FFree(slist *Slist) {
	slist.Head = nil
}