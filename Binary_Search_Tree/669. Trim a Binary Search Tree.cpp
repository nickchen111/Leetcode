/*
669. Trim a Binary Search Tree
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        //刪減BST
        if(root == NULL) return NULL;
        if(root->val < low) return trimBST(root->right,low,high);
        else if(root->val > high) return trimBST(root->left,low,high);
        
        root->left = trimBST(root->left,low,high);
        root->right = trimBST(root->right,low,high);
        return root;
    }
};
