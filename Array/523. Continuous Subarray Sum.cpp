/*
523. Continuous Subarray Sum
*/

// TC:O(n) SC:O(k)
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        if(n <= 1) return false;

        unordered_map<int,int> map;
        map[0] = -1;
        int sum = 0;
        for(int i = 0; i < n; i++){
            sum += nums[i];
            sum %= k;
            if(map.find(sum) != map.end()){
                if(i - map[sum] >= 2) return true;
            }
            else {
                map[sum] = i; 
            }
            
        }

        return false;
    }
};
