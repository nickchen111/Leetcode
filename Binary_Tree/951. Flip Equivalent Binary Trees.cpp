/*
951. Flip Equivalent Binary Trees
*/


// TC:O(n) SC:O(n)
class Solution {
public:
    bool flipEquiv(TreeNode* root1, TreeNode* root2) {
        if(root1 == NULL && root2 == NULL) return true;
        if(root1 == NULL) return false;
        if(root2 == NULL) return false;

        if(root1 -> val != root2 -> val) return false;
        return (isSameTree(root1->left, root2->right) && isSameTree(root2->left, root1->right)) || (isSameTree(root1->left, root2->left) && isSameTree(root1->right, root2->right));
    }
    bool isSameTree(TreeNode* root1, TreeNode* root2) {
        if(root1 == NULL && root2 == NULL) return true;
        if(root1 == NULL) return false;
        if(root2 == NULL) return false;
        if(root1 -> val != root2 -> val) return false;

        return (isSameTree(root1->left, root2->right) && isSameTree(root2->left, root1->right)) || (isSameTree(root1->left, root2->left) && isSameTree(root1->right, root2->right));
    }
};
