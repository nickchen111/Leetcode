/*
624. Maximum Distance in Arrays
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays) {
        int minVal = INT_MAX;
        int maxVal = INT_MIN;
        bool flag = 0;
        int res = 0;
        for(int i = 0; i < arrays.size(); i++){
            if(minVal == INT_MAX && maxVal == INT_MIN){
                minVal = arrays[i][0];
                maxVal = arrays[i].back();
                flag = 1;
            }
            else {
                if(minVal > arrays[i][0] && maxVal < arrays[i].back()){
                    flag = 1;
                    res = max(maxVal - arrays[i][0], arrays[i].back() - minVal);
                    minVal = arrays[i][0];
                    maxVal = arrays[i].back();
                }
                else {
                    if(flag == 1 && maxVal > arrays[i].back() && minVal < arrays[i][0]){
                        res = max(maxVal - arrays[i][0], arrays[i].back() - minVal);
                    }
                    else {
                        minVal = min(minVal, arrays[i][0]);
                        maxVal = max(maxVal, arrays[i].back());
                        flag = 0;
                    }
                }
            }
        }

        if(flag) return res;
        else return maxVal - minVal;

    }
};
