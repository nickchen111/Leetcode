/*
144. Binary Tree Preorder Traversal
*/

// Stack to simulate recursion TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> stack;

        TreeNode* cur = root;
        while(!stack.empty() || cur != NULL){
            while(cur != NULL){
                res.push_back(cur->val);
                stack.push(cur);
                cur = cur->left;
            }
            cur = stack.top();
            stack.pop();
            cur = cur->right;
        }

        return res;
    }
};


// 分解問題 
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

// DFS TC:O(n) SC:O(lgn)
class Solution {
    vector<int> res;
public:
    vector<int> preorderTraversal(TreeNode* root) {
        //DFS
        DFS(root);

        return res;
    }
    void DFS(TreeNode* root){
        if(root == NULL) return;

        res.push_back(root->val);
        DFS(root->left);
        DFS(root->right);
    }
};
