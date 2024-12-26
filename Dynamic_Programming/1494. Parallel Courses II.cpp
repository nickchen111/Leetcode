/*
1494. Parallel Courses II
*/

// TC:O(3^n) SC:O(2^n)
class Solution {
public:
    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
        vector<int> pre(n);
        for(int i = 0; i < relations.size(); i++) {
            pre[relations[i][1] - 1] |= 1 << (relations[i][0] - 1);
        }
        int u = (1<<n) - 1;
        vector<int> dp(1<<n, INT_MAX/2);
        dp[0] = 0;
        for(int i = 0; i < (1<<n); i++) {
            int ci = u ^ i, i1 = 0;
            // 檢查是否所選的補集都有包含
            for(int j = 0; j < n; j++) {
                if(((i >> j) & 1) && (pre[j] | ci) == ci) {
                    i1 |= (1 << j);
                }
            }
            if(__builtin_popcount(i1) <= k) {
                dp[i] = min(dp[i], 1 + dp[i ^ i1]);
                continue;
            }
            
            for(int j = i1; j; j = (j-1) & i1) {
                if(__builtin_popcount(j) == k) {
                    dp[i] = min(dp[i], 1 + dp[i^j]);
                }
            }
        }

        return dp[u];
        /*
        遞歸 TC:O(3^n) SC:O(2^n)
        vector<int> memo(1<<n, -1);
        int u = (1<<n) - 1; // 全集
        auto dfs = [&](auto &&dfs, int i) -> int {
            if(i == 0) return 0;
            if(memo[i] != -1) return memo[i];
            int ci = u ^i, i1 = 0;
            for(int j = 0; j < n; j++) {
                if(((i >> j) & 1) && (pre[j] | ci) == ci) {
                    i1 |= (1 << j);
                }
            }

            if(__builtin_popcount(i1) <= k) return memo[i] = 1 + dfs(dfs, i ^ i1);
            int ret = INT_MAX;
            for(int j = i1; j; j = (j-1) & i1) {
                if(__builtin_popcount(j) == k) {
                    ret = min(ret, 1 + dfs(dfs, i ^ j));
                }
            }

            return memo[i] = ret;
        };
        return dfs(dfs, u);
        */
    }
};
