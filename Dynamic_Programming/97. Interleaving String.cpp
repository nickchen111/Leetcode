/*
97. Interleaving String
*/

//iterative tc:O(m*n) sc:O(m*n)
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.size(); int n = s2.size();
        if(m+n != s3.size()) return false;
        s1 = "#" + s1;
        s2 = "#" + s2;
        s3 = "#" + s3;

        //自底向上iterative
        vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
        //s2都沒東西的情況
        dp[0][0] = 1;// 兩個都沒東西 必相等
        for(int i = 1; i<=m; i++){
            dp[i][0] = (dp[i-1][0] == true && s1[i] == s3[i]);
        }
        //s1沒東西
        for(int j = 1; j<=n; j++){
            dp[0][j] = (dp[0][j-1] == true && s2[j] == s3[j]);
        }

        for(int i = 1; i <=m; i++){
            for(int j = 1; j<=n; j++){
                if(s1[i] == s3[i+j] && dp[i-1][j] == true){
                    dp[i][j] = true;
                }
                else if(s2[j] == s3[i+j] && dp[i][j-1] == true){
                    dp[i][j] = true;
                }
            }
        }
        return dp[m][n];
    }
};

//recursion+memo
class Solution {
    vector<vector<int>> memo;
public:
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.size(); int n = s2.size();
        if(m+n != s3.size()) return false;
        memo = vector<vector<int>>(m+1, vector<int>(n+1,-1));
 
        return dp(s1, s2, s3, 0, 0);
    }
    bool dp(string& s1, string& s2, string& s3, int m, int n){
        if(m+n == s3.size()) return true;

        if(memo[m][n] != -1) return memo[m][n] == 1 ? true:false;

        bool res = false;
        //如果 可以就在多加一個試試看可不可以自底向上
        if(m < s1.size() && s1[m] == s3[m+n]){
            res = dp(s1,s2,s3,m+1,n);
        }
        if(n < s2.size() && s2[n] == s3[m+n]){
            res = res || dp(s1,s2,s3,m,n+1);
        } 

        memo[m][n] = res == true ? 1:0;
        return res;
    }
};




/*
屬於 two pointer converging
 ij
 k == s3.size() 代表成功返回true
 dp定義為 dp[i][j]  s1[0:i] s2[0: j]能否組成 s3[0:i+j]
 此題一定要全部都用到不能跳過 所以dp[i-1][j-1]就不會用到了
 只會有 dp[i-1][j] dp[i][j-1]

 xxxxx i
 yyyyyy j
 zzzzzzzzzzzz 
*/
