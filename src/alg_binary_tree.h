#ifndef __ALG_BINARY_TREE_H
#define __ALG_BINARY_TREE_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize);
int maxDepth(struct TreeNode* root);
int* inorderTraversal(struct TreeNode* root, int* returnSize);
struct TreeNode* sortedArrayToBST(int* nums, int numsSize);
bool isSymmetric(struct TreeNode* root);

#endif