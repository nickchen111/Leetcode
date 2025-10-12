class Solution {
public:
    int sumDivisibleByK(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> mp;
        for (auto &num : nums) mp[num] += 1;
        int ans = 0;
        for (auto &[key, v] : mp) {
            if ((v % k) == 0) ans += key * v;
        }
        return ans;
    }
};