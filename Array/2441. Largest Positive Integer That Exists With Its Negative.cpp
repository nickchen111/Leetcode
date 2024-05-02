/*
2441. Largest Positive Integer That Exists With Its Negative
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int findMaxK(vector<int>& nums) {
        int n = nums.size();
        int maxVal = -1;
        unordered_map<int,int> map;
        for(int i = 0; i < n; i++){
            if(nums[i] < 0){
                if(map.find(-nums[i]) != map.end()){
                    maxVal = max(maxVal, -nums[i]);
                }
                map[nums[i]] += 1;
            }
            else {
                if(map.find(-nums[i]) != map.end()){
                    maxVal = max(maxVal, nums[i]);
                }
                map[nums[i]] += 1;
            }
        }
        
        return maxVal;
    }
};
