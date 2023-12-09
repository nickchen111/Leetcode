/*
2786. Visit Array Positions to Maximize Score
*/

// TC:O(n) SC:O(2*n)
class Solution {
public:
    long long maxScore(vector<int>& nums, int x) {
        int n = nums.size();
        vector<vector<long long>> dp(n, vector<long long>(2, INT_MIN));
        if(nums[0] % 2 == 1){
            dp[0][1] = nums[0];
        }
        else {
            dp[0][0] = nums[0];
        }
        
        long long res = 0;
        for(int i = 1; i < n ; i++){
            //不取的狀態
            dp[i][0] = dp[i-1][0];
            dp[i][1] = dp[i-1][1];
            //取的話
            if(nums[i] % 2 == 1){
                dp[i][1] = max(dp[i][1], max(dp[i-1][1] + nums[i], dp[i-1][0] + nums[i] - x));
            }
            else {
                dp[i][0] = max(dp[i][0], max(dp[i-1][0] + nums[i], dp[i-1][1] + nums[i] - x));
            }
        }

        res = max(dp[n-1][0], dp[n-1][1]);
        return res;
    }
};

/*
此題說 你可以從起點走到後面任意點 可以累積分數 
但是如果這點跟你的上一點奇偶性不同 你就會失去x 分 
問最多能得到幾分
dp[i][j] : 走到i element時能得到的最大分 並且奇偶性是 % 2 == j

*/
