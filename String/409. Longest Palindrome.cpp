/*
409. Longest Palindrome
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> map;
        for(auto ch : s){
            map[ch] += 1;
        }
        bool flag = 0;
        int res = 0;
        for(auto [ch,freq] : map){
            if(flag == 0 && freq % 2 == 1){
                flag = 1;
            }
            if(freq % 2 == 0){
                res += freq;
            }
            else if(freq > 2){
                res += freq-1;
            }
        }

        return res + flag;
    }
};
