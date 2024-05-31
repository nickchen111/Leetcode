/*
260. Single Number III
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        vector<int> res;
        int cur = 0;
        for(auto x : nums){
            cur ^= x;
        }
        int lowbit;
        for(int bit = 0; bit < 32; bit++){
            if(cur& (1 << bit)){
                lowbit = bit;
                break;
            }
        }
        int cur2 = 0;
        for(auto x : nums){
            if(x& (1 << lowbit)){
                cur2 ^= x;
            }
        }
        

        return {cur^cur2, cur2};
    }
};
