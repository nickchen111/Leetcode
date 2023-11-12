/*
404. Sum of Left Leaves
*/

//Recursion with 分解問題
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        if(root == NULL) return 0;
        int sum = 0;
        if(root->left != NULL && root->left->left == NULL && root->left->right == NULL){
            sum = root->left->val;
        }


        return sum+sumOfLeftLeaves(root->left)+sumOfLeftLeaves(root->right);
    }
};

//BFS 
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        //BFS
        if(root== NULL) return 0;
        queue<pair<TreeNode*,int>> q;
        q.push({root,0});
        int sum = 0;
        while(!q.empty()){
            int sz = q.size();
            for(int i = 0; i<sz; i++){
                TreeNode* cur = q.front().first;
                int tag = q.front().second;
                q.pop();
                if(tag == 1 && cur->left == NULL && cur->right == NULL) sum+=cur->val;
                if(cur->left) q.push({cur->left,1});
                if(cur->right) q.push({cur->right,0});
            }
        }

        return sum;
    }
};
