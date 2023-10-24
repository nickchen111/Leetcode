/*
217. Contains Duplicate
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int,int> map;
        int n = nums.size();
        for(int i = 0; i<n; i++){
            if(map.count(nums[i]) > 0) return true;
            map[nums[i]]++;
        }
        return false;
    }
};

/*
此題我想到的方法有兩個
1.用hash map TC:O(n) SC:O(n)
1. 先sort 後 二分 TC:O(nlgn + lgn) SC:O(1)
*/
