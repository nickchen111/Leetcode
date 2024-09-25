/*
2100. Find Good Days to Rob the Bank
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> goodDaysToRobBank(vector<int>& security, int time) {
        int n = security.size();
        vector<int> res;
        if(time == 0) {
            for(int i = 0; i < n; i++){
                res.push_back(i);
            }
            return res;
        }

        vector<int> suffix(n);
        for(int i = n-2; i >= 0; i--){
            if(security[i] <= security[i+1]){
                suffix[i] = suffix[i+1] + 1;
            }
        }

        int prefix = 0;
        
        for(int i = 1; i < n - time; i++){
            if(security[i] <= security[i-1]) {
                prefix ++;
            }
            else prefix = 0;
            
            if(i >= time){
                if(prefix >= time && suffix[i] >= time){
                    res.push_back(i);
                }
            }
        }

        return res;
    }
};
