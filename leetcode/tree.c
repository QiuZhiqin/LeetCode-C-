#include "alg_binary_tree.h"
#include "common.h"

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

/* Solution for leetcode problem: https://leetcode.cn/problems/flatten-binary-tree-to-linked-list/description/ */
void flatten(struct TreeNode* root) {
    struct TreeNode *p, *left, *right;

    if (root == NULL) {
        return;
    }

    left = root->left;
    right = root->right;
    flatten(left);
    flatten(right);
    root->left = NULL;
    root->right = left;
    p = root;
    while (p->right != NULL) {
        p = p->right;
    }
    p->right = right;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/path-sum-iii/description/ */
int countPathsFromNode(struct TreeNode* node, int currentSum, int targetSum) {
    int ret;

    if (node == NULL) {
        return 0;
    }

    currentSum += node->val;
    ret = (currentSum == targetSum) ? 1 : 0;
    ret += countPathsFromNode(node->left, currentSum, targetSum);
    ret += countPathsFromNode(node->right, currentSum, targetSum);

    return ret;
}

int pathSum(struct TreeNode* root, int targetSum) {
    if (root == NULL) {
        return 0;
    }

    return countPathsFromNode(root, 0, targetSum) + pathSum(root->left, targetSum) + pathSum(root->right, targetSum);
}

/* Solution for leetcode problem: https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/description/ */
struct TreeNode* dfsFindTarget(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q)
{
    struct TreeNode* left = NULL, *right = NULL;

    if (root == NULL) {
        return NULL;
    }

    if (root == p || root == q) {
        return root;
    }

    left = dfsFindTarget(root->left, p, q);
    right = dfsFindTarget(root->right, p, q);
    if (left == NULL) {    // p and q are in the right subtree.
        return right;
    } else if (right == NULL) {    // p and q are in the left subtree.
        return left;
    } else {    // p and q are in the different subtrees.
        return root;
    }
}

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    return dfsFindTarget(root, p, q);
}

/* Solution for leetcode problem: https://leetcode.cn/problems/binary-tree-maximum-path-sum/description/ */
int maxPathSumHelper(struct TreeNode* root, int *max)
{
    int left = 0, right = 0, sum = 0;

    if (root == NULL) {
        return 0;
    }

    left = maxPathSumHelper(root->left, max);
    right = maxPathSumHelper(root->right, max);
    /* Try to connect the left and right max path to the root node, see if the sum is bigger than the current max path sum. */
    sum = root->val + left + right;
    if (sum > *max) {
        *max = sum;
    }

    /* This function returns the maximum path sum that starts from the root node and ends at any node in the subtree rooted at root. 
     * Notice that you cant return MAX(sum, 0) because one node can only has one path.
     * MAX(left, right) + root->val means connect root to the bigger path.
     */
    return MAX(root->val + MAX(left, right), 0);
}

int maxPathSum(struct TreeNode* root) {
    int max = INT_MIN;

    if (root == NULL) {
        return 0;
    }

    maxPathSumHelper(root, &max);
    return max;
}

/* Solution for leetcode problem: https://leetcode.cn/problems/balanced-binary-tree/description/ */
bool isBalanced(struct TreeNode* root) {
    int left = 0, right = 0;

    if (root == NULL) {
        return true;
    }

    left = maxDepth(root->left);
    right = maxDepth(root->right);
    if (abs(left - right) > 1) {
        return false;
    }

    return isBalanced(root->left) && isBalanced(root->right);
}