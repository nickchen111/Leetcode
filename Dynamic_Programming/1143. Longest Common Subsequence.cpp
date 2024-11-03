/*
1143. Longest Common Subsequence
*/

// 遞歸 + 遞歸 空間優化 2024/11/03
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        if(text1.size() < text2.size()) {
            string tmp = text1;
            text1 = text2;
            text2 = tmp;
        }
        int m = text1.size();
        int n = text2.size();
        // vector<vector<int>> dp(m+1, vector<int>(n+1,0));
        vector<int> dp(n+1);
        for(int i = 1; i <= m; i++) {
            int prev = dp[0];
            for(int j = 1; j <= n; j++) {
                int tmp = dp[j];
                if(text1[i-1] == text2[j-1]) {
                    dp[j] = prev + 1;
                }
                else {
                    dp[j] = max(dp[j], dp[j-1]);
                }
                prev = tmp;
            }
        }

        return dp[n];
        // vector<vector<int>> memo(m+1, vector<int>(n+1,-1));
        // function<int(int,int)> dfs = [&](int len1, int len2) -> int {
        //     if(len1 == 0 || len2 == 0) return 0;
        //     if(memo[len1][len2] != -1) return memo[len1][len2];

        //     if(text1[len1-1] == text2[len2-1]) {
        //         return memo[len1][len2] = dfs(len1-1,len2-1) + 1;
        //     }
        //     else {
        //         return memo[len1][len2] = max(dfs(len1-1,len2), dfs(len1, len2-1));
        //     }
        // };
        // return dfs(m,n);

    }
};
// iterative
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(); int n = text2.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        

        for(int i = 1; i<=m; i++){
            for(int j =1; j<=n; j++){
                if(text1[i-1] == text2[j-1]){
                    dp[i][j] =  dp[i-1][j-1]+1;
                }
                else {
                    dp[i][j] = max(
                        dp[i][j-1],
                        dp[i-1][j]
                    );
                }
            }
        }
        return dp[m][n];
    }
};

//recursion+memo => TLE
class Solution {
    //recursion+memo
    vector<vector<int>> memo;
    int res = INT_MIN;
public:
    int longestCommonSubsequence(string text1, string text2) {
        //LCA 
        int m = text1.size();
        int n = text2.size();
        text1 = "#" + text1;
        text2 = "#" + text2;

        if(m == 0 || n == 0) return 0;
        memo = vector<vector<int>>(m+1, vector<int>(n+1, -1));
        for(int i = 0; i<= m; i++){
            memo[i][0] = 0;
        }

        for(int j = 0; j<= n; j++){
            memo[0][j] = 0;
        }
        

        return dp(text1, text2, m,n);        
    }
    //dp return 的是什麼？ 是dp i 到 t2 j的LCS
    int dp(string text1, string text2, int i, int j){
        //base case
        if(i <= 0 || j <= 0) return 0;

        if(memo[i][j] != -1) return memo[i][j];

        
        if(text1[i] == text2[j]){
            memo[i][j] = dp(text1, text2, i-1, j-1)+1;
        }
        else{
            memo[i][j] = max(dp(text1, text2, i-1,j), dp(text1, text2, i, j-1));
        }
    

        return memo[i][j];
    }
};

/*
解題思路：
求LCS的經典題型 屬於two string converging
此題是想求最長字符串的長度
dp: 選擇 狀態 base case dp數組定義
數組定義： return the length of their longest common subsequence 從t1[0....i]到t2[0....j]
選擇：目前的字符串長度那些字符
狀態：當尾巴相同or不同時
tc: o(m*n) sc:o(m*n)
*/
