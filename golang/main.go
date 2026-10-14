package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

const fileName = "data.txt"

func printHelp() {
	fmt.Println("ARRAY:               MPUSH <value> | MINSERT <value> <index> | MGET <index>")
	fmt.Println("                     MDEL <index> | MSET <value> <index> | MLEN")
	fmt.Println("FORWARD LIST SLIST:  FPUSHHEAD|FPUSHTAIL <value>")
	fmt.Println("                     FPUSHAFTER|FPUSHBEFORE <value> <target>")
	fmt.Println("                     FDELHEAD|FDELTAIL | FDELAFTER|FDELBEFORE <target> | FDELVAL <value>")
	fmt.Println("                     FGET <value>")
	fmt.Println("LINKED LIST DLIST:   LPUSHHEAD|LPUSHTAIL|LPUSHAFTER|LPUSHBEFORE|LDELHEAD|LDELTAIL")
	fmt.Println("                     LDELAFTER|LDELBEFORE|LDELVAL|LGET <value>")
	fmt.Println("STACK:               SPUSH <value> | SPOP")
	fmt.Println("QUEUE:               QPUSH <value> | QPOP")
	fmt.Println("TREE:                TINSERT <number> | TDEL <number> | TGET <number>")
	fmt.Println("ELSE:                PRINT array|slist|dlist|stack|queue|tree | HELP | EXIT")
}

// SaveAll сохраняет все структуры в файл.
func SaveAll(arr *Array, slist *Slist, dlist *DlistNode,
	stack *Stack, queue *Queue, tree *TreeNode) {
	f, err := os.Create(fileName)
	if err != nil {
		return
	}
	defer f.Close()
	w := bufio.NewWriter(f)
	defer w.Flush()

	fmt.Fprintf(w, "ARRAY %d\n", MLength(arr))
	for i := 0; i < MLength(arr); i++ {
		fmt.Fprintf(w, "%s\n", MGet(arr, i))
	}

	fcount := 0
	for n := slist.head; n != nil; n = n.next {
		fcount++
	}
	fmt.Fprintf(w, "FLIST %d\n", fcount)
	for n := slist.head; n != nil; n = n.next {
		fmt.Fprintf(w, "%s\n", n.text)
	}

	lcount := 0
	for n := dlist; n != nil; n = n.next {
		lcount++
	}
	fmt.Fprintf(w, "DLIST %d\n", lcount)
	for n := dlist; n != nil; n = n.next {
		fmt.Fprintf(w, "%s\n", n.text)
	}

	scount := 0
	for n := stack.head; n != nil; n = n.next {
		scount++
	}
	fmt.Fprintf(w, "STACK %d\n", scount)
	for n := stack.head; n != nil; n = n.next {
		fmt.Fprintf(w, "%s\n", n.text)
	}

	qcount := 0
	for n := queue.head; n != nil; n = n.next {
		qcount++
	}
	fmt.Fprintf(w, "QUEUE %d\n", qcount)
	for n := queue.head; n != nil; n = n.next {
		fmt.Fprintf(w, "%s\n", n.text)
	}

	fmt.Fprint(w, "TREE ")
	var walk func(r *TreeNode)
	walk = func(r *TreeNode) {
		if r == nil {
			return
		}
		fmt.Fprintf(w, "%d ", r.data)
		walk(r.left)
		walk(r.right)
	}
	walk(tree)
	fmt.Fprint(w, "\n")
}

// LoadAll читает все структуры из файла.
func LoadAll(arr *Array, slist *Slist, dlist *DlistNode,
	stack *Stack, queue *Queue, tree *TreeNode) (*DlistNode, *TreeNode) {
	f, err := os.Open(fileName)
	if err != nil {
		return dlist, tree
	}
	defer f.Close()
	scanner := bufio.NewScanner(f)

	readSection := func(want string) (int, bool) {
		if !scanner.Scan() {
			return 0, false
		}
		fields := strings.Fields(scanner.Text())
		if len(fields) != 2 || fields[0] != want {
			return 0, false
		}
		count, err := strconv.Atoi(fields[1])
		if err != nil {
			return 0, false
		}
		return count, true
	}

	if count, ok := readSection("ARRAY"); ok {
		for i := 0; i < count && scanner.Scan(); i++ {
			MAddEnd(arr, scanner.Text())
		}
	}

	if count, ok := readSection("FLIST"); ok {
		for i := 0; i < count && scanner.Scan(); i++ {
			FPushTail(slist, scanner.Text())
		}
	}

	if count, ok := readSection("DLIST"); ok {
		for i := 0; i < count && scanner.Scan(); i++ {
			dlist = DPushTail(dlist, scanner.Text())
		}
	}

	if count, ok := readSection("STACK"); ok {
		buf := make([]string, 0, count)
		for i := 0; i < count && scanner.Scan(); i++ {
			buf = append(buf, scanner.Text())
		}
		for i := len(buf) - 1; i >= 0; i-- {
			SPush(stack, buf[i])
		}
	}

	if count, ok := readSection("QUEUE"); ok {
		for i := 0; i < count && scanner.Scan(); i++ {
			QPush(queue, scanner.Text())
		}
	}

	if scanner.Scan() {
		fields := strings.Fields(scanner.Text())
		if len(fields) > 0 && fields[0] == "TREE" {
			for _, tok := range fields[1:] {
				v, err := strconv.Atoi(tok)
				if err != nil {
					continue
				}
				if tree == nil {
					tree = NewTreeNode(v, false)
				} else {
					tree = insertRecursive(tree, v)
					tree.isRed = false
				}
			}
		}
	}

	return dlist, tree
}

func main() {
	var arr Array
	var slist Slist
	var dlist *DlistNode
	var stack Stack
	var queue Queue
	var tree *TreeNode

	MInitArray(&arr, 4)
	FInitializeSlist(&slist)
	SInitializeStack(&stack)
	QInitializeQueue(&queue)

	dlist, tree = LoadAll(&arr, &slist, dlist, &stack, &queue, tree)

	fmt.Println("Abstract Data Structures. HELP — list of commands.")

	scanner := bufio.NewScanner(os.Stdin)
	running := true
	for running {
		fmt.Print("> ")
		if !scanner.Scan() {
			break
		}
		tokens := strings.Fields(scanner.Text())
		if len(tokens) == 0 {
			continue
		}

		cmd := GetCommand(tokens[0])
		args := tokens[1:]
		argIdx := 0
		nextArg := func() (string, bool) {
			if argIdx < len(args) {
				argIdx++
				return args[argIdx-1], true
			}
			return "", false
		}
		nextInt := func() (int, bool) {
			s, ok := nextArg()
			if !ok {
				return 0, false
			}
			v, err := strconv.Atoi(s)
			if err != nil {
				return 0, false
			}
			return v, true
		}

		changed := false

		switch cmd {

		// ---------- массив ----------
		case MPUSH:
			if value, ok := nextArg(); ok {
				MAddEnd(&arr, value)
				fmt.Println("->", value)
				changed = true
			} else {
				fmt.Println("No")
			}

		case MINSERT:
			value, ok1 := nextArg()
			index, ok2 := nextInt()
			if ok1 && ok2 && index >= 0 && index <= MLength(&arr) {
				MAddIndex(&arr, value, index)
				fmt.Println("->", value)
				changed = true
			} else {
				fmt.Println("No")
			}

		case MGET:
			if index, ok := nextInt(); ok && index >= 0 && index < MLength(&arr) {
				fmt.Println("->", MGet(&arr, index))
			} else {
				fmt.Println("No")
			}

		case MDEL:
			if index, ok := nextInt(); ok && index >= 0 && index < MLength(&arr) {
				out := MGet(&arr, index)
				MDeleteIndex(&arr, index)
				fmt.Println("->", out)
				changed = true
			} else {
				fmt.Println("No")
			}

		case MSET:
			value, ok1 := nextArg()
			index, ok2 := nextInt()
			if ok1 && ok2 && index >= 0 && index < MLength(&arr) {
				MReplace(&arr, value, index)
				fmt.Println("->", value)
				changed = true
			} else {
				fmt.Println("No")
			}

		case MLEN:
			fmt.Println("->", MLength(&arr))

		// ---------- односвязный список ----------
		case FPUSHHEAD:
			if value, ok := nextArg(); ok {
				FPushHead(&slist, value)
				fmt.Println("->", value)
				changed = true
			} else {
				fmt.Println("No")
			}

		case FPUSHTAIL:
			if value, ok := nextArg(); ok {
				FPushTail(&slist, value)
				fmt.Println("->", value)
				changed = true
			} else {
				fmt.Println("No")
			}

		case FPUSHAFTER:
			value, ok1 := nextArg()
			target, ok2 := nextArg()
			if ok1 && ok2 {
				n := slist.head
				for n != nil && n.text != target {
					n = n.next
				}
				if n != nil {
					FPushAfter(n, value)
					fmt.Println("->", value)
					changed = true
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}

		case FPUSHBEFORE:
			value, ok1 := nextArg()
			target, ok2 := nextArg()
			if ok1 && ok2 {
				if slist.head == nil {
					fmt.Println("No")
				} else if slist.head.text == target {
					FPushHead(&slist, value)
					fmt.Println("->", value)
					changed = true
				} else {
					n := slist.head
					for n.next != nil && n.next.text != target {
						n = n.next
					}
					if n.next != nil {
						FPushAfter(n, value)
						fmt.Println("->", value)
						changed = true
					} else {
						fmt.Println("No")
					}
				}
			} else {
				fmt.Println("No")
			}

		case FDELHEAD:
			if slist.head != nil {
				out := slist.head.text
				FDeleteHead(&slist)
				fmt.Println("->", out)
				changed = true
			} else {
				fmt.Println("No")
			}

		case FDELTAIL:
			if slist.head != nil {
				n := slist.head
				for n.next != nil {
					n = n.next
				}
				out := n.text
				FDeleteTailForSlist(&slist)
				fmt.Println("->", out)
				changed = true
			} else {
				fmt.Println("No")
			}

		case FDELAFTER:
			if target, ok := nextArg(); ok {
				n := slist.head
				for n != nil && n.text != target {
					n = n.next
				}
				if n != nil && n.next != nil {
					out := n.next.text
					FDeleteAfter(n)
					fmt.Println("->", out)
					changed = true
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}

		case FDELBEFORE:
			if target, ok := nextArg(); ok {
				if slist.head == nil || slist.head.text == target {
					fmt.Println("No")
				} else if slist.head.next != nil && slist.head.next.text == target {
					out := slist.head.text
					FDeleteHead(&slist)
					fmt.Println("->", out)
					changed = true
				} else {
					n := slist.head
					for n.next != nil && n.next.next != nil && n.next.next.text != target {
						n = n.next
					}
					if n.next != nil && n.next.next != nil {
						out := n.next.text
						FDeleteAfter(n)
						fmt.Println("->", out)
						changed = true
					} else {
						fmt.Println("No")
					}
				}
			} else {
				fmt.Println("No")
			}

		case FDELVAL:
			if value, ok := nextArg(); ok {
				n := slist.head
				for n != nil && n.text != value {
					n = n.next
				}
				if n != nil {
					FDeleteValue(&slist, value)
					fmt.Println("->", value)
					changed = true
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}

		case FGET:
			if value, ok := nextArg(); ok {
				n := slist.head
				for n != nil && n.text != value {
					n = n.next
				}
				if n != nil {
					fmt.Println("->", value)
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}

		// ---------- двусвязный список ----------
		case LPUSHHEAD:
			if value, ok := nextArg(); ok {
				dlist = DPushHead(dlist, value)
				fmt.Println("->", value)
				changed = true
			} else {
				fmt.Println("No")
			}

		case LPUSHTAIL:
			if value, ok := nextArg(); ok {
				dlist = DPushTail(dlist, value)
				fmt.Println("->", value)
				changed = true
			} else {
				fmt.Println("No")
			}

		case LPUSHAFTER:
			value, ok1 := nextArg()
			target, ok2 := nextArg()
			if ok1 && ok2 {
				n := DFind(dlist, target)
				if n != nil {
					DPushAfter(n, value)
					fmt.Println("->", value)
					changed = true
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}

		case LPUSHBEFORE:
			value, ok1 := nextArg()
			target, ok2 := nextArg()
			if ok1 && ok2 {
				n := DFind(dlist, target)
				if n != nil {
					if n == dlist {
						dlist = DPushHead(dlist, value)
					} else {
						DPushBefore(n, value)
					}
					fmt.Println("->", value)
					changed = true
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}

		case LDELHEAD:
			if dlist != nil {
				out := dlist.text
				dlist = DDeleteHead(dlist)
				fmt.Println("->", out)
				changed = true
			} else {
				fmt.Println("No")
			}

		case LDELTAIL:
			if dlist != nil {
				n := dlist
				for n.next != nil {
					n = n.next
				}
				out := n.text
				dlist = DDeleteTail(dlist)
				fmt.Println("->", out)
				changed = true
			} else {
				fmt.Println("No")
			}

		case LDELAFTER:
			if target, ok := nextArg(); ok {
				n := DFind(dlist, target)
				if n != nil && n.next != nil {
					out := n.next.text
					DDeleteAfter(n)
					fmt.Println("->", out)
					changed = true
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}

		case LDELBEFORE:
			if target, ok := nextArg(); ok {
				n := DFind(dlist, target)
				if n != nil && n.prev != nil {
					out := n.prev.text
					if n.prev == dlist {
						dlist = DDeleteHead(dlist)
					} else {
						DDeleteBefore(n)
					}
					fmt.Println("->", out)
					changed = true
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}

		case LDELVAL:
			if value, ok := nextArg(); ok {
				n := DFind(dlist, value)
				if n != nil {
					dlist = DDeleteValue(dlist, value)
					fmt.Println("->", value)
					changed = true
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}

		case LGET:
			if value, ok := nextArg(); ok {
				n := DFind(dlist, value)
				if n != nil {
					fmt.Println("->", value)
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}

		// ---------- стек ----------
		case SPUSH:
			if value, ok := nextArg(); ok {
				SPush(&stack, value)
				fmt.Println("->", value)
				changed = true
			} else {
				fmt.Println("No")
			}

		case SPOP:
			if out, ok := SPop(&stack); ok {
				fmt.Println("->", out)
				changed = true
			} else {
				fmt.Println("No")
			}

		// ---------- очередь ----------
		case QPUSH:
			if value, ok := nextArg(); ok {
				QPush(&queue, value)
				fmt.Println("->", value)
				changed = true
			} else {
				fmt.Println("No")
			}

		case QPOP:
			if out, ok := QPop(&queue); ok {
				fmt.Println("->", out)
				changed = true
			} else {
				fmt.Println("No")
			}

		// ---------- дерево ----------
		case TINSERT:
			if value, ok := nextArg(); ok {
				v, err := strconv.Atoi(value)
				if err == nil {
					if tree == nil {
						tree = NewTreeNode(v, false)
					} else {
						tree = insertRecursive(tree, v)
						tree.isRed = false
					}
					fmt.Println("->", v)
					changed = true
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}

		case TDEL:
			if value, ok := nextArg(); ok {
				v, err := strconv.Atoi(value)
				if err == nil && search(tree, v) {
					tree = remove(tree, v)
					if tree != nil {
						tree.isRed = false
					}
					fmt.Println("->", v)
					changed = true
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}

		case TGET:
			if value, ok := nextArg(); ok {
				v, err := strconv.Atoi(value)
				if err == nil && search(tree, v) {
					fmt.Println("->", v)
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}

		// ---------- печать ----------
		case PRINT:
			typeArg, ok := nextArg()
			if !ok {
				fmt.Println("No")
				break
			}
			switch typeArg {
			case "array":
				MPrint(&arr)
			case "slist":
				for n := slist.head; n != nil; n = n.next {
					fmt.Print(n.text, " ")
				}
				fmt.Println()
			case "dlist":
				DPrintForward(dlist)
			case "stack":
				SPrint(&stack)
			case "queue":
				QPrint(&queue)
			case "queue1":
				QPrint(&queue)
			case "tree":
				fmt.Print("preorder:  ")
				printPreOrder(tree)
				fmt.Println()
				fmt.Print("inorder:   ")
				printInOrder(tree)
				fmt.Println()
				fmt.Print("postorder: ")
				printPostOrder(tree)
				fmt.Println()
				fmt.Print("bfs:       ")
				printBFS(tree)
			default:
				fmt.Println("No")
			}

		case HELP:
			printHelp()

		case EXIT:
			running = false

		default:
			fmt.Println("Unknown command. HELP — list of commands")
		}

		if changed {
			SaveAll(&arr, &slist, dlist, &stack, &queue, tree)
		}
	}

	SaveAll(&arr, &slist, dlist, &stack, &queue, tree)

	MFree(&arr)
	FFree(&slist)
	DFree(dlist)
	SFree(&stack)
	QFree(&queue)
	clearTree(tree)

	fmt.Println("Done.")
}
