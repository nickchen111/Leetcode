/*
935. Knight Dialer
*/

// TC:O(n) SC:O(10*n)
class Solution {
    long long M = 1e9+7;
public:
    int knightDialer(int n) {
        vector<vector<long long>> dp(n+1,vector<long long>(10,0));
        for(int i = 0; i<10; i++){
            dp[0][i] = 0;
            dp[1][i] = 1;
        }

        for(int i = 2; i<=n; i++){
            dp[i][1] = (dp[i-1][6]+dp[i-1][8])%M;
            dp[i][0] = (dp[i-1][6]+dp[i-1][4])%M;
            dp[i][2] = (dp[i-1][9]+dp[i-1][7])%M;
            dp[i][3] = (dp[i-1][4]+dp[i-1][8])%M;
            dp[i][4] = (dp[i-1][3]+dp[i-1][9]+dp[i-1][0])%M;
            
            dp[i][6] = (dp[i-1][1]+dp[i-1][7]+dp[i-1][0])%M;
            dp[i][7] = (dp[i-1][2]+dp[i-1][6])%M;
            dp[i][8] = (dp[i-1][1]+dp[i-1][3])%M;
            dp[i][9] = (dp[i-1][2]+dp[i-1][4])%M;
        }

        int res = 0;
        for(int i = 0; i<10; i++){
            res = (res+dp[n][i])%M;
        }

        return res;

    }
};
