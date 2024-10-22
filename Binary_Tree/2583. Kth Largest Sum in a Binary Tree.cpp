/*
2583. Kth Largest Sum in a Binary Tree
*/


// TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long kthLargestLevelSum(TreeNode* root, int k) {
        if(root == NULL) return -1;
        vector<LL> depth;
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()) {
            depth.push_back(0);
            int sz = q.size();
            while(sz--) {
                TreeNode* cur = q.front();
                q.pop();
                depth.back() += (LL)cur->val;
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
        }
        if(depth.size() < k) return -1;
        
        // 7個元素 要求第二大 也就是第六小 x x x x x x x -> idx = 5
        int n = depth.size();
        k = n - k;
        std::nth_element(depth.begin(), depth.begin() + k, depth.end());

        return depth[k];
    }
};
