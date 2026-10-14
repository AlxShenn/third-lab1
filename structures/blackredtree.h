#ifndef BLACKREDTREE_H
#define BLACKREDTREE_H

using namespace std;

struct TreeNode {
    int data;
    bool isRed;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val, bool red = true)
        : data(val), isRed(red), left(nullptr), right(nullptr) {}
};

bool isRed(TreeNode* node);
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

void clearTree(TreeNode* root);

#endif
