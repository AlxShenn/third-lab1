package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"

	s "adstruct/structures"
)

const fileName = "data.txt"

type arrayEntry struct {
	arr  *s.Array
	name string
}
type slistEntry struct {
	arr  *s.Slist
	name string
}
type dlistEntry struct {
	arr  *s.Dlist
	name string
}
type stackEntry struct {
	arr  *s.Stack
	name string
}
type queueEntry struct {
	arr  *s.Queue
	name string
}
type treeEntry struct {
	arr  **s.TreeNode
	name string
}

var (
	arrays []arrayEntry
	slists []slistEntry
	dlists []dlistEntry
	stacks []stackEntry
	queues []queueEntry
	trees  []treeEntry
)

func getArray(name string) *s.Array {
	for _, e := range arrays {
		if e.name == name {
			return e.arr
		}
	}
	a := &s.Array{}
	s.MInitArray(a, 4)
	arrays = append(arrays, arrayEntry{a, name})
	return a
}

func getSlist(name string) *s.Slist {
	for _, e := range slists {
		if e.name == name {
			return e.arr
		}
	}
	sl := &s.Slist{}
	s.FInitializeSlist(sl)
	slists = append(slists, slistEntry{sl, name})
	return sl
}

func getDlist(name string) *s.Dlist {
	for _, e := range dlists {
		if e.name == name {
			return e.arr
		}
	}
	d := &s.Dlist{}
	s.DInitialize(d)
	dlists = append(dlists, dlistEntry{d, name})
	return d
}

func getStack(name string) *s.Stack {
	for _, e := range stacks {
		if e.name == name {
			return e.arr
		}
	}
	st := &s.Stack{}
	s.SInitializeStack(st)
	stacks = append(stacks, stackEntry{st, name})
	return st
}

func getQueue(name string) *s.Queue {
	for _, e := range queues {
		if e.name == name {
			return e.arr
		}
	}
	q := &s.Queue{}
	s.QInitializeQueue(q)
	queues = append(queues, queueEntry{q, name})
	return q
}

func getTree(name string) **s.TreeNode {
	for _, e := range trees {
		if e.name == name {
			return e.arr
		}
	}
	t := new(*s.TreeNode)
	trees = append(trees, treeEntry{t, name})
	return t
}

func printHelp() {
	fmt.Println("Input: COMMAND <name> [argument]")
	fmt.Println("ARRAY: MPUSH <name> <value> | MINSERT <name> <value> <index> | MGET <name> <index>")
	fmt.Println("       MDEL <name> <index> | MSET <name> <value> <index> | MLEN <name>")
	fmt.Println("FORWARD LIST SLIST: FPUSHHEAD|FPUSHTAIL <name> <value>")
	fmt.Println("       FPUSHAFTER|FPUSHBEFORE <name> <value> <target>")
	fmt.Println("       FDELHEAD|FDELTAIL <name> | FDELAFTER|FDELBEFORE <name> <target> | FDELVAL <name> <value>")
	fmt.Println("       FGET <name> <value>")
	fmt.Println("LINKED LIST DLIST: LPUSHHEAD|LPUSHTAIL <name> <value> | LPUSHAFTER|LPUSHBEFORE <name> <value> <target>")
	fmt.Println("       LDELHEAD|LDELTAIL <name> | LDELAFTER|LDELBEFORE <name> <target> | LDELVAL|LGET <name> <value>")
	fmt.Println("STACK: SPUSH <name> <value> | SPOP <name>")
	fmt.Println("QUEUE: QPUSH <name> <value> | QPOP <name>")
	fmt.Println("TREE: TINSERT <name> <number> | TDEL <name> <number> | TGET <name> <number>")
	fmt.Println("ELSE: PRINT array|slist|dlist|stack|queue|tree <name> | HELP | EXIT")
}

func saveAll() {
	f, err := os.Create(fileName)
	if err != nil {
		return
	}
	defer f.Close()
	w := bufio.NewWriter(f)
	defer w.Flush()

	for _, e := range arrays {
		fmt.Fprintf(w, "ARRAY %s %d\n", e.name, s.MLength(e.arr))
		for j := 0; j < s.MLength(e.arr); j++ {
			fmt.Fprintln(w, s.MGet(e.arr, j))
		}
	}
	for _, e := range slists {
		count := 0
		for n := e.arr.Head; n != nil; n = n.Next {
			count++
		}
		fmt.Fprintf(w, "FLIST %s %d\n", e.name, count)
		for n := e.arr.Head; n != nil; n = n.Next {
			fmt.Fprintln(w, n.Text)
		}
	}
	for _, e := range dlists {
		count := 0
		for n := e.arr.Head; n != nil; n = n.Next {
			count++
		}
		fmt.Fprintf(w, "DLIST %s %d\n", e.name, count)
		for n := e.arr.Head; n != nil; n = n.Next {
			fmt.Fprintln(w, n.Text)
		}
	}
	for _, e := range stacks {
		count := 0
		for n := e.arr.Head; n != nil; n = n.Next {
			count++
		}
		fmt.Fprintf(w, "STACK %s %d\n", e.name, count)
		for n := e.arr.Head; n != nil; n = n.Next {
			fmt.Fprintln(w, n.Text)
		}
	}
	for _, e := range queues {
		count := 0
		for n := e.arr.Head; n != nil; n = n.Next {
			count++
		}
		fmt.Fprintf(w, "QUEUE %s %d\n", e.name, count)
		for n := e.arr.Head; n != nil; n = n.Next {
			fmt.Fprintln(w, n.Text)
		}
	}
	for _, e := range trees {
		fmt.Fprintf(w, "TREE %s ", e.name)
		var sb strings.Builder
		var walk func(n *s.TreeNode)
		walk = func(n *s.TreeNode) {
			if n == nil {
				return
			}
			sb.WriteString(strconv.Itoa(n.Data))
			sb.WriteString(" ")
			walk(n.Left)
			walk(n.Right)
		}
		walk(*e.arr)
		fmt.Fprintln(w, sb.String())
	}
}

func loadAll() {
	f, err := os.Open(fileName)
	if err != nil {
		return
	}
	defer f.Close()
	sc := bufio.NewScanner(f)
	var lines []string
	for sc.Scan() {
		lines = append(lines, sc.Text())
	}

	i := 0
	for i < len(lines) {
		parts := strings.Fields(lines[i])
		if len(parts) < 2 {
			i++
			continue
		}
		tag := parts[0]
		name := parts[1]

		if tag == "TREE" {
			tree := getTree(name)
			if len(parts) > 2 {
				for _, tok := range parts[2:] {
					v, err := strconv.Atoi(tok)
					if err != nil {
						continue
					}
					if *tree == nil {
						*tree = s.NewTreeNode(v, false, nil)
					} else {
						s.InsertRecursive(tree, v)
						(*tree).IsRed = false
					}
				}
			}
			i++
			continue
		}

		if len(parts) < 3 {
			i++
			continue
		}
		count, err := strconv.Atoi(parts[2])
		if err != nil {
			i++
			continue
		}
		i++
		vals := make([]string, 0, count)
		for k := 0; k < count && i < len(lines); k++ {
			vals = append(vals, lines[i])
			i++
		}

		switch tag {
		case "ARRAY":
			arr := getArray(name)
			for _, v := range vals {
				s.MAddEnd(arr, v)
			}
		case "FLIST":
			sl := getSlist(name)
			for _, v := range vals {
				s.FPushTail(sl, v)
			}
		case "DLIST":
			d := getDlist(name)
			for _, v := range vals {
				s.DPushTail(d, v)
			}
		case "STACK":
			st := getStack(name)
			for k := len(vals) - 1; k >= 0; k-- {
				s.SPush(st, vals[k])
			}
		case "QUEUE":
			q := getQueue(name)
			for _, v := range vals {
				s.QPush(q, v)
			}
		}
	}
}

func main() {
	loadAll()
	fmt.Println("Abstract Data Structures. HELP — list of commands.")

	reader := bufio.NewReader(os.Stdin)
	for {
		fmt.Print("> ")
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		line = strings.TrimRight(line, "\r\n")
		fields := strings.Fields(line)
		if len(fields) == 0 {
			continue
		}

		cmdName := fields[0]
		cmd := GetCommand(cmdName)
		if cmd == CmdHelp {
			printHelp()
			continue
		}
		if cmd == CmdExit {
			break
		}
		if len(fields) < 2 {
			fmt.Println("No name provided")
			continue
		}

		dsName := fields[1]
		args := fields[2:]
		changed := false

		needArg := func(n int) bool {
			return len(args) >= n
		}

		switch cmd {
		// --- ARRAY ---
		case CmdMPush:
			if needArg(1) {
				arr := getArray(dsName)
				s.MAddEnd(arr, args[0])
				fmt.Println("->", args[0])
				changed = true
			} else {
				fmt.Println("No")
			}
		case CmdMInsert:
			if needArg(2) {
				idx, _ := strconv.Atoi(args[1])
				arr := getArray(dsName)
				if idx >= 0 && idx <= s.MLength(arr) {
					s.MAddIndex(arr, args[0], idx)
					fmt.Println("->", args[0])
					changed = true
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}
		case CmdMGet:
			if needArg(1) {
				idx, _ := strconv.Atoi(args[0])
				arr := getArray(dsName)
				if idx >= 0 && idx < s.MLength(arr) {
					fmt.Println("->", s.MGet(arr, idx))
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}
		case CmdMDel:
			if needArg(1) {
				idx, _ := strconv.Atoi(args[0])
				arr := getArray(dsName)
				if idx >= 0 && idx < s.MLength(arr) {
					v := s.MGet(arr, idx)
					s.MDeleteIndex(arr, idx)
					fmt.Println("->", v)
					changed = true
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}
		case CmdMSet:
			if needArg(2) {
				idx, _ := strconv.Atoi(args[1])
				arr := getArray(dsName)
				if idx >= 0 && idx < s.MLength(arr) {
					s.MReplace(arr, args[0], idx)
					fmt.Println("->", args[0])
					changed = true
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}
		case CmdMLen:
			arr := getArray(dsName)
			fmt.Println("->", s.MLength(arr))

		// --- SLIST ---
		case CmdFPushHead:
			if needArg(1) {
				sl := getSlist(dsName)
				s.FPushHead(sl, args[0])
				fmt.Println("->", args[0])
				changed = true
			} else {
				fmt.Println("No")
			}
		case CmdFPushTail:
			if needArg(1) {
				sl := getSlist(dsName)
				s.FPushTail(sl, args[0])
				fmt.Println("->", args[0])
				changed = true
			} else {
				fmt.Println("No")
			}
		case CmdFPushAfter:
			if needArg(2) {
				sl := getSlist(dsName)
				s.FPushAfter(sl, args[1], args[0])
				fmt.Println("->", args[0])
				changed = true
			} else {
				fmt.Println("No")
			}
		case CmdFPushBefore:
			if needArg(2) {
				sl := getSlist(dsName)
				s.FPushBefore(sl, args[1], args[0])
				fmt.Println("->", args[0])
				changed = true
			} else {
				fmt.Println("No")
			}
		case CmdFDelHead:
			sl := getSlist(dsName)
			if sl.Head != nil {
				v := sl.Head.Text
				s.FDeleteHead(sl)
				fmt.Println("->", v)
				changed = true
			} else {
				fmt.Println("No")
			}
		case CmdFDelTail:
			sl := getSlist(dsName)
			if sl.Head != nil {
				s.FDeleteTail(sl)
				fmt.Println("-> Deleted")
				changed = true
			} else {
				fmt.Println("No")
			}
		case CmdFDelAfter:
			if needArg(1) {
				sl := getSlist(dsName)
				if s.FGet(sl, args[0]) {
					s.FDeleteAfter(sl, args[0])
					fmt.Println("-> Deleted")
					changed = true
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}
		case CmdFDelBefore:
			if needArg(1) {
				sl := getSlist(dsName)
				if s.FGet(sl, args[0]) {
					s.FDeleteBefore(sl, args[0])
					fmt.Println("-> Deleted")
					changed = true
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}
		case CmdFDelVal:
			if needArg(1) {
				sl := getSlist(dsName)
				if s.FGet(sl, args[0]) {
					s.FDeleteValue(sl, args[0])
					fmt.Println("->", args[0])
					changed = true
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}
		case CmdFGet:
			if needArg(1) {
				sl := getSlist(dsName)
				if s.FGet(sl, args[0]) {
					fmt.Println(">> True")
				} else {
					fmt.Println(">> False")
				}
			} else {
				fmt.Println("No")
			}

		// --- DLIST ---
		case CmdLPushHead:
			if needArg(1) {
				d := getDlist(dsName)
				s.DPushHead(d, args[0])
				fmt.Println("->", args[0])
				changed = true
			} else {
				fmt.Println("No")
			}
		case CmdLPushTail:
			if needArg(1) {
				d := getDlist(dsName)
				s.DPushTail(d, args[0])
				fmt.Println("->", args[0])
				changed = true
			} else {
				fmt.Println("No")
			}
		case CmdLPushAfter:
			if needArg(2) {
				d := getDlist(dsName)
				if s.DFind(d, args[1]) {
					s.DPushAfter(d, args[0], args[1])
					fmt.Println("->", args[0])
					changed = true
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}
		case CmdLPushBefore:
			if needArg(2) {
				d := getDlist(dsName)
				if s.DFind(d, args[1]) {
					s.DPushBefore(d, args[0], args[1])
					fmt.Println("->", args[0])
					changed = true
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}
		case CmdLDelHead:
			d := getDlist(dsName)
			if d.Head != nil {
				v := d.Head.Text
				s.DDeleteHead(d)
				fmt.Println("->", v)
				changed = true
			} else {
				fmt.Println("No")
			}
		case CmdLDelTail:
			d := getDlist(dsName)
			if d.Tail != nil {
				v := d.Tail.Text
				s.DDeleteTail(d)
				fmt.Println("->", v)
				changed = true
			} else {
				fmt.Println("No")
			}
		case CmdLDelAfter:
			if needArg(1) {
				d := getDlist(dsName)
				if s.DFind(d, args[0]) {
					s.DDeleteAfter(d, args[0])
					fmt.Println("-> Deleted")
					changed = true
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}
		case CmdLDelBefore:
			if needArg(1) {
				d := getDlist(dsName)
				if s.DFind(d, args[0]) {
					s.DDeleteBefore(d, args[0])
					fmt.Println("-> Deleted")
					changed = true
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}
		case CmdLDelVal:
			if needArg(1) {
				d := getDlist(dsName)
				if s.DFind(d, args[0]) {
					s.DDeleteValue(d, args[0])
					fmt.Println("->", args[0])
					changed = true
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}
		case CmdLGet:
			if needArg(1) {
				d := getDlist(dsName)
				if s.DFind(d, args[0]) {
					fmt.Println("->", args[0])
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}

		// --- STACK ---
		case CmdSPush:
			if needArg(1) {
				st := getStack(dsName)
				s.SPush(st, args[0])
				fmt.Println("->", args[0])
				changed = true
			} else {
				fmt.Println("No")
			}
		case CmdSPop:
			st := getStack(dsName)
			if v, ok := s.SPop(st); ok {
				fmt.Println("->", v)
				changed = true
			} else {
				fmt.Println("No")
			}

		// --- QUEUE ---
		case CmdQPush:
			if needArg(1) {
				q := getQueue(dsName)
				s.QPush(q, args[0])
				fmt.Println("->", args[0])
				changed = true
			} else {
				fmt.Println("No")
			}
		case CmdQPop:
			q := getQueue(dsName)
			if v, ok := s.QPop(q); ok {
				fmt.Println("->", v)
				changed = true
			} else {
				fmt.Println("No")
			}

		// --- TREE ---
		case CmdTInsert:
			if needArg(1) {
				v, err := strconv.Atoi(args[0])
				if err != nil {
					fmt.Println("No")
					break
				}
				tree := getTree(dsName)
				if *tree == nil {
					*tree = s.NewTreeNode(v, false, nil)
				} else {
					s.InsertRecursive(tree, v)
					(*tree).IsRed = false
				}
				fmt.Println("->", v)
				changed = true
			} else {
				fmt.Println("No")
			}
		case CmdTDel:
			if needArg(1) {
				v, err := strconv.Atoi(args[0])
				if err != nil {
					fmt.Println("No")
					break
				}
				tree := getTree(dsName)
				if s.Search(*tree, v) {
					*tree = s.Remove(*tree, v)
					if *tree != nil {
						(*tree).IsRed = false
					}
					fmt.Println("->", v)
					changed = true
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}
		case CmdTGet:
			if needArg(1) {
				v, err := strconv.Atoi(args[0])
				if err != nil {
					fmt.Println("No")
					break
				}
				tree := getTree(dsName)
				if s.Search(*tree, v) {
					fmt.Println("->", v)
				} else {
					fmt.Println("No")
				}
			} else {
				fmt.Println("No")
			}

		// --- PRINT ---
		case CmdPrint:
			if len(args) < 1 {
				fmt.Println("No")
				break
			}
			targetName := args[0]
			switch dsName {
			case "array":
				s.MPrint(getArray(targetName))
			case "slist":
				s.FPrint(getSlist(targetName))
			case "dlist":
				s.DPrintForward(getDlist(targetName))
			case "stack":
				s.SPrint(getStack(targetName))
			case "queue":
				s.QPrint(getQueue(targetName))
			case "tree":
				tree := *getTree(targetName)
				fmt.Print("preorder: ")
				s.PrintPreOrder(tree)
				fmt.Println()
				fmt.Print("inorder: ")
				s.PrintInOrder(tree)
				fmt.Println()
				fmt.Print("postorder: ")
				s.PrintPostOrder(tree)
				fmt.Println()
				fmt.Print("bfs: ")
				s.PrintBFS(tree)
				fmt.Print("leaves: ")
				s.PrintLeaves(tree)
				fmt.Println()
			default:
				fmt.Println("No")
			}

		default:
			fmt.Println("Unknown command. HELP — list of commands")
		}

		if changed {
			saveAll()
		}
	}

	saveAll()
	fmt.Println("Done.")
}