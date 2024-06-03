/*
2486. Append Characters to String to Make Subsequence
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int appendCharacters(string s, string t) {
        int m = s.size();
        int n = t.size();
        int i = 0, j = 0;
        while(i < m && j < n){
            if(s[i] == t[j]){
                j++;
            }
            i++;
        }
        return n-j;
    }
};
