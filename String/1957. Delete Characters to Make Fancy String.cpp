/*
1957. Delete Characters to Make Fancy String
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    string makeFancyString(string s) {
        int n = s.size();
        string res;
        for(int i = 0; i < n; i++) {
            int j = i + 1;
            while(j < n && s[i] == s[j]) j++;
            if (j - i >= 2) {
                res += s[i];
                res += s[i];
            } else {
                res += s[i];
            }

            i = j-1;
        }

        return res;
    }
};
