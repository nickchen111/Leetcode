/*
1302. Deepest Leaves Sum
*/


// BFS
class Solution {
public:
    int deepestLeavesSum(TreeNode* root) {
        //找出深度...BFS
        if(root == NULL) return 0;
        queue<TreeNode*> q;
        int res;
        q.push(root);
        while(!q.empty()){
            int sz=q.size();
            int sum = 0;
            for(int i=0; i<sz; i++){
                TreeNode* cur = q.front();
                q.pop();
                sum+=cur->val;
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
            res = sum;
        }

        return res;
    }
};
