/*
583. Delete Operation for Two Strings
*/

//自底向上 iterative
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(); int n = word2.size();

        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        //base case
        for(int i = 1; i <= m; i++){
            dp[i][0] = i;
        }
        for(int j = 1; j<=n; j++){
            dp[0][j] = j;
        }

        //狀態轉移
        for(int i = 1; i<=m; i++){
            for(int j = 1; j<=n; j++){
                if(word1[i-1] == word2[j-1]){
                    dp[i][j] = dp[i-1][j-1];
                }
                else{
                    dp[i][j] = min(
                        dp[i-1][j]+1,
                        dp[i][j-1]+1
                    );
                }
            }
        }
        return dp[m][n];
    }
};

//recursion
class Solution {
//自頂向下
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(); int n = word2.size();

        vector<vector<int>> memo(m+1, vector<int>(n+1, -1));//紀錄需要幾次delete
        
        return backtrack(word1, word2, m, n, memo);
    }
    int backtrack(string& word1, string& word2, int m, int n, vector<vector<int>>& memo){
        if(m == 0) return memo[0][n] = n;
        if(n == 0) return memo[m][0] = m;
        
        if(memo[m][n] != -1) return memo[m][n];

        if(word1[m-1] == word2[n-1]){
            return memo[m][n] = backtrack(word1, word2, m-1, n-1, memo);
        }
        else{
            int deleteM = backtrack(word1, word2, m-1, n, memo)+1;
            int deleteN = backtrack(word1, word2, m, n-1, memo)+1;
            return memo[m][n] = min(deleteM, deleteN);
        }

    }
};

/*
解題思維：
給你兩個字串 要你怎樣怎樣 結果會怎樣怎樣 two string converging
dp[i][j] 要你在string 1指向i 根string 2 指向 j時 判斷需要幾步才能讓他們一樣

選擇是刪除
dp[i-1][j]
dp[i][j-1]
通常這類型題目就是 
dp[i-1][j]
dp[i][j-1]
dp[i-1][j-1] 三種在挑
tc: o(m*n) sc:o(m*n)
*/
