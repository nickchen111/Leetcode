class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> mp;
        int i = 0;
        int ans = 0;
        for (int j = 0; j < n; j++) {
            mp[nums[j]] += 1;
            while (mp[nums[j]] > k) {
                mp[nums[i]] -= 1;
                i += 1;
            }
            ans = max(ans, j - i + 1);
        }
        return ans;
    }
};