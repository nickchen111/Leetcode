// TC:O(n) SC:O(1)
class Solution {
public:
    int longestAlternatingSubarray(vector<int>& nums, int threshold) {
        int ans = 0, n = nums.size(), i = 0;
        while(i < n) {
            if(nums[i] % 2 || nums[i] > threshold) {
                i += 1;
                continue;
            }
            int start = i;
            while(i+1 < n && nums[i] % 2 != nums[i+1] % 2 && nums[i+1] <= threshold) i += 1;
            ans = max(ans, i - start + 1);
            i += 1;
        }
        return ans;
    }
};
