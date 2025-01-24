// TC:O(n) SC:O(n)
class Solution {
public:
    int countCompleteSubarrays(vector<int>& nums) {
        int n = nums.size();
        unordered_set<int> set(nums.begin(), nums.end());
        int target = set.size();
        unordered_map<int,int> mp;
        int i = 0, valid = 0, ans = 0;
        for(int j = 0; j < n; j++) {
            if(mp[nums[j]] == 0) valid += 1;
            mp[nums[j]] += 1;
            while(valid == target) {
                if(mp[nums[i]] == 1) valid -= 1;
                mp[nums[i++]] -= 1;
            }
            ans += i;
        }
        return ans;
    }
};
