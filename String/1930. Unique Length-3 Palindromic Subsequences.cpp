/*
1930. Unique Length-3 Palindromic Subsequences
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int countPalindromicSubsequence(string s) {
        //數一個字串中長度為3的subsequence 且是回文串數量有多少
        // 區間DP?!但是回文串不能重複->hash set
        unordered_set<char> set;
        int res = 0;
        for(auto ch:s){
            set.insert(ch);
        }
        for(auto c:set){
            int start = s.find(c);
            int end = s.rfind(c);
            if(start < end){
                //判斷這段合法區間可以組成多少個長度3的回文串 需去重
                unordered_set<char> charSet;
                for(int i = start+1; i<end; i++){
                    charSet.insert(s[i]);
                }
                res+=charSet.size();
            }
        }
        return res;
    }
};
