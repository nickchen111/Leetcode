/*
144. Binary Tree Preorder Traversal
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
    //分解問題算法
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        if(root == nullptr) return ans;

        ans.push_back(root->val); //根
        vector<int> left = preorderTraversal(root->left);//左邊
        ans.insert(ans.end(), left.begin(), left.end());
        vector<int> right = preorderTraversal(root->right);//右邊
        ans.insert(ans.end(), right.begin(), right.end());

        return ans; 
    }
};

class Solution {
    //遍歷 回溯算法
    vector<int> ans;
public:
    vector<int> preorderTraversal(TreeNode* root) {
        traverse(root);

        return ans;
    }

    void traverse(TreeNode* root){
        
        if(root == nullptr) return;
        ans.push_back(root->val);
        traverse(root->left);
        traverse(root->right);
    }
};
