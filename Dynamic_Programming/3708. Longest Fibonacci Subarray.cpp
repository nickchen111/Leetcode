// TC:O(n) SC:O(1)
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int n = nums.size();
        int ans = 2;
        int prev = 2;
        for (int i = 2; i < n; i++) {
            int cur = 2;
            if (nums[i - 2] + nums[i - 1] == nums[i]) {
                cur = prev + 1;
            }
            ans = max(ans, cur);
            prev = cur;
        }
        return ans;
    }
};
