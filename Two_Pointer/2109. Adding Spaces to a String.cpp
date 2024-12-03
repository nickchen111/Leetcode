/*
2109. Adding Spaces to a String
*/

// TC:O(m+n) SC:O(1) 
class Solution {
public:
    string addSpaces(string s, vector<int>& spaces) {
        int m = s.size();
        int n = spaces.size();
        string res = "";
        int idx = 0;
        for(int i = 0; i < m; i++) {
            if(idx < n && i == spaces[idx]) {
                res += " ";
                idx ++;
            }
            res += s[i];
        }

        return res;
    }
};
