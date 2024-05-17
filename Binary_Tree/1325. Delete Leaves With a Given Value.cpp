/*
1325. Delete Leaves With a Given Value
*/


//  TC:O(n) SC:O(n)
class Solution {
public:
    TreeNode* removeLeafNodes(TreeNode* root, int target) {
        if(root == NULL) return NULL;
        return DFS(NULL, root, target, 0);
    }
    TreeNode* DFS(TreeNode* parent, TreeNode* root, int target, bool left){
        if(root == NULL) return NULL;

        DFS(root, root->left, target, 1);
        DFS(root, root->right, target, 0);
        if(root->left == NULL && root->right == NULL && root->val == target){
            if(parent == NULL) return NULL;
            if(left) parent -> left = NULL;
            else parent->right = NULL;

            return parent;
        }
        
        return root;
    }
};
