/*
1043. Partition Array for Maximum Sum
*/

// TC:O(n^2) SC:O(n)
class Solution {
    using LL = long long;
public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        int n = arr.size();
        arr.insert(arr.begin(), -1);
        vector<LL> dp(n+1);
        dp[0] = 0;
        dp[1] = arr[1];
        for(int i = 2; i <= n; i++){
            int maxVal = arr[i];
            for(int j = 1; j <= k; j++){
                if(i-j >= 0){ 
                    dp[i] = max(dp[i], dp[i-j] + maxVal*j);
                    maxVal = max(maxVal, arr[i-j]);
                }
            }
        }

        return dp[n];
    }
};

/*
此題要將數組切割成許多子數組 
子數組的最大值會代表整個數組 並且乘以數組長度 問說所有切割數組加總最大可以是多少
dp[i] 截至i為止怎麼切割最大 
k = 3
dp[i] = dp[i-1] + nums[i]*1, dp[i-2]+nums[x]*2, dp[i-3]+nums[x]*3 
如果她比前兩位的大 何樂而不為 跟他們並 如果沒有比較大 自成一國
*/
