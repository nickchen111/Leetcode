/*
94. Binary Tree Inorder Traversal
Given the root of a binary tree, return the inorder traversal of its nodes' values.
 
Example 1:
Input: root = [1,null,2,3]
Output: [1,3,2]

Example 2:
Input: root = []
Output: []

Example 3:
Input: root = [1]
Output: [1]

Constraints:
The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100
*/



#include <iostream>
#include <vector>
#include <stack>
using namespace std; 

 // Definition for a binary tree node.
 struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };


//直接用dfs
class Solution1 {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        if(root == nullptr) return{};
        int depth;
        dfs(root, 0, ans);

        return ans;
    }
    void dfs(TreeNode* root, int depth, vector<int>& ans){
        if(root == nullptr) return;
        dfs(root->left, depth+1, ans);
        ans.push_back(root->val);
        dfs(root->right, depth+1, ans);
    }
};

//dfs概念但不用recursion 直接用stack
class Solution2 {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> stack; // 主要是用來存node 利用stack先進後出的特性去經過所有點
        vector<int> ans;
        TreeNode *cur = root; //去判斷當前選到的root 是否有left right

        while(cur || !stack.empty()){
            while(cur !=nullptr){    //先去判斷每次root的最左邊 在這過程順便把中間利用stack存起來
                stack.push(cur);
                cur = cur->left;
            }
            cur = stack.top();
            stack.pop();
            ans.push_back(cur->val);
            cur = cur->right; //按照inorder的順序邏輯 去檢查最左邊的右邊  LEFT ROOT RIGHT（此時最左邊會等同於中間）
        }
        return ans;
    }
};