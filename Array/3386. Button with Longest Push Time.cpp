/*
3386. Button with Longest Push Time
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int buttonWithLongestTime(vector<vector<int>>& events) {
        int n = events.size();
        int maxTime = events[0][1];
        int res = events[0][0];
        for(int i = 1; i < n; i++) {
            int diffTime = events[i][1] - events[i-1][1];
            if(diffTime > maxTime) {
                maxTime = diffTime;
                res = events[i][0];
            }
            else if(diffTime == maxTime) {
                res = min(res, events[i][0]);
            }
        }
        return res;
    }
};
