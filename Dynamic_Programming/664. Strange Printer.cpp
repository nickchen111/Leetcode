/*
664. Strange Printer
*/

// 遞歸 + 遞推 TC:O(n^3) SC:O(n^2)
class Solution {
public:
    int strangePrinter(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n,INT_MAX));
        dp[n-1][n-1] = 1;
       
        for(int i = n-2; i >= 0; i--) {
            dp[i][i] = 1;
            dp[i][i+1] = s[i] == s[i+1] ? 1 : 2;
            for(int j = i + 2; j < n; j++) {
                if(s[i] == s[j]) {
                    dp[i][j] = dp[i][j-1];
                }
                else {
                    for(int k = i; k < j; k++) {
                        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j]);
                    }
                }
            }
        }

        return dp[0][n-1];
        // vector<vector<int>> memo(n, vector<int>(n,-1));
        // function<int(int, int)> dfs = [&](int l, int r) -> int {
        //     if(l == r) return 1;
        //     if(l == r-1) {
        //         return s[l] == s[r] ? 1 : 2;
        //     }
        //     if(memo[l][r] != -1) return memo[l][r];
        //     int res = INT_MAX;
        //     if(s[l] == s[r]) {
        //         res = min(res, dfs(l, r-1));
        //     }
        //     else {
        //         for(int i = l; i < r; i++) {
        //             res = min(res, dfs(l,i) + dfs(i+1, r));
        //         }
        //     }

        //     return memo[l][r] = res;
        // };

        // return dfs(0,n-1);
    }
};

// TC:O(n^3) SC:O(n^2)
class Solution {
public:
    int strangePrinter(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, INT_MAX/2));
        for(int i = 0; i < n; i++){
            dp[i][i] = 1;
            if(i+1 < n){
                if(s[i] == s[i+1]){
                    dp[i][i+1] = 1;
                }
                else dp[i][i+1] = 2;
            }
        }
        

        for(int len = 3; len <= n; len++){
            for(int i = 0; i + len -1 < n; i++){
                int j = i + len - 1;
                //x x x 
                dp[i][j] = 1 + dp[i+1][j];
                for(int k = i+1; k < j; k++){
                    if(s[i] == s[k]){
                        dp[i][j] = min(dp[i][j] , dp[i][k-1] + dp[k+1][j]);
                    }
                }

                if(s[i] == s[j]){
                    dp[i][j] = min(dp[i][j] , dp[i][j-1]);
                }
            }
        }

        return dp[0][n-1];
    }
};

// 像是區間DP
// abcdedcba
// aaaaaa
