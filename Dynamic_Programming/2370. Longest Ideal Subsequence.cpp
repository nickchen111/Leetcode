/*
2370. Longest Ideal Subsequence
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int longestIdealString(string s, int k) {
        int n = s.size();
        s = "#" + s;
        vector<int> dp(26,0);
        int res = 1;
        for(int i = 1; i <= n; i++){
            int ch = s[i]-'a';
            int cand2 = max(0, ch - k);
            int cand1 = min(25, ch + k);
            auto dp_tmp = dp;
            for(int j = cand2; j <= cand1; j++){
                dp[ch] = max(dp[ch], dp_tmp[(j+26)%26] + 1);
            }
            res = max(res, dp[ch]);
        }

        return res;
    }
};

/*
給你一個字串s與 整數 k
一個字串t要是理想的必須滿足兩個條件
1. 是s的subsequence
2. t的兩個相鄰絕對值字母差要小於等於k
問說最長的這種子串可以是多長
 24 k = 3 -> +k : 1 , -k : 21 -> 21 22 23 24 25 26 1
 21-27
 eduktdb -> edkdb k=15
 5,4,21,11,20,4,2 
*/
