#include "common.h"
#include "alg_binary_tree.h"
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <unordered_map>

using namespace std;

class Solution {
    public:
        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
            /* parent is used to store the parent of each node, and set1 is used to store the path from p to root. */
            unordered_map<TreeNode*, TreeNode*> parent;
            unordered_set<TreeNode*> set1;
            TreeNode* cur = NULL;

            getParent(root, parent);
            parent.insert({root, root});
            /* Find all fathers of p and store them in set1. */
            cur = p;
            while (cur != root) {
                set1.insert(cur);
                cur = parent[cur];
            }
            /* root node must be father of p. */
            set1.insert(root);

            /* Find all fathers of q, if one of them is in set1, return it. */
            cur = q;
            while (cur != root) {
                if (set1.count(cur)) {
                    return cur;
                }
                cur = parent[cur];
            }
            /* root node must be father of q. */
            if (set1.count(root)) {
                return root;
            }

            return NULL;
        }

        void getParent(TreeNode* root, unordered_map<TreeNode*, TreeNode*>& parent) {
            if (root == NULL) {
                return;
            }

            if (root->left != NULL) {
                parent.insert({root->left, root});
            }
            if (root->right != NULL) {
                parent.insert({root->right, root});
            }

            getParent(root->left, parent);
            getParent(root->right, parent);
        }
};

