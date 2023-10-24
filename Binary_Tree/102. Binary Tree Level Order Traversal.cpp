/*
102. Binary Tree Level Order Traversal
*/

// BFS TC:O(n) SC:O(w)
class Solution {
//bfs 用 queue
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(root == nullptr) return {};
        vector<vector<int>> result;
        queue<TreeNode*> q;
        vector<int> temp;
        q.push(root);
        while(!q.empty()){
            int n = q.size();
            for(int i = 0; i < n; i++){
                 TreeNode *node = q.front();
                 q.pop();
                 temp.push_back(node->val);
                 if(node->left) q.push(node->left);
                 if(node->right) q.push(node->right);
            }
            result.push_back(temp);
            temp.clear();
        }

        return result;
    }
};

// DFS TC:O(n) SC:O(lgn)
class Solution {
//dfs
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(root == nullptr) return {};
        vector<vector<int>> result;
        
        dfs(root, 0, result);

        return result;
    }
    void dfs(TreeNode* root, int depth, vector<vector<int>>& result){
        if(root == nullptr) return;   
        ////此操作代表depth意思是我要加入第幾行 如果當前沒那麼多行 我就要push多少進去
        while(result.size() <= depth) result.push_back({}); //因為不知道有多深 所以須寫這條判斷式 將vector裡面新增一格來存放這層的元素 
        result[depth].push_back(root->val);
        dfs(root->left, depth+1, result);
        dfs(root->right, depth+1, result);
    }
};

//一開始自己寫的 用bfs without queue
class Solution {
//bfs without queue
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(root == nullptr) return {};
        vector<TreeNode*> cur, next;
        vector<vector<int>> result;
        vector<int> temp;
        
        cur.push_back(root);
        while(!cur.empty()){
            for(auto node:cur){
                temp.push_back(node->val);
                if(node->left) next.push_back(node->left);
                if(node->right) next.push_back(node->right);

            }
            result.push_back(temp);
            temp.clear();
            cur.swap(next);
            next.clear();
        }
        return result;
    }
};

