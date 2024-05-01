/*
2000. Reverse Prefix of Word
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    string reversePrefix(string word, char ch) {
        int start = 0;
        int end = 0;
        int n = word.size();
        while(end < n && word[end] != ch) end++;
        if(end == n) return word;
        
        while(start < end && end  < n){
            char tmp = word[end];
            word[end] = word[start];
            word[start] = tmp;
            end--;
            start++;
        }

        return word;
    }
};
