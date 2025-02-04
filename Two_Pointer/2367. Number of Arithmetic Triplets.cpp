// TC:O(n) SC:O(1) Three Pointer

 class Solution {
public:
    int arithmeticTriplets(vector<int>& nums, int diff) {
        int i = 0, j = 1, k = 2, n = nums.size(), ans = 0;
        while(k < n) {
            while(nums[j] + diff < nums[k]) {
                j += 1;
            }
            if(nums[j] + diff > nums[k]) {
                k += 1;
                continue;
            }
            while(nums[i] + 2 * diff < nums[k]) i += 1;
            if(nums[i] + 2 * diff == nums[k]) ans += 1;
            k += 1;
        }
        return ans;
    }
};
