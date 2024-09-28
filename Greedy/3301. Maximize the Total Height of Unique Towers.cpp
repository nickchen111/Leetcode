/*
3301. Maximize the Total Height of Unique Towers
*/


// TC:O(nlgn) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long maximumTotalSum(vector<int>& maximumHeight) {
        
        sort(maximumHeight.rbegin(), maximumHeight.rend());
        LL res = maximumHeight[0];
        int n = maximumHeight.size();
        LL curMax = maximumHeight[0]-1;
        
        for(int i = 1; i < n; i++){
            if(curMax == 0) return -1;
            
            if(maximumHeight[i] <= curMax){
                res += maximumHeight[i];
                curMax = maximumHeight[i]-1;
            }
            else {
                res += curMax;
                curMax -= 1;
            }
        }
        
        return res;
    }
};
