/*
2825. Make String a Subsequence Using Cyclic Increments
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    bool canMakeSubsequence(string str1, string str2) {
        int m = str1.size();
        int n = str2.size();
        int i = 0, j = 0;
        while(i < m && j < n) {
            if(str2[j]-'a' == str1[i]-'a' || str2[j]-'a' == ((str1[i]-'a'+1)%26)) {
                j++;
            }
            i++;
        }

        return j == n;
    }
};
