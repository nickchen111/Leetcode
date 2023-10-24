/*
111. Minimum Depth of Binary Tree
*/

//BFS for迴圈遍歷層  TC:O(n) SC:O(n)
class Solution {
    //BFS
public:
    int minDepth(TreeNode* root) {
        if(root == nullptr) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int depth = 1;
        while(!q.empty()){
            int n = q.size();
            for(int i = 0; i<n; i++){
                TreeNode* node = q.front();
                q.pop();
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
                if(node->left == nullptr && node->right == nullptr) return depth;
            }
            depth++;
        }

        return 0;
        
    }
};

//BFS pair來判斷階層
class Solution {
    //BFS
public:
    int minDepth(TreeNode* root) {
        if(root == nullptr) return 0;
        queue<pair<TreeNode*, int>> q;
        q.push({root,1});
        while(!q.empty()){
            int n = q.size();
            TreeNode* node = q.front().first;
            int depth = q.front().second;
            q.pop();
            if(node->left == nullptr && node->right == nullptr) return depth;
            if(node->left) q.push({node->left,depth+1});
            if(node->right) q.push({node->right,depth+1});
        }

        return -1;
    }
};
