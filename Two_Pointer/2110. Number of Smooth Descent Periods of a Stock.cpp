// TC:O(n) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long getDescentPeriods(vector<int>& nums) {
        int n = nums.size(), i = 0;
        LL ans = 0;
        while(i < n) {
            int start = i;
            while(i + 1 < n && nums[i+1] == nums[i] - 1) i += 1;
            ans += (LL)(i - start + 1) * (i - start + 1 + 1) / 2;
            i += 1;
        }
        return ans;
    }
};
