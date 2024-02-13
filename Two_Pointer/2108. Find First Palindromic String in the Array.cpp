/*
2108. Find First Palindromic String in the Array
*/

// TC:O(m*n) SC:O(1)
class Solution {
public:
    string firstPalindrome(vector<string>& words) {
        int n = words.size();
        for(int i = 0; i < n; i++){
            if(check(words[i])) return words[i];
        }

        return "";
    }
    bool check(string& s){
        int n = s.size();
        int left = 0;
        int right = 0;
        // x x x x 
        if(n%2){
            left = n/2;
            right = n/2;
        } 
        else {
            left = n/2-1;
            right = n/2;
        }
        while(left >= 0 && right < n){
            if(s[left] == s[right]){
                left--;
                right++;
            }
            else return false;
        }

        return true;
    }
};
