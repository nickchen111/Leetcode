// TC:O(n) SC:O(n)
class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        if(n <= k) return *max_element(nums.begin(), nums.end());
        unordered_map<int,int> map;
        unordered_map<int,int> store;
        int i = 0;
        for(int j = 0; j < n; j++) {
            map[nums[j]] += 1;
            if(j - i + 1 == k) {
                for(auto &[num, freq] : map) {
                    store[num] += 1;
                }
                map[nums[i]] -= 1;
                if(map[nums[i]] == 0) map.erase(nums[i]);
                i += 1;
            }
        }
        int ans = -1;
        for(auto &[num, freq] : store) {
            if(freq == 1) ans = max(ans, num);
        }
        return ans;
        
    }
};
