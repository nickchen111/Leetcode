/*
107. Binary Tree Level Order Traversal II
*/

// DFS without using reverse  TC:O(n) SC:O(lgn)
class Solution {
public:
    //先計算出深度 就可以倒著將最上層的答案裝進最底層
    int depth(TreeNode *root) {
        if (!root) return 0;
        return max(depth(root->left),depth(root->right))+1;
    }

    void levelOrder(vector<vector<int>> &ans, TreeNode *node, int level) {
        if (!node) return;
        ans[level].push_back(node->val);
        levelOrder(ans,node->left,level-1);
        levelOrder(ans,node->right,level-1);
    }

    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        int d = depth(root);
        vector<vector<int>> ans(d,vector<int> {});
        levelOrder(ans,root,d-1);
        return ans;
    }
};

//DFS + reverse
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        if(root == NULL) return {};
        vector<vector<int>> res;
        traverse(root,res,0);
        reverse(res.begin(),res.end());
        return res;
    }

    void traverse(TreeNode* root, vector<vector<int>>& res, int depth){
        if(root == NULL) return;

        while(res.size() <= depth) res.push_back({});
        traverse(root->left,res,depth+1);
        traverse(root->right,res,depth+1);
        res[depth].push_back(root->val);
    }
};

//BFS + insert TC:O(n) SC:O(w)
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        if(root == NULL) return {};
        vector<vector<int>> res;
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()){
            int sz = q.size();
            vector<int> temp;
            for(int i = 0; i < sz; i++){
                TreeNode* cur = q.front();
                q.pop();
                temp.push_back(cur->val);
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
            res.insert(res.begin(),temp);
        }
        return res;
    }
}; 
