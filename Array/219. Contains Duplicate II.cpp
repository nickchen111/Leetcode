/*
219. Contains Duplicate II
*/

// Hash Map TC:(n) SC:O(n)
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        // Hash table 
        unordered_map<int,vector<int>> map;
        int n = nums.size();
        for(int i = 0; i<n; i++){
            map[nums[i]].push_back(i);
        }

        for(auto x:map){
            for(int i =1; i<x.second.size();i++){
                if(x.second[i] - x.second[i-1] <=k) return true;
            }
        }
        
        return false;

    }
};

//優化
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> map;
        int n = nums.size();
        for(int i = 0; i < n; i++){
            if(!map.count(nums[i])){
                map[nums[i]] = i;
            }
            else if (abs(i - map[nums[i]]) <= k){
                return true;
            }
            else map[nums[i]] = i;
        }
        return false;
    }
};

// Slide Window TC:O(n) SC:O(k)
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int,int> map;
        int n = nums.size();
        int j = 0;
        for(int i = 0; i<n; i++){
            while(j < n && j-i<=k){
                map[nums[j]]+=1;
                if(map[nums[j]] > 1) return true;
                j++;
            }
            map[nums[i]]--;
        }
        return false;
    }
};
