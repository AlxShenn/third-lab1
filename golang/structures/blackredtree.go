package structures

import (
	"fmt"
	"strconv"
)

type TreeNode struct {
	Data   int
	IsRed  bool
	Left   *TreeNode
	Right  *TreeNode
	Parent *TreeNode
}

func NewTreeNode(val int, red bool, parent *TreeNode) *TreeNode {
	return &TreeNode{Data: val, IsRed: red, Parent: parent}
}

func IsRed(node *TreeNode) bool {
	return node != nil && node.IsRed
}

func NodeStr(n *TreeNode) string {
	if n == nil {
		return "nullptr"
	}
	color := "(B)"
	if n.IsRed {
		color = "(R)"
	}
	return strconv.Itoa(n.Data) + color
}

func rotateLeft(root **TreeNode) {
	if *root == nil || (*root).Right == nil {
		return
	}
	newRoot := (*root).Right
	(*root).Right = newRoot.Left
	if newRoot.Left != nil {
		newRoot.Left.Parent = *root
	}
	newRoot.Parent = (*root).Parent
	newRoot.Left = *root
	(*root).Parent = newRoot
	*root = newRoot
}

func rotateRight(root **TreeNode) {
	if *root == nil || (*root).Left == nil {
		return
	}
	newRoot := (*root).Left
	(*root).Left = newRoot.Right
	if newRoot.Right != nil {
		newRoot.Right.Parent = *root
	}
	newRoot.Parent = (*root).Parent
	newRoot.Right = *root
	(*root).Parent = newRoot
	*root = newRoot
}

func balance(root **TreeNode) {
	r := *root
	if r == nil || IsRed(r) {
		return
	}

	if IsRed(r.Left) && (IsRed(r.Left.Left) || IsRed(r.Left.Right)) {
		if IsRed(r.Right) {
			r.Left.IsRed = false
			r.Right.IsRed = false
			r.IsRed = true
		} else {
			if IsRed(r.Left.Right) {
				rotateLeft(&r.Left)
			}
			rotateRight(root)
			r = *root
			r.IsRed = false
			r.Right.IsRed = true
		}
	} else if IsRed(r.Right) && (IsRed(r.Right.Left) || IsRed(r.Right.Right)) {
		if IsRed(r.Left) {
			r.Left.IsRed = false
			r.Right.IsRed = false
			r.IsRed = true
		} else {
			if IsRed(r.Right.Left) {
				rotateRight(&r.Right)
			}
			rotateLeft(root)
			r = *root
			r.IsRed = false
			r.Left.IsRed = true
		}
	}
}

func InsertRecursive(root **TreeNode, value int) {
	if *root == nil {
		*root = NewTreeNode(value, true, nil)
		return
	}
	r := *root
	if value < r.Data {
		if r.Left == nil {
			r.Left = NewTreeNode(value, true, r)
		} else {
			InsertRecursive(&r.Left, value)
		}
	} else if value > r.Data {
		if r.Right == nil {
			r.Right = NewTreeNode(value, true, r)
		} else {
			InsertRecursive(&r.Right, value)
		}
	} else {
		return
	}
	balance(root)
}

func findMin(root *TreeNode) *TreeNode {
	for root != nil && root.Left != nil {
		root = root.Left
	}
	return root
}

func rbTransplant(root **TreeNode, u, v *TreeNode) {
	if u.Parent == nil {
		*root = v
	} else if u == u.Parent.Left {
		u.Parent.Left = v
	} else {
		u.Parent.Right = v
	}
	if v != nil {
		v.Parent = u.Parent
	}
}

func rbDeleteFixup(root **TreeNode, x *TreeNode) {
	for x != *root && (x == nil || !x.IsRed) {
		var xParent *TreeNode
		if x != nil {
			xParent = x.Parent
		}
		if xParent == nil {
			break
		}

		if x == xParent.Left {
			w := xParent.Right

			if w != nil && w.IsRed {
				w.IsRed = false
				xParent.IsRed = true
				rotateLeft(&xParent)
				w = xParent.Right
			}

			if (w == nil || (w.Left == nil || !w.Left.IsRed)) &&
				(w == nil || (w.Right == nil || !w.Right.IsRed)) {
				if w != nil {
					w.IsRed = true
				}
				x = xParent
			} else {
				if w.Right == nil || !w.Right.IsRed {
					if w.Left != nil {
						w.Left.IsRed = false
					}
					w.IsRed = true
					rotateRight(&w)
					w = xParent.Right
				}
				w.IsRed = xParent.IsRed
				xParent.IsRed = false
				if w.Right != nil {
					w.Right.IsRed = false
				}
				rotateLeft(&xParent)
				x = *root
				break
			}
		} else {
			w := xParent.Left

			if w != nil && w.IsRed {
				w.IsRed = false
				xParent.IsRed = true
				rotateRight(&xParent)
				w = xParent.Left
			}

			if (w == nil || (w.Left == nil || !w.Left.IsRed)) &&
				(w == nil || (w.Right == nil || !w.Right.IsRed)) {
				if w != nil {
					w.IsRed = true
				}
				x = xParent
			} else {
				if w.Left == nil || !w.Left.IsRed {
					if w.Right != nil {
						w.Right.IsRed = false
					}
					w.IsRed = true
					rotateLeft(&w)
					w = xParent.Left
				}
				w.IsRed = xParent.IsRed
				xParent.IsRed = false
				if w.Left != nil {
					w.Left.IsRed = false
				}
				rotateRight(&xParent)
				x = *root
				break
			}
		}
	}
	if x != nil {
		x.IsRed = false
	}
}

func Remove(root *TreeNode, value int) *TreeNode {
	if root == nil {
		return nil
	}

	z := root
	for z != nil && z.Data != value {
		if value < z.Data {
			z = z.Left
		} else {
			z = z.Right
		}
	}
	if z == nil {
		return root
	}

	y := z
	yOriginalRed := y.IsRed
	var x *TreeNode

	if z.Left == nil {
		x = z.Right
		rbTransplant(&root, z, z.Right)
	} else if z.Right == nil {
		x = z.Left
		rbTransplant(&root, z, z.Left)
	} else {
		y = findMin(z.Right)
		yOriginalRed = y.IsRed
		x = y.Right

		if y.Parent == z {
			if x != nil {
				x.Parent = y
			}
		} else {
			rbTransplant(&root, y, y.Right)
			y.Right = z.Right
			if y.Right != nil {
				y.Right.Parent = y
			}
		}

		rbTransplant(&root, z, y)
		y.Left = z.Left
		if y.Left != nil {
			y.Left.Parent = y
		}
		y.IsRed = z.IsRed
	}

	if !yOriginalRed {
		rbDeleteFixup(&root, x)
	}

	if root != nil {
		root.IsRed = false
	}
	return root
}

func Search(root *TreeNode, target int) bool {
	if root == nil {
		return false
	}
	if root.Data == target {
		return true
	}
	if target < root.Data {
		return Search(root.Left, target)
	}
	return Search(root.Right, target)
}

func PrintPreOrder(root *TreeNode) {
	if root == nil {
		return
	}
	fmt.Print(NodeStr(root), " ")
	PrintPreOrder(root.Left)
	PrintPreOrder(root.Right)
}

func PrintInOrder(root *TreeNode) {
	if root == nil {
		return
	}
	PrintInOrder(root.Left)
	fmt.Print(NodeStr(root), " ")
	PrintInOrder(root.Right)
}

func PrintPostOrder(root *TreeNode) {
	if root == nil {
		return
	}
	PrintPostOrder(root.Left)
	PrintPostOrder(root.Right)
	fmt.Print(NodeStr(root), " ")
}

func PrintBFS(root *TreeNode) {
	if root == nil {
		fmt.Println()
		return
	}
	queue := []*TreeNode{root}
	for len(queue) > 0 {
		cur := queue[0]
		queue = queue[1:]
		fmt.Print(NodeStr(cur), " ")
		if cur.Left != nil {
			queue = append(queue, cur.Left)
		}
		if cur.Right != nil {
			queue = append(queue, cur.Right)
		}
	}
	fmt.Println()
}

func PrintLeaves(root *TreeNode) {
	if root == nil {
		return
	}
	if root.Left == nil && root.Right == nil {
		fmt.Print(NodeStr(root), " (left=nullptr, right=nullptr) ")
		return
	}
	PrintLeaves(root.Left)
	PrintLeaves(root.Right)
}

func PrintAddresses(root *TreeNode) {
	if root == nil {
		return
	}
	color := "B"
	if root.IsRed {
		color = "R"
	}
	left := "nullptr"
	if root.Left != nil {
		left = NodeStr(root.Left)
	}
	right := "nullptr"
	if root.Right != nil {
		right = NodeStr(root.Right)
	}
	parent := "nullptr"
	if root.Parent != nil {
		parent = NodeStr(root.Parent)
	}
	fmt.Printf("TreeNode [%2d %s] | Address: %p | Parent: %s (%p) | Left: %s (%p) | Right: %s (%p)\n",
		root.Data, color, root, parent, root.Parent, left, root.Left, right, root.Right)
	PrintAddresses(root.Left)
	PrintAddresses(root.Right)
}

func ClearTree(root *TreeNode) {
	if root == nil {
		return
	}
	ClearTree(root.Left)
	ClearTree(root.Right)
}