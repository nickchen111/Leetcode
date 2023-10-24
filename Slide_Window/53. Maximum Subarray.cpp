/*
53. Maximum Subarray
*/

//解法之一slide window:
// TC:O(n) SC:O(1)
class Solution {
    //slide window
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0];
        int left = 0; int right = 0;
        int windowSum = 0;
        int MaxSum = INT_MIN;
        while(right < n){
            //何時該擴大
            windowSum+=nums[right];
            right++;

            MaxSum = max(MaxSum, windowSum);

            while(windowSum < 0){
                windowSum -=nums[left];
                left++;
            }
        }
        return MaxSum;
    }
};
