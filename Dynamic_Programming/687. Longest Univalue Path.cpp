/*
687. Longest Univalue Path
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int longestUnivaluePath(TreeNode* root) {
        int res = 0;
        auto dfs = [&](auto &&dfs, TreeNode* node) -> pair<int,int> {
            if(node == NULL) return {0, 1001};
            auto left = dfs(dfs, node->left);
            auto right = dfs(dfs, node->right);
            int cur = node->val;
            int ret = 1;
            if(cur == left.second && cur == right.second) {
                res = max(res, left.first + right.first);
            }
            else if(cur == left.second) {
                res = max(res, left.first);
            }
            else if(cur == right.second) {
                res = max(res, right.first);
            }
            
            return {max(left.second == cur ? left.first : 0, right.second == cur ? right.first : 0) + ret, cur};
        };

        dfs(dfs, root);
        return res;
    }
};
