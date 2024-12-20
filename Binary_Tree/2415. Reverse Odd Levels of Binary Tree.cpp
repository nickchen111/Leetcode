/*
2415. Reverse Odd Levels of Binary Tree
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    TreeNode* reverseOddLevels(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        int depth = -1;
        while(!q.empty()) {
            depth += 1;
            int sz = q.size();
            vector<TreeNode*> nodes; 
            while(sz--) {
                auto node = q.front();
                q.pop();
                if(depth % 2) {
                    nodes.push_back(node);
                }
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            int m = nodes.size();
            if(depth % 2) {
                for(int i = 0; i < nodes.size() / 2; i++) {
                    int tmp = nodes[i] -> val;
                    nodes[i] -> val = nodes[m-1-i] -> val;
                    nodes[m-1-i] -> val = tmp;
                }
            }
        }

        return root;
        
    }
};
