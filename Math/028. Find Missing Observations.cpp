/*
2028. Find Missing Observations
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
        int m = rolls.size();
        
        int total = (m + n)*mean;
        int sum = accumulate(rolls.begin(), rolls.end(), 0);
        int diff = total - sum;
        if((diff / n) == 0 || n*6 < diff || diff < 0) return {};
        vector<int> res;

        int mod = diff % n;
        int base = diff/n;
        for(int i = 0; i < n; i++){
            if(i < mod) {
                res.push_back(base+1);
            }
            else res.push_back(base);
        }

        return res;

    }
};
