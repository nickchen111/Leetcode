/*
3375. Minimum Operations to Make Array Values Equal to K
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        // sort(nums.rbegin(), nums.rend());
        // if(nums.back() < k) return -1;
        int n = nums.size();
        int res = 0;
        int minVal = INT_MAX;
        unordered_set<int> set;
        for(int i = 0; i < n; i++) {
            set.insert(nums[i]);
            minVal = min(minVal, nums[i]);
        }
        if(minVal < k) return -1;
        res += (int)set.size() - (minVal == k ? 1 : 0);
        
        return res;
    }
};
