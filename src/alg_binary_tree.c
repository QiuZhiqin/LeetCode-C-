#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"alg_binary_tree.h"

struct TreeNode* deduceTree(int* preorder, int preorderSize, int* inorder, int inorderSize)
{
    int i;
    TreeNode *ret = NULL;

    if (preorder == NULL || inorder == NULL || preorderSize == 0 || inorderSize == 0) {
        return NULL;
    }

    ret = (TreeNode *)malloc(sizeof(TreeNode));
    if (ret == NULL) {
        return NULL;
    }

    ret->left = NULL;
    ret->right = NULL;
    ret->val = preorder[0];
    if (inorderSize == 1 && preorderSize == 1) {
        if (inorder[0] = preorder[0]) {
            return ret;
        } else {
            free(ret);
            return NULL;
        }
    }

    for (i = 0; i < inorderSize; ++i) {
        if (inorder[i] != preorder[0])
            continue;
        
        ret->left = deduceTree(preorder + 1, i + 1, inorder, i);
        ret->right = deduceTree(preorder + i + 1, preorderSize - i - 1, inorder + i + 1, inorderSize - i - 1);
        return ret;
    }

    free(ret);
    return NULL;
}

int maxDepth(struct TreeNode* root) {
    int left_depth, right_depth;

    if (root == NULL) {
        return 0;
    }

    left_depth = maxDepth(root->left);
    right_depth = maxDepth(root->right);
    return (left_depth > right_depth) ? left_depth + 1 : right_depth + 1;
}

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    int depth = 0, *inorderArray = NULL;
    int *leftInorderArray = NULL, leftInorderSize, *rightInorderArray = NULL, rightInorderSize;

    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    depth = maxDepth(root);
    inorderArray = (int *)malloc(sizeof(int) * (2 << depth));
    if (inorderArray == NULL) {
        printf("inorderTraversal: malloc failed\n");
        *returnSize = 0;
        return NULL;
    }

    leftInorderArray = inorderTraversal(root->left, &leftInorderSize);
    rightInorderArray = inorderTraversal(root->right, &rightInorderSize);
    if (leftInorderSize != 0)
        memcpy(inorderArray, leftInorderArray, sizeof(int) * leftInorderSize);
    inorderArray[leftInorderSize] = root->val;
    if (rightInorderSize != 0)
        memcpy(inorderArray + leftInorderSize + 1, rightInorderArray, sizeof(int) * rightInorderSize);
    *returnSize = leftInorderSize + rightInorderSize + 1;

    return inorderArray;
}