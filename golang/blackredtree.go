package main

import "fmt"

type TreeNode struct {
	data  int
	isRed bool
	left  *TreeNode
	right *TreeNode
}

func NewTreeNode(val int, red bool) *TreeNode {
	return &TreeNode{data: val, isRed: red}
}

func isRed(node *TreeNode) bool {
	return node != nil && node.isRed
}

func rotateLeft(root *TreeNode) *TreeNode {
	newRoot := root.right
	root.right = newRoot.left
	newRoot.left = root
	return newRoot
}

func rotateRight(root *TreeNode) *TreeNode {
	newRoot := root.left
	root.left = newRoot.right
	newRoot.right = root
	return newRoot
}

func balance(root *TreeNode) *TreeNode {
	if root == nil || isRed(root) {
		return root
	}

	if isRed(root.left) && (isRed(root.left.left) || isRed(root.left.right)) {
		if isRed(root.right) {
			root.left.isRed = false
			root.right.isRed = false
			root.isRed = true
		} else {
			if isRed(root.left.right) {
				root.left = rotateLeft(root.left)
			}
			root = rotateRight(root)
			root.isRed = false
			root.right.isRed = true
		}
	} else if isRed(root.right) && (isRed(root.right.left) || isRed(root.right.right)) {
		if isRed(root.left) {
			root.left.isRed = false
			root.right.isRed = false
			root.isRed = true
		} else {
			if isRed(root.right.left) {
				root.right = rotateRight(root.right)
			}
			root = rotateLeft(root)
			root.isRed = false
			root.left.isRed = true
		}
	}
	return root
}

func insertRecursive(root *TreeNode, value int) *TreeNode {
	if value < root.data {
		if root.left == nil {
			root.left = NewTreeNode(value, true)
		} else {
			root.left = insertRecursive(root.left, value)
		}
	} else if value > root.data {
		if root.right == nil {
			root.right = NewTreeNode(value, true)
		} else {
			root.right = insertRecursive(root.right, value)
		}
	} else {
		return root
	}
	return balance(root)
}

func findMin(root *TreeNode) *TreeNode {
	for root != nil && root.left != nil {
		root = root.left
	}
	return root
}

func remove(root *TreeNode, value int) *TreeNode {
	if root == nil {
		return nil
	}
	if value < root.data {
		root.left = remove(root.left, value)
	} else if value > root.data {
		root.right = remove(root.right, value)
	} else {
		if root.left == nil {
			return root.right
		}
		if root.right == nil {
			return root.left
		}
		temp := findMin(root.right)
		root.data = temp.data
		root.right = remove(root.right, temp.data)
	}
	return root
}

func search(root *TreeNode, target int) bool {
	if root == nil {
		return false
	}
	if root.data == target {
		return true
	}
	if target < root.data {
		return search(root.left, target)
	}
	return search(root.right, target)
}

func printPreOrder(root *TreeNode) {
	if root == nil {
		return
	}
	color := "(Чёрный) "
	if root.isRed {
		color = "(Красный) "
	}
	fmt.Printf("%d%s", root.data, color)
	printPreOrder(root.left)
	printPreOrder(root.right)
}

func printInOrder(root *TreeNode) {
	if root == nil {
		return
	}
	printInOrder(root.left)
	fmt.Printf("%d ", root.data)
	printInOrder(root.right)
}

func printPostOrder(root *TreeNode) {
	if root == nil {
		return
	}
	printPostOrder(root.left)
	printPostOrder(root.right)
	fmt.Printf("%d ", root.data)
}

func printLevel(root *TreeNode, level int) bool {
	if root == nil {
		return false
	}
	if level == 0 {
		fmt.Printf("%d ", root.data)
		return true
	}
	left := printLevel(root.left, level-1)
	right := printLevel(root.right, level-1)
	return left || right
}

func printBFS(root *TreeNode) {
	level := 0
	for printLevel(root, level) {
		level++
	}
	fmt.Println()
}

func nodePtr(p *TreeNode) string {
	if p == nil {
		return "0"
	}
	return fmt.Sprintf("%p", p)
}

func printAddresses(root *TreeNode) {
	if root == nil {
		return
	}
	color := " B"
	if root.isRed {
		color = " R"
	}
	leftVal, rightVal := "null", "null"
	if root.left != nil {
		leftVal = fmt.Sprintf("%d", root.left.data)
	}
	if root.right != nil {
		rightVal = fmt.Sprintf("%d", root.right.data)
	}
	fmt.Printf("TreeNode [%2d%s] | Address: %p | Left: %s (%s) | Right: %s (%s)\n",
		root.data, color, root, leftVal, nodePtr(root.left), rightVal, nodePtr(root.right))
	printAddresses(root.left)
	printAddresses(root.right)
}

func clearTree(root *TreeNode) {
	if root == nil {
		return
	}
	clearTree(root.left)
	clearTree(root.right)
	root.left = nil
	root.right = nil
}
