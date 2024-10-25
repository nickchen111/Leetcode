/*
375. Guess Number Higher or Lower II
*/

// Iterative TC:O(n*3) SC:O(n^2)
class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int>> dp(n+5, vector<int>(n+5, 0));
        for(int i = 0; i <= n; i++) {
            dp[i][i] = 0;
            if(i+1 < n) dp[i][i+1] = i+1;
        }

        for(int len = 2; len <= n; len ++) {
            for(int i = 1; i + len -1 <= n; i++) {
                int j = i + len -1;
                dp[i][j] = INT_MAX/2;
                for(int k = i; k <= j; k++) {
                    int cur = max(dp[i][k-1], dp[k+1][j]) + k;
                    dp[i][j] = min(dp[i][j], cur);
                }
            }
        }

        return dp[1][n];
        
    }
};

// Recursion TC:O(n*3) SC:O(n^2)
class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int>> memo(n+1, vector<int>(n+1,INT_MAX/2));
        
        function<int(int l, int r)> DFS = [&](int l, int r) -> int {
            if(l >= r) return 0;
            if(memo[l][r] != INT_MAX/2) return memo[l][r];
            
            int res = INT_MAX/2;
            for(int i = l; i <= r; i++) {
                int cur = max(DFS(l, i-1), DFS(i+1,r)) + i;
                res = min(res, cur);
            }

            return memo[l][r] = res;
        };

        return DFS(1,n);
    }
};
