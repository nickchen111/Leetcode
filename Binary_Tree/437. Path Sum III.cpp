/*
437. Path Sum III
*/

 
// 最佳解 Hash Map + Presum: TC:O(n) SC:O(n) 子節點要父節點訊息
class Solution {
    using LL = long long;
public:
    int pathSum(TreeNode* root, int targetSum) {
        int res = 0;
        function<void(TreeNode* node, LL sum, unordered_map<LL,LL>& map)> dfs = [&](TreeNode* node, LL sum, unordered_map<LL,LL>& map) -> void{
            if(node == NULL) {
                return;
            }
            sum += node->val;
            res += map[sum - targetSum];
            map[sum] += 1;
            dfs(node->left, sum, map);
            dfs(node->right, sum, map);
            map[sum] -= 1;
        };
        unordered_map<LL, LL> map;
        map[0] = 1;
        dfs(root, 0, map);
        return res;
    }
};

// 次佳解  父節點要子節點訊息
class Solution {
    using LL = long long;
public:
    int pathSum(TreeNode* root, int targetSum) {
        int res = 0;
        function<vector<LL>(TreeNode* node)> dfs = [&](TreeNode* node) -> vector<LL> {
            if(node == NULL) return {};
            vector<LL> left = dfs(node->left);
            vector<LL> right = dfs(node->right);
            vector<LL> cur = {node->val};
            if(node->val == targetSum) res += 1; 
            for(auto &l : left) {
                if(node->val + l == targetSum) {
                    res += 1;
                }
                cur.push_back(node->val + l);
            }
            for(auto &r : right) {
                if(node->val + r == targetSum) {
                    res += 1;
                }
                cur.push_back(node->val + r);
            }

            return cur;
        };
        dfs(root);
        return res;
    }
};
