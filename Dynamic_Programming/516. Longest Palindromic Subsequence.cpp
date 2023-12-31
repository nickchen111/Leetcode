/*
516. Longest Palindromic Subsequence
*/

//區間型dp TC:O(n^2) SC:O(n^2)
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n,0));
        //base case

        for(int i = 0; i < n; i++){
            dp[i][i] = 1;
        }

        for(int len = 2; len <= n; len++){
            for(int i = 0; i+len-1 < n; i++){
                int j = len+i-1;
                if(s[i] == s[j]){
                    dp[i][j] = dp[i+1][j-1]+2;
                }
                else {
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
                }
            }
        }
        

        return dp[0][n-1];
        
    }
};
/*
此題要求可以包含兩種性質 1. 回文串 2.最長子序列
有點區間回文串感覺 但是又可以跳數
1.用區間型dp
dp[i][j] 從s[i:j]最長回文子序列長度
跟一般型的dp不同 
一般可能是dp[j] si = sj的話 si之前的數可決定到sj ex dp[j] = dp[i] +1 i 是j之前的數
這題的話是要看被ij包覆住的區間 那麼dp寫法就呼之欲出了dp[i][j] = dp[i+1][j-1]+2;
如果 si != sj dp[i][j-1], dp[i+1][j]求最大 因為這兩個數ij也是有可能包覆住的形成回文串
       xxxx i xxxx j
2. brute force n! 每個點 起點到終點 都跟大家遍歷一下判斷
*/
