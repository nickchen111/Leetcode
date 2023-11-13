/*
112. Path Sum
*/

class Solution {
    int sum = 0;
    bool ok = false;
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        traverse(root, targetSum);
        return ok;
    }
    void traverse(TreeNode* root, int targetSum){
        if(root == nullptr) return;

        sum +=root->val;
        traverse(root->left, targetSum);
        traverse(root->right, targetSum);
        if(sum == targetSum && root->left == nullptr && root->right == nullptr){
            ok = true;
        }

        sum -=root->val;
    }
};

//簡短的遞迴寫法
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        //結束條件
        if(root == nullptr) return false;
        if(root->left == nullptr && root->right == nullptr){
            return root->val == targetSum;
        }
        int newSum = targetSum-root->val;

        return hasPathSum(root->left, newSum) || hasPathSum(root->right, newSum);
    }

};

//tc: o(n) sc:o(h) 
