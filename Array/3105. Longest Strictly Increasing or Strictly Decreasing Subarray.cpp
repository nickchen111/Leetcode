/*
3105. Longest Strictly Increasing or Strictly Decreasing Subarray
*/

//TC:O(n) SC:O(1)
class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int n = nums.size();
        int count1 = 1;
        int count2 = 1;
        int res = 1;
        for(int i = 1; i < n; i++){
            if(nums[i] > nums[i-1]){
                count1 += 1;
            }
            else count1 = 1;
            if(nums[i] < nums[i-1]){
                count2 += 1;
            }
            else count2 = 1;
            res = max(res, max(count2, count1));
        }
        
        return res;
    }
};
