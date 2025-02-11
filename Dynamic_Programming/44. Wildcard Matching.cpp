// TC:O(n*m) SC:O(n*m)
class Solution {
public:
    bool isMatch(string s, string p) {
        // 問說兩個字串是否完全一樣
        int m = s.size(), n = p.size();
        vector dp(m+1, vector<bool>(n+1, false));
        dp[0][0] = true;
        for(int j = 1; j <= n; j++) {
            if(p[j-1] == '*') dp[0][j] = true;
            else break;
        }
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(p[j] == '?' || s[i] == p[j]) {
                    dp[i+1][j+1] = dp[i][j];
                }
                else if(p[j] == '*') {
                    dp[i+1][j+1] = dp[i][j] || dp[i+1][j] || dp[i][j+1];
                }
            }
        }
        return dp[m][n];
        /*
        遞歸
        vector memo(m, vector<int>(n, -1));
        auto dfs = [&](auto &&dfs, int i, int j) -> bool {
            if(i < 0 && j < 0) return true;
            if(j < 0) return false;
            if(i < 0) {
                return p[j] == '*' ? dfs(dfs, i, j-1) : false;
            }
            if(memo[i][j] != -1) return memo[i][j];
            if(p[j] == '?' || s[i] == p[j]) {
                return memo[i][j] = dfs(dfs, i-1, j-1);
            }
            if(p[j] == '*') return memo[i][j] = dfs(dfs, i-1, j-1) || dfs(dfs, i, j-1) || dfs(dfs,i-1,j);
            return memo[i][j] = false;
        };
        return dfs(dfs, m-1, n-1);
        */
    }
};
