/*
62. Unique Paths
*/

// tc: O(n*m) sc:O(m*n)
class Solution {
    //迭代 
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));

        //base case
        for(int i = 0; i<m; i++){
            dp[i][0] = 1;
        }
        for(int j = 1; j<n; j++){
            dp[0][j] = 1;
        }


        //狀態轉移方程
        for(int i=1; i<m; i++){
            for(int j =1; j<n; j++){
                dp[i][j] = dp[i-1][j]+dp[i][j-1];
            }
        }

        return dp[m-1][n-1];
    }
};

//空間上省了不少 tc: O(n*m) sc:O(m)
class Solution {
    //迭代 優化 因為此題走的方式限制可以這樣優化
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(m);
        //等於保存了第一列的狀態 
        for(int i = 0; i<m; i++){
            dp[i] = 1;
        }
        //每次只計算一列的節果 漿結果加上他上面跟左邊不斷更新就可以了
        for(int i = 1; i<n;i++){//從列開始慢慢更新 更新到最後一列就是我要的結果
           for(int j = 1; j<m; j++){
               dp[j] = dp[j] + dp[j-1]; // j-1為上面 i為左邊
           }
        }

        return dp[m-1];
    }
};

//recursion + memo  耗費空間 沒加的話直接TLE
class Solution {
    //recursion + memo
    vector<vector<int>> memo;
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));
        memo = vector<vector<int>>(m, vector<int>(n, -1));
        return backtrack(dp, m-1, n-1);
    }

    int backtrack(vector<vector<int>>& dp, int m, int n){
        if( m == 0 || n == 0) return 1;
        if(memo[m][n] != -1) return memo[m][n];

     
        dp[m][n] = backtrack(dp, m, n-1) + backtrack(dp, m-1,n);

        memo[m][n] = dp[m][n];

        return dp[m][n]; 
    }
};
/*
解題思路：
通常遇到這種有夠多選擇的腦袋要爆開的題目 試試動態規劃
只能下or右
dp[i][j] i j這個位置取決於 dp[i-1][j] dp[i][j-1]兩條路的可能性相加 easy?
*/
