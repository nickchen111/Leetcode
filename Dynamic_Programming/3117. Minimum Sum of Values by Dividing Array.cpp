// TC:O(n * m * lgU) SC:O(n * m * lgU)
class Solution {
public:
    int minimumValueSum(vector<int>& nums, vector<int>& andValues) {
        int n = nums.size(), m = andValues.size();
        // vector<vector<unordered_map<int,int>>> memo(n, vector<unordered_map<int,int>>(m));
        // 更好玩寫法 壓縮三位數成long long
        unordered_map<long long, int> memo;
        auto dfs = [&](auto &&dfs, int i, int j, int nd) -> int {
            if (i == n) return j == m ? 0 : INT_MAX/2;
            nd &= nums[i];
            if (j == m || nd < andValues[j]) return INT_MAX/2;
            long long mask = (long long)i << 36 | (long long)j << 32 | nd;
            // if(memo[i][j].count(nd)) return memo[i][j][nd];
            if (memo.count(mask)) return memo[mask];
            int ret = dfs(dfs, i + 1, j, nd);
            if (nd == andValues[j]) ret = min(ret, dfs(dfs, i + 1, j + 1, -1) + nums[i]);
            // return memo[i][j][nd] = ret;
            return memo[mask] = ret;
        };
        int ans = dfs(dfs, 0, 0, -1);
        return ans == INT_MAX/2 ? -1 : ans;
    }
};
