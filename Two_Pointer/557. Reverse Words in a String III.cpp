/*
557. Reverse Words in a String III
*/


// TC:O(n^2) SC:O(1)
class Solution {
public:
    string reverseWords(string& s) {
        //想單獨分割字符串 個別做reverse
        int n = s.size();
        int left = 0; int right = 0;
        while(right < n){
            if(s[right] != ' ') right++;
            
            if(s[right] == ' ' || s[right] == '\0'){
                int right_temp = right-1;
                while(left < right_temp){
                    char cur = s[left];
                    s[left] = s[right_temp];
                    s[right_temp] = cur;
                    left++; right_temp--;
                }
                left = right+1;
                right++;
            }
        }

        return s;
    }
};
