/*
2678. Number of Senior Citizens
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int countSeniors(vector<string>& details) {
        int res = 0;
        for(int i = 0; i < details.size(); i++){
            int cur = stoi(details[i].substr(11,2));
            if(cur > 60) res += 1;
        }

        return res;
    }
};
