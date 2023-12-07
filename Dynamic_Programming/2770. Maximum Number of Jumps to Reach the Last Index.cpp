/*
2770. Maximum Number of Jumps to Reach the Last Index
*/


// TC:O(n^2) SC:O(n)
class Solution {
public:
    int maximumJumps(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> dp(n,-1);
        dp[0] = 0;
        for(int i = 1; i < n; i++){
            for(int j = i-1; j >= 0; j--){
                if(dp[j] == -1) continue;
                if(abs(nums[i] - nums[j]) <= target){
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        
        return dp[n-1];

    }
};

/*
此題有點類似原始的jump game多了一個限制 問說想跳到終點的最多步數為多少
-target <= nums[j] - nums[i] <= target  s.t 0 <= i < j < n
*/ 
