/*
198. House Robber
*/

//iterative TC:O(n) SC:O(1)
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size() == 0) return 0;

        int rob = nums[0], no_rob = 0;

        for(int i = 1; i<nums.size(); i++){
            int rob_temp = rob; int norob_temp = no_rob;//紀錄上一輪的狀態
            rob = norob_temp + nums[i];
            no_rob = max(rob_temp, norob_temp);
        }
        
        return max(rob, no_rob);;
    }
};

/*
雙狀態問題 
每輪的狀態只會是偷or不偷
dp[no rob 3] = dp[rob 2] or dp[no rob 2]看哪個大
dp[rob 3] = dp[no rob 2] + rob3財產 
*/
