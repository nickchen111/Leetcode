/*
1026. Maximum Difference Between Node and Ancestor
*/

// TC:O(n) SC:O(n)
class Solution {
    int res = 0;
public:
    int maxAncestorDiff(TreeNode* root) {
        traverse(root,INT_MAX,INT_MIN);

        return res;
    }
    void traverse(TreeNode* root, int min_val, int max_val){
        if(root == NULL) return;

        min_val = min(min_val,root->val);
        max_val = max(max_val,root->val);
        res = max(res,max_val-min_val);
        traverse(root->left,min_val,max_val);
        traverse(root->right,min_val,max_val);
    }
};
