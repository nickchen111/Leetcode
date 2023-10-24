/*
515. Find Largest Value in Each Tree Row
*/


//BFS TC:O(n) SC:O(n)
class Solution {
    vector<int> res;
public:
    vector<int> largestValues(TreeNode* root) {
        //BFS
        if(root == NULL) return {};
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()){
            int sz = q.size();
            int maxNum = INT_MIN;
            for(int i = 0; i<sz; i++){
                TreeNode* cur = q.front();
                q.pop();
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
                maxNum = max(maxNum,cur->val);
            }
            res.push_back(maxNum);
        }

        return res;
        
    }
};
