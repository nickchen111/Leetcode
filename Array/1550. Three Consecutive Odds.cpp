/*
1550. Three Consecutive Odds
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    bool threeConsecutiveOdds(vector<int>& arr) {
        int count = 0;
        for(auto x : arr){
            if(x % 2) {
                count ++;
                if(count == 3) return true;
            }
            else count = 0;
        }

        return false;
    }
};
