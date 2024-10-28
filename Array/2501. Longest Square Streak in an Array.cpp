/*
2501. Longest Square Streak in an Array
*/

// TC:O(nlgn) SC:O(n)

class Solution {
public:
    int longestSquareStreak(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int n = nums.size();
        unordered_map<int,int> map;
        map[nums[0]] = 1;
        int res = -1;
        for(int i = 1; i < n; i++) {
            int cur = sqrt(nums[i]);
            if(cur * cur == nums[i]) {
                if(map.find(cur) != map.end()) {
                    map[nums[i]] = map[cur] + 1;
                    if(map[nums[i]] >= 2) res = max(res, map[nums[i]]);
                }
                else map[nums[i]] = 1;
            }
            else map[nums[i]] = 1;
        }

        return res;
    }
};
