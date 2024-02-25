/*
3046. Split the Array
*/

//  TC:O(n) SC:O(n)
class Solution {
public:
    bool isPossibleToSplit(vector<int>& nums) {
        unordered_map<int,int> map;
        for(auto x : nums){
            map[x] += 1;
            if(map[x] > 2) return false; 
        }
        
        return true;
    }
};
