/*
3196. Maximize Total Cost of Alternating Subarrays
*/

//  TC:O(n) SC:O(n*2)
class Solution {
    using LL = long long;
public:
    long long maximumTotalCost(vector<int>& nums) {
        int n = nums.size();
        vector<vector<LL>> dp(n, vector<LL>(2,LLONG_MIN/2));
        dp[0][0] = nums[0];
        for(int i = 1; i < n; i++){
            if(nums[i] >= 0){
                dp[i][0] = max(dp[i-1][0] + (LL)nums[i], dp[i-1][1] + (LL)nums[i]);
            }
            else {
                dp[i][0] = max(dp[i-1][0] + (LL)nums[i], dp[i-1][1] + (LL)nums[i]);
                dp[i][1] = dp[i-1][0] - (LL)nums[i];
            }
        }
        
        return max(dp[n-1][0], dp[n-1][1]);
    }
};

/*
切割數組 求出最大subarray總和
如果是負數 就會希望跟前面組成正數可能 
子數組偶數位可以變號
負數前面有正數 就可以變正數
dp[i][j]: 走到i的時候數組的最大值可以是多少 並且前面是有變號還是沒變號 0 -> 沒變號 ,1 -> 有變號
*/
