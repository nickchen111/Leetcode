// TC:O(n) SC:O(1)
class Solution {
public:
    int maxAdjacentDistance(vector<int>& nums) {
        nums.push_back(nums[0]);
        int n = nums.size();
        int res = 0;
        for(int i = 1; i < n; i++) {
            res = max(res, abs(nums[i] - nums[i-1]));
        }
        return res;
    }
};
