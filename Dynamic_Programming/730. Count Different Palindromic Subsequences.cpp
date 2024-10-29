/*
730. Count Different Palindromic Subsequences
*/

// TC:O(26*n^2) SC:O(26 + n^2)
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int countPalindromicSubsequences(string s) {
        int n = s.size();
        vector<vector<LL>> dp(n, vector<LL>(n));
        vector<int> left(26,-1);
        for(int i = n-1; i >= 0; i--) {
            left[s[i]-'a'] = i;
            vector<int> right(26,-1);
            for(int j = i; j < n; j++) {
                right[s[j]-'a'] = j;
                for(int k = 0; k < 26; k++) {
                    int l = left[k], r = right[k];
                    if(l == -1 || r == -1) continue;
                    if(l == r) {
                        dp[i][j] = (dp[i][j] + 1) % MOD;
                    }
                    else if(l+1 == r) {
                        dp[i][j] = (dp[i][j] + 2) % MOD;
                    }
                    else dp[i][j] = (dp[i][j] + dp[l+1][r-1] + 2) % MOD;
                }
            }
        }

        return dp[0][n-1];

    }
};

/*
問有多少種
cn 取2 + cn取3 + cn取4 .... 
xxx = c3取2 = 3*2/2 = 3

1000*999/2 + 1000*999*998/3 + .....
回文串 aabaa 就會是包含 aba 與 b 
abba 就只有bb 

dp[i][j] 可以知道每段的最長回文串長度 感覺不好用
dp[i][j] 此區間的回文串有多少種
會需要用英文字母的計算最左邊與最右邊的每個字母出現在哪
*/
