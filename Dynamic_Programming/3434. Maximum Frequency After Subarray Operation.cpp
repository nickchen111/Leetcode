// TC:O(n* U) SC:O(U) 如果寫n*3 開DP陣列不會過
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        int n = nums.size(), ans = 0;
        unordered_set<int> set(nums.begin(), nums.end());
        for(auto &target:set) {
            // vector<vector<int>> dp(n, vector<int>(3, INT_MIN)); // 0 第一區 1第二區 2第三區
            // dp[0][0] = (nums[0] == k);
            // dp[0][1] = (nums[0] == target);
            int f0 = (nums[0] == k), f1 = (nums[0] == target), f2 = INT_MIN;
            for(int i = 1; i < n; i++) {
                // dp[i][0] = dp[i-1][0] + (nums[i] == k);
                // dp[i][1] = max(dp[i-1][1], dp[i-1][0]) + (nums[i] == target);
                // dp[i][2] = max(dp[i-1][1], dp[i-1][2]) + (nums[i] == k);
                f2 = max(f1, f2) + (nums[i] == k);
                f1 = max(f1, f0) + (nums[i] == target);
                f0 += (nums[i] == k);
            }
            ans = max({ans, f0, f1, f2});
        }
        return ans;
        
    }
};
