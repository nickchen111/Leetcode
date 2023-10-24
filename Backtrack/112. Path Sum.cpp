/*
112. Path Sum
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
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

//更簡潔的寫法
/*
easy dfs to solve!? to record the sum and check it mabe postorder 
*/
