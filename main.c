#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "alg_sort.h"
#include "alg_linked_list.h"
#include "alg_binary_tree.h"
#include "myhash.h"

int diameterOfBinaryTree(struct TreeNode* root);
int kthSmallest(struct TreeNode* root, int k);
int* rightSideView(struct TreeNode* root, int* returnSize);

int main(void)
{
    int preOrder[] = {1, 2, 5, 3, 4};
    int inOrder[] = {2, 5, 1, 3, 4};
    struct TreeNode *tree = deduceTree(preOrder, sizeof(preOrder) / sizeof(int), inOrder, sizeof(inOrder) / sizeof(int));
    int retSize = 0;
    int *result = rightSideView(tree, &retSize);

    return 0;
}