/*
350. Intersection of Two Arrays II
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        //349的follow up 可以接受重複
        unordered_map<int,int> map;
        for(auto num:nums1){
            map[num]+=1;
        }
        vector<int> res;
        for(auto num:nums2){
            if(map[num] > 0){
                res.push_back(num);
                map[num]-=1;
            }
        }

        return res;
    }
};
