/*
664. Strange Printer
*/

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
