#include <iostream>
#include <iomanip>
#include <string>
#include <blackredtree.h>

using namespace std;

bool isRed(TreeNode* node) {
    return node != nullptr && node->isRed;
}

void rotateLeft(TreeNode*& root) {
    TreeNode* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    root = newRoot;
}

void rotateRight(TreeNode*& root) {
    TreeNode* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    root = newRoot;
}

void balance(TreeNode*& root) {
    if (root == nullptr || isRed(root)) return;

    if (isRed(root->left) && (isRed(root->left->left) || isRed(root->left->right))) {
        if (isRed(root->right)) {
            root->left->isRed = false;
            root->right->isRed = false;
            root->isRed = true;
        } else {
            if (isRed(root->left->right)) {
                rotateLeft(root->left);
            }
            rotateRight(root);
            root->isRed = false;
            root->right->isRed = true;
        }
    }

    else if (isRed(root->right) && (isRed(root->right->left) || isRed(root->right->right))) {
        if (isRed(root->left)) {
            root->left->isRed = false;
            root->right->isRed = false;
            root->isRed = true;
        } else {
            if (isRed(root->right->left)) {
                rotateRight(root->right);
            }
            rotateLeft(root);
            root->isRed = false;
            root->left->isRed = true;
        }
    }
}

void insertRecursive(TreeNode*& root, int value) {
    if (value < root->data) {
        if (root->left == nullptr) {
            root->left = new TreeNode(value, true);
        } else {
            insertRecursive(root->left, value);
        }
    } else if (value > root->data) {
        if (root->right == nullptr) {
            root->right = new TreeNode(value, true);
        } else {
            insertRecursive(root->right, value);
        }
    } else {
        return; 
    }
    balance(root);
}

TreeNode* findMin(TreeNode* root) {
    while (root != nullptr && root->left != nullptr) {
        root = root->left;
    }
    return root;
}


TreeNode* remove(TreeNode* root, int value) {
    if (root == nullptr) return nullptr;

    if (value < root->data) {
        root->left = remove(root->left, value);
    } else if (value > root->data) {
        root->right = remove(root->right, value);
    } else {

        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        TreeNode* temp = findMin(root->right);
        root->data = temp->data;
        root->right = remove(root->right, temp->data);
    }
    return root;
}


bool search(TreeNode* root, int target) {
    if (root == nullptr) return false;
    if (root->data == target) return true;

    if (target < root->data)
        return search(root->left, target);
    else
        return search(root->right, target);
}


void printPreOrder(TreeNode* root) {
    if (root == nullptr) return;
    cout << root->data << " ";
    printPreOrder(root->left);
    printPreOrder(root->right);
}

void printInOrder(TreeNode* root) {
    if (root == nullptr) return;
    printInOrder(root->left);
    cout << root->data << " ";
    printInOrder(root->right);
}

void printPostOrder(TreeNode* root) {
    if (root == nullptr) return;
    printPostOrder(root->left);
    printPostOrder(root->right);
    cout << root->data << " ";
}

bool printLevel(TreeNode* root, int level) {
    if (root == nullptr) return false;
    if (level == 0) {
        cout << root->data << " ";
        return true;
    }
    bool left = printLevel(root->left, level - 1);
    bool right = printLevel(root->right, level - 1);
    return left || right;
}

void printBFS(TreeNode* root) {
    int level = 0;
    while (printLevel(root, level)) {
        level++;
    }
    cout << endl;
}

void printAddresses(TreeNode* root) {
    if (root == nullptr) return;

    cout << "TreeNode [" << setw(2) << root->data << (root->isRed ? " R" : " B") << "]"
         << " | Address: " << root
         << " | Left: " << (root->left ? to_string(root->left->data) : "null")
         << " (" << root->left << ")"
         << " | Right: " << (root->right ? to_string(root->right->data) : "null")
         << " (" << root->right << ")\n";

    printAddresses(root->left);
    printAddresses(root->right);
}

void clearTree(TreeNode* root) {
    if (root == nullptr) return;
    clearTree(root->left);
    clearTree(root->right);
    delete root;
}
