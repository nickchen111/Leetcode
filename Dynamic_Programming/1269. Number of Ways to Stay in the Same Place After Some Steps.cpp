/*
1269. Number of Ways to Stay in the Same Place After Some Steps
*/

// TC:O(n^2) SC:O(n)
class Solution {
public:
    int numWays(int steps, int arrLen) {
        vector<long long> dp(min(arrLen, steps),0);
        dp[0] = 1;
        int M = 1e9+7;
        for(int i = 0; i < steps; i++){
            auto dp_tmp = dp;
            for(int j = 0; j < min(arrLen,steps/2+1); j++){
                dp[j] = (dp[j] + (j-1 < 0 ? 0 : dp_tmp[j-1]) + (j+1 >= min(arrLen,steps/2+1) ? 0 :  dp_tmp[j+1])) %M;
            }
        }

        return dp[0];
    }
};

/*
問你走了k步以後你還待在原點的可能性
每一步你可以待在原點也可以向左or向右走一步
n :dp[0] += dp[1]
n-1 : dp[1] = dp_prev[0] + dp_prev[2];
這題的優化就是不關心step/2+1的可能性 因為他肯定走不回來

*/
