/*
199. Binary Tree Right Side View

*/

 // 一開始的寫法
class Solution1 {
public:
//不用queue 好難寫==
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        vector<TreeNode*> cur, next;
        if(root == nullptr) return {};
        cur.push_back(root);
        while(!cur.empty()){
            int n = cur.size();
            for(int i = 0; i < n; i++){
                if(cur[i]->left) next.push_back(cur[i]->left);
                if(cur[i]->right) next.push_back(cur[i]->right);
                if(i == n-1) result.push_back(cur[i]->val);
            }
            cur.swap(next);
            next.clear();
        }
        return result;
    }
};

//BFS TC:O(n) SC:O(w)
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        //BFS
        if(root == NULL) return {};
        vector<int> res;
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()){
            int sz = q.size();
            for(int i = 0; i<sz; i++){
                TreeNode* cur = q.front();
                q.pop();
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
                //這步是重點
                if(i == sz-1) res.push_back(cur->val);
            }
        }

        return res;
    }
};

//DFS TC:O(n) SC:O(lgn)
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        //DFS
        if(root == NULL) return {};
        vector<int> res;
        traverse(root,res,0);
        return res;
    }

    void traverse(TreeNode* root, vector<int>& res, int depth){
        if(root == NULL) return;
        if(res.size() == depth) res.push_back(root->val);
        traverse(root->right,res,depth+1);
        traverse(root->left,res,depth+1);
    }
};
