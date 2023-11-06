/*
58. Length of Last Word
*/

//TC:O(n) SC:O(1)
class Solution {
public:
    int lengthOfLastWord(string s) {
        int n = s.length()-1;
        int count = 0;
        while(s[n] == ' '){
            n--;
        }
        while(n >= 0 && s[n] != ' '){
            count++;
            n--;
        }
        return count;
    }
};
