#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
#include <blackredtree.h>

using namespace std;

bool isRed(TreeNode* node) {
    return node != nullptr && node->isRed;
}

string nodeStr(TreeNode* n) {
    if (n == nullptr) return "nullptr";
    string s = to_string(n->data);
    s += n->isRed ? "(R)" : "(B)";
    return s;
}

void rotateLeft(TreeNode*& root) {
    if (root == nullptr || root->right == nullptr) return;
    TreeNode* newRoot = root->right;
    root->right = newRoot->left;
    if (newRoot->left != nullptr) newRoot->left->parent = root;
    newRoot->parent = root->parent;
    newRoot->left = root;
    root->parent = newRoot;
    root = newRoot;
}

void rotateRight(TreeNode*& root) {
    if (root == nullptr || root->left == nullptr) return;
    TreeNode* newRoot = root->left;
    root->left = newRoot->right;
    if (newRoot->right != nullptr) newRoot->right->parent = root;
    newRoot->parent = root->parent;
    newRoot->right = root;
    root->parent = newRoot;
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
    if (root == nullptr) {
        root = new TreeNode(value, true, nullptr);
        return;
    }
    if (value < root->data) {
        if (root->left == nullptr) {
            root->left = new TreeNode(value, true, root);
        } else {
            insertRecursive(root->left, value);
        }
    } else if (value > root->data) {
        if (root->right == nullptr) {
            root->right = new TreeNode(value, true, root);
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

static void RBTransplant(TreeNode*& root, TreeNode* u, TreeNode* v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

static void RBDeleteFixup(TreeNode*& root, TreeNode* x) {
    while (x != root && (x == nullptr || !x->isRed)) {
        TreeNode* xParent = (x != nullptr) ? x->parent : nullptr;
        if (xParent == nullptr) break;

        if (x == xParent->left) {
            TreeNode* w = xParent->right;

            if (w != nullptr && w->isRed) {
                w->isRed = false;
                xParent->isRed = true;
                rotateLeft(xParent);
                w = xParent->right;
            }

            if ((w == nullptr || (w->left == nullptr || !w->left->isRed)) &&
                (w == nullptr || (w->right == nullptr || !w->right->isRed))) {
                if (w != nullptr) w->isRed = true;
                x = xParent;
            } else {
                if (w->right == nullptr || !w->right->isRed) {
                    if (w->left != nullptr) w->left->isRed = false;
                    w->isRed = true;
                    rotateRight(w);
                    w = xParent->right;
                }
                w->isRed = xParent->isRed;
                xParent->isRed = false;
                if (w->right != nullptr) w->right->isRed = false;
                rotateLeft(xParent);
                x = root;
                break;
            }
        } else {
            TreeNode* w = xParent->left;

            if (w != nullptr && w->isRed) {
                w->isRed = false;
                xParent->isRed = true;
                rotateRight(xParent);
                w = xParent->left;
            }

            if ((w == nullptr || (w->left == nullptr || !w->left->isRed)) &&
                (w == nullptr || (w->right == nullptr || !w->right->isRed))) {
                if (w != nullptr) w->isRed = true;
                x = xParent;
            } else {
                if (w->left == nullptr || !w->left->isRed) {
                    if (w->right != nullptr) w->right->isRed = false;
                    w->isRed = true;
                    rotateLeft(w);
                    w = xParent->left;
                }
                w->isRed = xParent->isRed;
                xParent->isRed = false;
                if (w->left != nullptr) w->left->isRed = false;
                rotateRight(xParent);
                x = root;
                break;
            }
        }
    }
    if (x != nullptr) x->isRed = false;
}

TreeNode* remove(TreeNode* root, int value) {
    if (root == nullptr) return nullptr;

    TreeNode* z = root;
    while (z != nullptr && z->data != value) {
        if (value < z->data) z = z->left;
        else z = z->right;
    }
    if (z == nullptr) return root;

    TreeNode* y = z;
    bool yOriginalRed = y->isRed;
    TreeNode* x = nullptr;

    if (z->left == nullptr) {
        x = z->right;
        RBTransplant(root, z, z->right);
    } else if (z->right == nullptr) {
        x = z->left;
        RBTransplant(root, z, z->left);
    } else {
        y = findMin(z->right);
        yOriginalRed = y->isRed;
        x = y->right;

        if (y->parent == z) {
            if (x != nullptr) x->parent = y;
        } else {
            RBTransplant(root, y, y->right);
            y->right = z->right;
            if (y->right != nullptr) y->right->parent = y;
        }

        RBTransplant(root, z, y);
        y->left = z->left;
        if (y->left != nullptr) y->left->parent = y;
        y->isRed = z->isRed;
    }

    delete z;

    if (!yOriginalRed) {
        RBDeleteFixup(root, x);
    }

    if (root != nullptr) root->isRed = false;
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
    cout << nodeStr(root) << " ";
    printPreOrder(root->left);
    printPreOrder(root->right);
}

void printInOrder(TreeNode* root) {
    if (root == nullptr) return;
    printInOrder(root->left);
    cout << nodeStr(root) << " ";
    printInOrder(root->right);
}

void printPostOrder(TreeNode* root) {
    if (root == nullptr) return;
    printPostOrder(root->left);
    printPostOrder(root->right);
    cout << nodeStr(root) << " ";
}

bool printLevel(TreeNode* root, int level) {
    if (root == nullptr) return false;
    if (level == 0) {
        cout << nodeStr(root) << " ";
        return true;
    }
    if (level < 0) return false;
    bool left  = printLevel(root->left,  level - 1);
    bool right = printLevel(root->right, level - 1);
    return left || right;
}

void printBFS(TreeNode* root) {
    if (root == nullptr) { cout << endl; return; }
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* cur = q.front(); q.pop();
        cout << nodeStr(cur) << " ";
        if (cur->left)  q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    cout << endl;
}

void printLeaves(TreeNode* root) {
    if (root == nullptr) return;
    if (root->left == nullptr && root->right == nullptr) {
        cout << nodeStr(root) << " (left=nullptr, right=nullptr) ";
        return;
    }
    printLeaves(root->left);
    printLeaves(root->right);
}

void printAddresses(TreeNode* root) {
    if (root == nullptr) return;
    cout << "TreeNode [" << setw(2) << root->data << (root->isRed ? " R" : " B") << "]"
         << " | Address: " << root
         << " | Parent: " << (root->parent ? nodeStr(root->parent) : "nullptr")
         << " (" << root->parent << ")"
         << " | Left: " << (root->left ? nodeStr(root->left) : "nullptr")
         << " (" << root->left << ")"
         << " | Right: " << (root->right ? nodeStr(root->right) : "nullptr")
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