/*
938. Range Sum of BST
*/

// TC:O(n) SC:O(n)
class Solution {
    int res = 0;
public:
    int rangeSumBST(TreeNode* root, int low, int high) {
        traverse(root,low,high);

        return res;
    }
    void traverse(TreeNode* root, int low, int high){
        if(root == NULL) return;
        traverse(root->left, low, high);
        if(root->val >= low && root->val <= high) res += root->val;
        traverse(root->right, low, high);
    }
};
