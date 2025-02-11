/*
1639. Number of Ways to Form a Target String Given a Dictionary
*/

// TC:O(n*m) SC:O(n*m) -> O(n)
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int numWays(vector<string>& words, string target) {
        int m = words.size(), n = target.size(), k = words[0].size();
        vector<vector<LL>> mp(words[0].size(), vector<LL>(26));
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < words[i].size(); j++) {
                mp[j][words[i][j] - 'a'] += 1;
            }
        }
        vector<LL> dp(n+1);
        dp[0] = 1;
        for(int i = 0; i < k; i++) {
            LL prev = dp[0];
            for(int j = 0; j < n; j++) {
                LL tmp = dp[j+1];
                dp[j+1] = (dp[j+1] + prev * mp[i][target[j] - 'a']) % MOD;
                prev = tmp;
            }
        }
        return dp[n];
        /*
        二維 遞推
        vector dp(k+1, vector<LL>(n+1));
        dp[0][0] = 1;
        for(int i = 0; i < k; i++) {
            dp[i+1][0] = 1;
            for(int j = 0; j < n; j++) {
                dp[i+1][j+1] = (dp[i][j+1] + dp[i][j] * mp[i][target[j] - 'a']) % MOD;
            }
        }
        return dp[k][n];
        */
        /*
        遞歸
        vector memo(k, vector<LL>(n, -1));
        auto dfs = [&](auto &&dfs, int i, int j) -> LL {
            if (j == n) return 1;  
            if (i == k) return 0; 
            if(memo[i][j] != -1) return memo[i][j];
            LL ret = dfs(dfs, i+1, j); // 不選
            if(mp[i][target[j] - 'a']) {
                ret = (ret + dfs(dfs, i+1, j+1) * mp[i][target[j] - 'a']) % MOD;
            }
            return memo[i][j] = ret;
        };
        return dfs(dfs, 0, 0);
        */
    }
};
/*
可以先預處理 每個index之前能有哪些字母可以選
dp[i][j] 處理到第i個target的字，用到第j個index 會有多少種方法組成
*/
