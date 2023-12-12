/*
1464. Maximum Product of Two Elements in an Array
*/


// TC:O(nlgn) SC:O(1)
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        return (nums[n-1]-1)*(nums[n-2]-1);
    }
};
