/*
1. Two Sum
*/

//brute force TC:O(n^2) SC:O(1)
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for(int i = 0; i< nums.size(); i++){
            for(int j = i+1; j <nums.size(); j++)
            {
                int sum = nums[i]+nums[j];
                if(sum == target) return {i,j};
            }
        }
        return {};
    }
};

// hash map TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> map;
        int n = nums.size();
        for(int i = 0; i<n; i++){
            map[nums[i]] = i;
        }


        for(int i = 0; i<n; i++){
            int left = target - nums[i];
            if(map.count(left) && map[left] != i){
                return {i,map[left]};
            }
        }

        return {};
    }
};
