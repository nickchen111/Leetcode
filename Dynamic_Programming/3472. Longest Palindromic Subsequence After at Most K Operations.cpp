// TC:O(n^2 * k) SC:O(n^2 * k)
class Solution {
public:
    int longestPalindromicSubsequence(string s, int k) {
        int n = s.size();
        vector dp(n, vector<vector<int>>(n, vector<int>(k+1, 0)));
        for(int i = 0; i < n; i++) {
            for(int t = 0; t <= k; t++)
                dp[i][i][t] = 1;
        }
        for(int i = n-2; i >= 0; i--) {
            for(int j = i + 1; j < n; j++) {
                for(int t = 0; t <= k; t++) {
                    dp[i][j][t] = max(dp[i+1][j][t], dp[i][j-1][t]); // 不選
                    int cost = 0;
                    if(s[i] != s[j]) {
                        cost = min((s[i] - s[j] + 26) % 26, (s[j] - s[i] + 26) % 26);
                    }
                    
                    if(t >= cost) {
                        dp[i][j][t] = max(dp[i][j][t], dp[i+1][j-1][t - cost] + 2);
                        // else dp[i][j][t] = max(dp[i][j][t], 2);
                    }
                }
            }
        }
        return dp[0][n-1][k];
        
        /*
        遞歸
        vector memo(n, vector<vector<int>>(n, vector<int>(k+1, 0)));
        auto dfs = [&](auto &&dfs, int l, int r, int cnt) -> int {
            if(l > r) return 0;
            if(l == r) return 1;
            int &ret = memo[l][r][cnt];
            if(ret) return ret;
            ret = max(dfs(dfs, l+1, r, cnt), dfs(dfs, l, r-1, cnt));
            int cost = 0;
            cost = min((s[l] - s[r] + 26) % 26, (s[r] - s[l] + 26) % 26);
            if(s[l] == s[r]) {
                ret = max(ret, dfs(dfs, l+1, r-1, cnt) + 2);
            }
            else if(cost <= cnt) ret = max(ret, dfs(dfs, l+1, r-1, cnt - cost) + 2);
            return ret;
        };
        return dfs(dfs, 0, n-1, k);
        */
    }
};
