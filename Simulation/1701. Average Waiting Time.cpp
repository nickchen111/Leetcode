/*
1701. Average Waiting Time
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    double averageWaitingTime(vector<vector<int>>& customers) {
        double res = 0;
        double count = 0;
        double curTime = 0;
        for(int i = 0; i < customers.size(); i++){
            curTime = max(curTime + customers[i][1] , (double)customers[i][0] + customers[i][1]);
            count += 1;
            res = (res + (curTime - customers[i][0]));
        }
        res /= count;

        return res;
    }
};
