// TC:O(n) SC:O(1)
class Solution {
public:
    int alternatingSubarray(vector<int>& nums) {
        int n = nums.size(), i = 0, ans = -1;
        while(i < n) {
            int start = i;
            while(i + 1 < n && ((((i - start) % 2) == 0 && nums[i] + 1 == nums[i+1]) || (((i - start) % 2) && nums[i] == nums[i+1] + 1))) i += 1;
            if(i - start + 1 >= 2) {
                ans = max(ans, i - start + 1);
                continue;
            }
            i += 1;
        }
        return ans;
    }
};
