/*
2400. Number of Ways to Reach a Position After Exactly k Steps
*/

// DP: TC:O(n*k) SC:O(n*k)
class Solution {
    using LL = long long;
    LL M = 1e9 + 7;
public:
    int numberOfWays(int startPos, int endPos, int k) {
        
        if(abs(endPos - startPos) > k) return 0;

        vector<vector<LL>> dp(k+1, vector<LL>(2*k+1));
        
        LL offset = k;
        dp[0][0+offset] = 1;

        for(int t = 1; t <= k; t++){
            for(int p = -k; p <= k; p++){
                if(p-1 >= -k) dp[t][p+offset] = (dp[t][p+offset] + dp[t-1][p-1+offset]) % M;
                if(p+1 <= k) dp[t][p+offset] = (dp[t][p+offset] + dp[t-1][p+1+offset]) % M;
            }
        }

        return dp[k][abs(endPos-startPos) + offset];
        
    }
};




/*
點走到點 在一條座標上(不包含負數)  限定走的步數 問有多少種方法可以走到指定地點
dp[t][p] 從原點走到p這個位置 總共走了t步的可能性
dp[t][p] = dp[t-1][p-1] + dp[t+1][p+1];
只在乎的是-k~+k的範圍 所以取位置只需要考慮這段就好
*/
