/*
637. Average of Levels in Binary Tree
*/

//此題要去計算每一層的總和平均值
//人生好難
//binary tree 題型 可用bfs or dfs

//BFS TC:(n) SC:O(w)
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> res;
        queue<TreeNode*> q;
        if(root == NULL) return {};
        q.push(root);

        while(!q.empty()){
            double sz =q.size();
            double sum = 0;
            for(int i =0; i<sz; i++){
                TreeNode* cur = q.front();
                q.pop();
                sum+=cur->val;
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
            res.push_back(sum/sz);
        }

        return res;
    }
};

//DFS TC:O(n) SC:O(lgn)
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        //DFS
        vector<pair<long,int>> count;
        DFS(root,count,0);
        vector<double> res;
        for(int i = 0; i < count.size(); i++){
            res.push_back((double)count[i].first/count[i].second);
        }

        return res;
    }

    void DFS(TreeNode* root, vector<pair<long,int>>& count, int depth){
        if(root == NULL) return;

        int cur = root->val;
        if(count.size() <= depth) count.push_back({cur,1});
        else {
            count[depth].first+=cur;
            count[depth].second+=1;
        }
        DFS(root->left, count,depth+1);
        DFS(root->right, count,depth+1);
    }
};



