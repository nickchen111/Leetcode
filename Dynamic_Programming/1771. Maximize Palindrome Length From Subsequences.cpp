/*
1771. Maximize Palindrome Length From Subsequences
*/


// TC:O(n^2) SC:O(n^2)
class Solution {
public:
    int longestPalindrome(string word1, string word2) {
      
        string s = word1 + word2;
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n));
        int res = 0;
        for(int i = n-1; i >= 0; i--) {
            dp[i][i] = 1;
            for(int j = i+1; j < n; j++) {
                if(s[i] == s[j]) {
                    dp[i][j] = dp[i+1][j-1] + 2;
                    if(i < word1.size() && j >= word1.size()) {
                        res = max(res, dp[i][j]);
                    }
                }
                else dp[i][j] = max(dp[i+1][j], dp[i][j-1]); 
            }
        }

        
        return res;
    }
};

/*
afaaadacb
ac
*/
