/*
94. Binary Tree Inorder Traversal
*/


//DFS inorder traverse
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        // DFS
        vector<int> res;
        DFS(root,res);
        return res;
    }
    void DFS(TreeNode* root, vector<int>& res){
        if(root== NULL) return;
        DFS(root->left,res);
        res.push_back(root->val);
        DFS(root->right,res);
    }
};

//直接用stack simulate recursion
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
