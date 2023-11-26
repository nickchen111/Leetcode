/*
632. Smallest Range Covering Elements from K Lists
*/

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int n = nums.size();
        vector<int> res;
        set<pair<int,int>> set;//val->哪個組的
        vector<int> pointer(n,0); //紀錄目前指到哪個數字 各個group
        for(int i =0;i<n;i++){
            set.insert({nums[i][0],i});
        }

        int range = INT_MAX;
        while(1){
            if(set.rbegin()->first - set.begin()->first < range){
                range = set.rbegin()->first - set.begin()->first;
                res = {set.begin()->first, set.rbegin()->first}; 
            }
            int i = set.begin()->second;//先記錄他是哪個小組
            pointer[i]++;
            if(pointer[i] == nums[i].size()) break;
            set.erase(set.begin());
            set.insert({nums[i][pointer[i]],i});
        }

        return res;
    }
};
