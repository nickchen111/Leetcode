/*
992. Subarrays with K Different Integers
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return atMostK(nums, k) - atMostK(nums, k-1);
    }
    int atMostK(vector<int>& nums, int k){
        unordered_map<int,int> map;
        int count = 0;
        int j = 0;
        for(int i = 0; i<nums.size(); i++){
            while(j <= nums.size() && map.size() <=k){
                if(j < nums.size()) map[nums[j]]+=1;
                count+=(j-i);
                j++;
            }
            
            map[nums[i]]-=1;
            if(map[nums[i]] == 0) map.erase(nums[i]);
        }

        return count;
    }
};
