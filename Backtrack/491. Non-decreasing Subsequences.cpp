/*
491. Non-decreasing Subsequences
*/

// TC:O(2^n) SC:O(2^n) 
class Solution {
    vector<vector<int>> res;
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        
        vector<int> track;
        backtrack(nums,track,0);
        return res;
    }
    void backtrack(vector<int>& nums, vector<int>& track, int cur){

        if(track.size() > 1){
            res.push_back(track); 
        }

        unordered_set<int> set;
        for(int i = cur; i<nums.size(); i++){
            if(!track.empty() && track.back() > nums[i]) continue;
            if(!set.empty() && set.find(nums[i]) != set.end()) continue;
            set.insert(nums[i]);
            track.push_back(nums[i]);
            backtrack(nums,track,i+1);
            track.pop_back();
        }
    }
};
