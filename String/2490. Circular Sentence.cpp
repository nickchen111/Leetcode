/*
2490. Circular Sentence
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    bool isCircularSentence(string s) {
        s = s + ' ' + s[0];
        int n = s.size();
        char ch1 = '#';
        for(int i = 0; i < n; i++) {
            int j = i;
            char ch2 = s[i];
            if(ch1 != '#' && ch1 != ch2) return false;
            while(j < n && s[j] != ' ') {
                ch1 = s[j];
                j++;
            }
            i = j;
        }

        return true;
    }
};
