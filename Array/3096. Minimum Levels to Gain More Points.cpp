/*
3096. Minimum Levels to Gain More Points
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int minimumLevels(vector<int>& possible) {
        int n = possible.size();
        int sum = 0;
        for(int i = 0; i < n; i++){
            if(possible[i] == 0) sum -= 1;
            else sum += 1;
        }
        
        int count = 0;
        for(int i = 0; i < n; i++){
            if(possible[i] == 0) count -= 1;
            else count += 1;
            if(count > sum-count && i != n-1) return i+1;
        }
        
        return -1;
    }
};
