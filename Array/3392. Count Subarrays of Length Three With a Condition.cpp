/*
3392. Count Subarrays of Length Three With a Condition
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int countSubarrays(vector<int>& nums) {
        int n = nums.size();
        // 前後數字和 == 中間數字/2
        int res = 0;
        for(int i = 1; i < n-1; i++) {
            if((nums[i] % 2 == 0) && nums[i-1] + nums[i+1] == nums[i]/2) res += 1;
        }
        return res;
    }
};
