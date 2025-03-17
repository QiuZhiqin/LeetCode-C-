#ifndef __ALG_BINARY_TREE_H
#define __ALG_BINARY_TREE_H

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

struct TreeNode* deduceTree(int* preorder, int preorderSize, int* inorder, int inorderSize);
int maxDepth(struct TreeNode* root);
int* inorderTraversal(struct TreeNode* root, int* returnSize);

#endif