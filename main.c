#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


 typedef struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
 } TreeNode;
 
struct TreeNode* deduceTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
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


int main()
{
    int nums[] = {}, retSize = 0;

    return 0;
}