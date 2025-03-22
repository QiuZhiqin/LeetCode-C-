#include "alg_binary_tree.h"

/* Solution for leetcode problem: https://leetcode.cn/problems/diameter-of-binary-tree/description/ */
int diameterOfBinaryTreeHelp(struct TreeNode* root, int *max)
{
    int leftDepth = 0, rightDepth = 0;

    if (root == NULL) {
        return 0;
    }

    leftDepth = diameterOfBinaryTreeHelp(root->left, max);
    rightDepth = diameterOfBinaryTreeHelp(root->right, max);
    if (leftDepth + rightDepth > *max)
        *max = leftDepth + rightDepth;    // Update the max diameter of the tree.

    return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;    // Return the depth of the tree.
}

int diameterOfBinaryTree(struct TreeNode* root) {
    int max = 0;

    diameterOfBinaryTreeHelp(root, &max);

    return max;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/kth-smallest-element-in-a-bst/description/ */
int dfsHelper(struct TreeNode* root, int *k)
{
    int ret = 0;

    if (root == NULL) {
        return 0;
    }

    ret = dfsHelper(root->left, k);
    if (ret != 0) {    // ret != 0 means the kth smallest element has been found.
        return ret;
    }

    /* The kth smallest node not found in left subtree, root val is the smallest node among unvisited nodes */
    (*k)--;
    if (*k == 0) {    // root is the kth smallest node.
        return root->val;
    }

    ret = dfsHelper(root->right, k);   // Find the kth smallest node in the right subtree.
    if (ret != 0) {
        return ret;
    }

    return 0;
}

int kthSmallest(struct TreeNode* root, int k) {
    if (root == NULL) {
        return 0;
    }

    return dfsHelper(root, &k);
}

/* Solution for leetcode problem: https://leetcode.cn/problems/binary-tree-right-side-view/description/ */
void rightSideViewHelper(struct TreeNode* root, int level, int *retArray)
{
    if (root == NULL) {
        return;
    }

    rightSideViewHelper(root->right, level + 1, retArray);
    if (retArray[level] == INT_MIN) {    // The right most node of the current level.
        retArray[level] = root->val;
    }
    rightSideViewHelper(root->left, level + 1, retArray);
}

int* rightSideView(struct TreeNode* root, int* returnSize) {
    int *retArray = NULL;

    *returnSize = 0;
    retArray = (int *)malloc(sizeof(int) * 100);
    if (retArray == NULL) {
        return NULL;
    }

    for (int i = 0; i < 100; i++) {
        retArray[i] = INT_MIN;
    }
    rightSideViewHelper(root, 0, retArray);
    *returnSize = maxDepth(root);
    return retArray;
}