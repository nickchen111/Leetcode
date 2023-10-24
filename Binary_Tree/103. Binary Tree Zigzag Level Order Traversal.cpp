/*
103. Binary Tree Zigzag Level Order Traversal
*/


//此題是自己解出來的 其他語言有些解答是使用bool true or false 
//bfs tc: on() sc: o(n)
class Solution1 {
public:
//bfs queue
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if(root == nullptr) return {};
        vector<vector<int>> ans;
        queue<TreeNode*> q;
        vector<int> temp;
        q.push(root);
        int d = 0;
        while(!q.empty()){
            int n = q.size();
            for(int i = 0; i < n; i++){
                TreeNode *node = q.front();
                q.pop();
                temp.push_back(node->val);
                if(node -> left) q.push(node->left);
                if(node -> right) q.push(node->right);     
            }
            if(d % 2 != 0){
                reverse(temp.begin(), temp.end());
                }    
            ans.push_back(temp);
            temp.clear();
            d++;
        }
        return ans;
    }
};

//DFS TC:O(n) SC:O(lgn)
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if(root == nullptr) return {};
        vector<vector<int>> res;
        int depth = 0;
        traverse(root, 0,  ans);
        for(int i = 0; i < res.size(); i++){
            if(i % 2 != 0){
                reverse(res[i].begin(), res[i].end());
            }
        }
        
        return res;
    }
    void traverse(TreeNode* root, int depth, vector<vector<int>>& res){
        if(root == nullptr) return;
        while(res.size() <= depth) res.push_back({});
        res[depth].push_back(root->val);
        traverse(root->left, depth+1, res);
        traverse(root->right, depth+1, res); 
    }
};




//BFS +用bool判斷到哪層 結合insert TC:O(n) SC:O(w)
class Solution {
public:
    vector<vector<int> > zigzagLevelOrder(TreeNode* root) {
        if (root == NULL) {
            return {};
        }
        vector<vector<int> > res;
        queue<TreeNode*> q;
        q.push(root);
        bool leftToRight = true;

        while (!q.empty()) {
            int sz = q.size();
            vector<int> temp;
            for (int i = 0; i < sz; i++) {
                TreeNode* cur = q.front();
                q.pop();
                if(leftToRight) temp.push_back(cur->val);
                else temp.insert(temp.begin(),cur->val);
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
            
            leftToRight = !leftToRight;
            res.push_back(temp);
        }
        return res;
    }
};
