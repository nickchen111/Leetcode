/*
3176. Find the Maximum Length of a Good Subsequence I
*/

// TC:O(k*n^2) SC:O(n*k)
class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(k+1,INT_MIN/2));
        for(int i = 0; i < n; i++){
            dp[i][0] = 1;
        }
        int res = 1;
        for(int i = 1; i < n; i++){
            for(int j = i-1; j >= 0; j--){
                for(int t = 0; t <= min(k,j); t++){
                    if(nums[i] != nums[j]){
                        if(t+1 <= k){
                            dp[i][t+1] = max(dp[j][t]+1, dp[i][t+1]);
                            res = max(res, dp[i][t+1]);
                        }
                    }
                    else dp[i][t] = max(dp[j][t]+1, dp[i][t]);
                    res = max(res, dp[i][t]);
                }
            }
        }
        
        return res;
        
        
    }
};

/*
最多只能有k個相鄰不同的元素 並且你可以選擇subsequence -> dp
dp[i][k] 走到i為止 當下選 可以產生的符合條件的最大值
k <= 25
*/
