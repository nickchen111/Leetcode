/*
334. Increasing Triplet Subsequence
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int n = nums.size();
        if(n < 3) return false;
        // 3個一組 -> 隨便選一個中間數 判斷當之前是否有數字比他小 之後是否有數字比他大
        int num1 = INT_MAX, num2 = INT_MAX;
        for(int i = 0; i < n; i++){
            if(nums[i] <= num1){
                num1 = nums[i];
            } else if(nums[i] <= num2){
                num2 = nums[i];
            }
            else return true;
        }

        return false;
    }
};
