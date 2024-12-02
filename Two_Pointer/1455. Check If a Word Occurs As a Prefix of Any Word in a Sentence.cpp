/*
1455. Check If a Word Occurs As a Prefix of Any Word in a Sentence
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int isPrefixOfWord(string sentence, string searchWord) {
        int m = sentence.size();
        int n = searchWord.size();
        int count = 1;
        for(int j = 0; j < m; j++) {
            int i = j;
            string s;
            while(j < m && sentence[j] != ' ') {
                s += sentence[j];
                j++;
            }
            if(s.size() >= n) {
                int left = 0;
                int right = 0;
                while(left < m && right < n) {
                    if(s[left] == searchWord[right]) {
                        left ++;
                        right ++;
                    }
                    else break;
                }
                if(right == n) return count;
            }
            i = j;
            count += 1;
        }
        return -1;
    }
};
