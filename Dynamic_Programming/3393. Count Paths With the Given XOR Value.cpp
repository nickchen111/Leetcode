/*
3393. Count Paths With the Given XOR Value
*/

// TC:O(m*n*16) SC:O(n*16)
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int countPathsWithXorValue(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        // vector<vector<vector<LL>>> dp(m, vector<vector<LL>>(n, vector<LL>(16,0)));
        vector<vector<LL>> dp(n,vector<LL>(16));
        dp[0][grid[0][0]] = 1;
        for(int i = 0; i < m; i++) {
            vector<vector<LL>> dp_new(n,vector<LL>(16));
            for(int j = 0; j < n; j++) {
                if(j + 1 < n) {
                    for(int t = 0; t < 16; t++) {
                        if(dp[j][t]) {
                            dp[j+1][t^grid[i][j+1]] = (dp[j+1][t^grid[i][j+1]] + dp[j][t]) % MOD;
                        }
                    }
                }
                if(i+1 < m) {
                    for(int t = 0; t < 16; t++) {
                        if(dp[j][t]) {
                            dp_new[j][t^grid[i+1][j]] = (dp_new[j][t^grid[i+1][j]] + dp[j][t]) % MOD;
                        }
                    }
                }
            }
            if(i != m-1) dp = dp_new;
        }
        return dp[n-1][k];
    }
};
