// TC:O(n) SC:O(n)
class Solution {
public:
    int maxSum(vector<int>& nums) {
        int n = nums.size();
        int ans = 0, mx = -101;
        bool flag = false;
        vector<int> cnt(201);
        const int BASE = 100;
        for(int i = 0; i < n; i++) {
            if(nums[i] > 0 && cnt[nums[i] + BASE] == 0) {
                flag = true;
                ans += nums[i];
                cnt[nums[i] + BASE] ++;
            }
            mx = max(mx, nums[i]);
        }
        return flag ? ans : mx;
    }
};
