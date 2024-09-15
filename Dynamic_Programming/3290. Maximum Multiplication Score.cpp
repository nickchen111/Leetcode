/*
3290. Maximum Multiplication Score
*/

// TC:O(n*5) SC:O(n*5)
class Solution {
    using LL = long long;
public:
    long long maxScore(vector<int>& a, vector<int>& b) {
        int n = b.size();
        vector<vector<LL>> dp(n+1, vector<LL>(5, LLONG_MIN/3));
        b.insert(b.begin(), -1);
        a.insert(a.begin(), -1);
        dp[0][0] = 0;
        for(int i = 1; i <= n; i++){
            for(int j = 0; j <= 4; j++){
                if(i < j) break;
                dp[i][j] = dp[i-1][j];
                if(j)
                    dp[i][j] = max(dp[i][j], dp[i-1][j-1] + (LL)a[j]*b[i]);
            }
        }

        return dp[n][4];
    }
};
