// TC:O(n) SC:O(n)
class Solution {
public:
    int countPairs(vector<int>& nums, int k) {
        /*
        之前有出現，並且index相乘要是k的倍數
        */
        int n = nums.size();
        int ans = 0;
        unordered_map<int, vector<int>> mp;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            for (auto &pos : mp[x]) {
                ans += (i * pos % k == 0 ? 1 : 0);
            }
            mp[x].emplace_back(i);
        }
        return ans;
    }
};
