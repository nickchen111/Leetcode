/*
1208. Get Equal Substrings Within Budget
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int equalSubstring(string s, string t, int maxCost) {
        int  sum = 0;
        int j = 0;
        int n = s.size();
        int res = 0;
        for(int i = 0; i < n; i++){
            while(j < n && sum <= maxCost){
                res = max(res, j-i);
                sum += abs(s[j]-t[j]);
                j++;
            }
            if(j == n && sum <= maxCost){
                res = max(res, j-i);
            }
            sum -= abs(s[i]-t[i]);
        }

        return res;
    }
};
