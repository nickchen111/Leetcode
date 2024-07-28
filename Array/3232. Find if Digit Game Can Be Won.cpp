/*
3232. Find if Digit Game Can Be Won
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    bool canAliceWin(vector<int>& nums) {
        int sum1 = 0;
        int sum2 = 0;
        for(auto x :nums){
            if(x >= 10) sum2 += x;
            else sum1 += x;
        }
        
        if(sum1 > sum2 || sum2 > sum1) return true;
        
        return false;
    }
};
