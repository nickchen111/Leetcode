/*
2331. Evaluate Boolean Binary Tree
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    bool evaluateTree(TreeNode* root) {
        return DFS(root);
    }

    bool DFS(TreeNode* root){
        if(root->left == NULL && root->right == NULL){
            if(root->val == true) return true;
            else return false;
        }

        bool left = DFS(root->left);
        bool right = DFS(root->right);
        if(root->val == 2){
            return left || right;
        }
        else return left && right;
    }
};
