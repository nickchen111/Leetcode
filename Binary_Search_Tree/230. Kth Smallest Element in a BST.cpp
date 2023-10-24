/*
230. Kth Smallest Element in a BST
*/

// TC:O(n) SC:O(lgn) 
class Solution {
    int k;
    int count = 0;
    int res;
public:
    int kthSmallest(TreeNode* root, int k) {
        //inorder
        this->k = k;
        traverse(root);

        return res;
    }

    void traverse(TreeNode* root){
        if(root == NULL) return;

        traverse(root->left);
        count++;
        if(count == k){ 
            res = root->val;
            return;
        }
        traverse(root->right);
    }
};
