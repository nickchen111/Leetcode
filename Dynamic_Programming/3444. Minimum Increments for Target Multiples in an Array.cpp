// TC:O(n * 3 ^m + 2^m * lgU) SC:O(n * 2^m)
class Solution {
    typedef long long LL;
public:
    int minimumIncrements(vector<int>& nums, vector<int>& target) {
        int m = target.size(), n = nums.size();
        vector<LL> lcms(1 << m);
        lcms[0] = 1; // 1 LCM任何數字都是ok的
        /*
        m * 2^m * lgU 的預處理 可以優化到2^m * lgU
        for(int i = 0; i < (1 << m); i++) {
            for(int j = 0; j < m; j++) {
                if((i >> j) & 1) {
                    lcms[i] = lcm(lcms[i ^ (1 << j)], target[j]);
                }
            }
        }
        */
        //藉由等比數列 + 二項式定理 推導出 時間複查度是2^m * lgU
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < (1 << i); j++) {
                lcms[j | (1 << i)] = lcm(lcms[j], target[i]); 
            }
        }
        /*
        遞歸 TC:O(n * 3 ^m + 2^m * lgU) SC:O(n * 2^m)
        vector memo(n, vector<LL>(1 << m, -1));
        auto dfs = [&](auto &&dfs, int i, int mask) -> int {
            if(mask == 0) return 0;
            if(i < 0) return INT_MAX;
            if(memo[i][mask] != -1) return memo[i][mask];
            int submask = mask;
            LL ret = dfs(dfs, i-1, mask); // 不選現在這個使用
            while(submask) {
                int remain = submask ^ mask;
                LL lcm = lcms[submask];
                ret = min(ret, dfs(dfs, i - 1, remain) + (lcm - (nums[i] % lcm)) % lcm);
                submask = (submask-1) & mask;
            }
            return memo[i][mask] = ret;
        };
        return dfs(dfs, n-1, (1 << m) - 1);
        */
        // 遞推 TC:O(n * 3 ^m + 2^m * lgU) SC:O(n * 2^m)
        vector dp(n+1, vector<LL>(1 << m));
        fill(dp[0].begin() + 1, dp[0].end(), INT_MAX / 2);
        for(int i = 0; i < n; i++) {
            for(int j = 1; j < (1 << m); j++) {
                dp[i+1][j] = dp[i][j]; // 不選當下這個
                int submask = j;
                while(submask) {
                    int remain = submask ^ j;
                    LL lcm = lcms[submask];
                    dp[i+1][j] = min(dp[i+1][j], dp[i][remain] + (lcm - (nums[i] % lcm)) % lcm);
                    submask = (submask - 1) & j;
                }
            }
        }
        return dp[n][(1 << m) - 1];
    }
};
