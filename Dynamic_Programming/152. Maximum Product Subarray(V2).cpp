/*
152. Maximum Product Subarray
*/


//優化 TC:O(n) SC:O(1)
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        //兩個數組 一個紀錄最小值 一個紀錄最大值
        int n = nums.size();

        int minVal = nums[0];
        int maxVal = nums[0];

        int res = nums[0];
        for(int i = 1; i<nums.size(); i++){
            int minVal_tmp = minVal;
            int maxVal_tmp = maxVal;
            minVal = min(minVal_tmp*nums[i],min(nums[i],maxVal_tmp*nums[i]));
            maxVal = max(maxVal_tmp*nums[i],max(nums[i],minVal_tmp*nums[i]));
            res = max(res, maxVal);
        }

        return res;
    }
};
