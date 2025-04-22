#ifndef ALG_BINARY_TREE_H_
#define ALG_BINARY_TREE_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

#ifdef __cplusplus
extern "C" {
#endif
struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize);
int maxDepth(struct TreeNode* root);
int* inorderTraversal(struct TreeNode* root, int* returnSize);
struct TreeNode* sortedArrayToBST(int* nums, int numsSize);
bool isSymmetric(struct TreeNode* root);

#ifdef __cplusplus
}
#endif
#endif