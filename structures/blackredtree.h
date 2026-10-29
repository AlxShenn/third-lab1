#ifndef BLACKREDTREE_H
#define BLACKREDTREE_H

using namespace std;

struct TreeNode {
    int data;
    bool isRed;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;

    TreeNode(int val, bool red = true, TreeNode* p = nullptr)
        : data(val), isRed(red), left(nullptr), right(nullptr), parent(p) {}
};

bool isRed(TreeNode* node);
string nodeStr(TreeNode* n);
void rotateLeft(TreeNode*& root);
void rotateRight(TreeNode*& root);
void balance(TreeNode*& root);

void insertRecursive(TreeNode*& root, int value);

TreeNode* remove(TreeNode* root, int value);

bool search(TreeNode* root, int target);

void printPreOrder(TreeNode* root);
void printInOrder(TreeNode* root);
void printPostOrder(TreeNode* root);
bool printLevel(TreeNode* root, int level);
void printBFS(TreeNode* root);
void printAddresses(TreeNode* root);
void printLeaves(TreeNode* root);

void clearTree(TreeNode* root);

#endif