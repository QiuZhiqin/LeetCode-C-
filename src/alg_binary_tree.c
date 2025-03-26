#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"alg_binary_tree.h"

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize)
{
    int i;
    struct TreeNode *ret = NULL;

    if (preorder == NULL || inorder == NULL || preorderSize == 0 || inorderSize == 0) {
        return NULL;
    }

    ret = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    if (ret == NULL) {
        return NULL;
    }

    ret->val = preorder[0];
    for (i = 0; i < inorderSize; ++i) {
        if (inorder[i] != preorder[0])
            continue;
        
        ret->left = buildTree(preorder + 1, i + 1, inorder, i);
        ret->right = buildTree(preorder + i + 1, preorderSize - i - 1, inorder + i + 1, inorderSize - i - 1);
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

void inorderTraversalHelper(struct TreeNode* root, int* inorderArray, int* returnSize) {
    if (root == NULL) {
        return;
    }

    inorderTraversalHelper(root->left, inorderArray, returnSize);
    inorderArray[(*returnSize)++] = root->val;
    inorderTraversalHelper(root->right, inorderArray, returnSize);
}

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    int depth = 0, *inorderArray = NULL;
    int *leftInorderArray = NULL;

    *returnSize = 0;
    if (root == NULL) {
        return NULL;
    }

    depth = maxDepth(root);
    inorderArray = (int *)malloc(sizeof(int) * (2 << depth));
    if (inorderArray == NULL) {
        printf("inorderTraversal: malloc failed\n");
        *returnSize = 0;
        return NULL;
    }

    inorderTraversalHelper(root, inorderArray, returnSize);
    return inorderArray;
}

struct TreeNode* invertTree(struct TreeNode* root) {
    struct TreeNode *tmp = NULL;

    if (root == NULL) {
        return NULL;
    }

    root->left = invertTree(root->left);
    root->right = invertTree(root->right);
    tmp = root->left;
    root->left = root->right;
    root->right = tmp;

    return root;
}

bool isSymmetricHelper(struct TreeNode* left, struct TreeNode* right) {
    if (left == NULL && right == NULL) {
        return true;
    } else if (left == NULL || right == NULL) {
        return false;
    }

    if (left->val != right->val) {
        return false;
    }

    return isSymmetricHelper(left->left, right->right) && isSymmetricHelper(left->right, right->left);
}

bool isSymmetric(struct TreeNode* root) {
    if (root == NULL) {
        return true;
    }

    return isSymmetricHelper(root->left, root->right);
}

/* Solution for leetcode problem: https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/description/ */
struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
    struct TreeNode *root = NULL;
    int center = numsSize / 2;

    if (nums == NULL || numsSize == 0) {
        return NULL;
    }

    root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    if (root == NULL) {
        return NULL;
    }

    root->val = nums[center];
    root->left = sortedArrayToBST(nums, center);
    root->right = sortedArrayToBST(nums + center + 1, numsSize - center - 1);

    return root;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/validate-binary-search-tree/description/ */
bool isValidBSTHelper(struct TreeNode* root, long long min, long long max) {
    if (root == NULL) {
        return true;
    }

    if (root->val <= min || root->val >= max) {
        return false;
    }

    return isValidBSTHelper(root->left, min, root->val) && isValidBSTHelper(root->right, root->val, max);
}

bool isValidBST(struct TreeNode* root) {
    return isValidBSTHelper(root, LLONG_MIN, LLONG_MAX);
}