/*
3396. Minimum Number of Operations to Make Elements in Array Distinct
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int,int> map;
        for(auto num : nums) {
            map[num] += 1;
        }
        
        int res = 0;
        for(int i = 0; i < n; i++) {
            if(map.size() == n-i) return res + ((i) % 3 == 0 ? 0 : 1);
            map[nums[i]] -= 1;
            if(map[nums[i]] == 0) map.erase(nums[i]);
            if((i+1) % 3 == 0) {
                res += 1;
            }
        }
        
        return n / 3 + (n % 3 == 0 ? 0 : 1);
    }
};
