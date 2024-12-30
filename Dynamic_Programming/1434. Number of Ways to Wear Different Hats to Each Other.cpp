/*
1434. Number of Ways to Wear Different Hats to Each Other
*/

// TC:O(n * maxVal * 2^n) maxVal = 40, SC:O(maxVal * 2^n) -> SC:O(2^n)
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int numberWays(vector<vector<int>>& hats) {
        int n = hats.size();
        // 一個帽子可以被多少個人使用
        int maxVal = 0; 
        for(auto &hat : hats)
            for(auto &h: hat)
                maxVal = max(maxVal, h);
        maxVal += 1;
        vector<int> htp(maxVal);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < hats[i].size(); j++) {
                htp[hats[i][j]] |= (1 << i);
            }
        }
        vector<LL> dp((1 << n));
        dp[0] = 1;
        for(int i = 0; i < maxVal; i++) {
            auto dp_tmp = dp;
            for(int mask = 0; mask < (1 << n); mask++) {
                for(int j = 0; j < n; j++) {
                    if(((mask >> j) & 1) == 0 && ((htp[i] >> j) & 1)) {
                        dp[mask | (1 << j)] = (dp[mask | (1 << j)] + dp_tmp[mask]) % MOD;
                    }
                }
            }
        }

        return dp[(1 << n) - 1];
        /*
        遞歸 TC:O(n * maxVal * 2^n) maxVal = 40, SC:O(maxVal * 2^n)
        // 1 << n 狀態 每個這些被選中的人會有多少種方案數量
        vector<vector<LL>> memo((1 << n), vector<LL>(maxVal, -1));
        auto dfs = [&](auto &&dfs, int mask, int j) -> LL {
            if(mask == (1 << n) - 1) return 1;
            if(j == maxVal) return 0;
            if(memo[mask][j] != -1) return memo[mask][j];
            LL ret = dfs(dfs, mask, j + 1);
            for(int i = 0; i < n; i++) {
                if(((mask >> i) & 1) == 0 && ((htp[j] >> i) & 1)) {
                    ret = (ret + dfs(dfs, mask | (1 << i), j + 1)) % MOD;
                }
            }

            return memo[mask][j] = ret;
        };

        return dfs(dfs, 0, 0);
        */
    }
};
