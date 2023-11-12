/*
513. Find Bottom Left Tree Value
*/

// BFS TC:O(n) SC:O(w)
class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        // how to find the deepset depth in the tree
        if(root == NULL) return 0;
        queue<TreeNode*> q;
        int res = 0;
        q.push(root);
        while(!q.empty()){
            int sz=q.size();
            res = q.front()->val;
            for(int i=0; i<sz; i++){
                TreeNode* cur = q.front();
                q.pop();
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
        }

        return res;
    }
};

//DFS TC:O(2*n) SC:O(2*lgn)
class Solution {
    bool flag=true;
    int res = 0;
public:
    int findBottomLeftValue(TreeNode* root) {
        //此題精華考點應是如何判斷到最底層 1.先DFS一次 O(n) 2.BFS邊做邊不斷更新答案
        int maxDepth = findDepth(root);
        DFS(root,maxDepth,1);

        return res;
    }
    int findDepth(TreeNode* root){
        if(root == NULL) return 0;
        return 1+max(findDepth(root->left),findDepth(root->right));
    }
    void DFS(TreeNode* root,int maxDepth, int depth){
        if(root==NULL) return;
        if(root->left == NULL && root->right == NULL && depth == maxDepth && flag){
            flag = false;
            res = root->val;
            return;
        }

        DFS(root->left,maxDepth, depth+1);
        DFS(root->right,maxDepth, depth+1);
    }
};
