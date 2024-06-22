/*
3190. Find Minimum Operations to Make All Elements Divisible by Three
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int n = nums.size();
        int res = 0;
        for(int i = 0; i < n; i++){
            int mod = (nums[i]%3);
            if(mod == 0) continue;
            else res += 1;
        }
        
        return res;
    }
};
