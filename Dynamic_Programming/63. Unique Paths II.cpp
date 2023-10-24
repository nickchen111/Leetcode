/*
63. Unique Paths II
*/

//iterative tc: O(m*n) sc: O(m*n)
class Solution {
    //iterative
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(); int n = obstacleGrid[0].size();
        if(obstacleGrid[0][0] == 1) return 0;

        //創建dp數組 dp[m][n] 走到此有幾種方法
        vector<vector<int>> dp(m, vector<int>(n, 0));
        
        //base case  但要同時加上有障礙的情況 遇到1 dp就是0
        for(int i = 0; i < m; i++){
            if(obstacleGrid[i][0] == 1){
                dp[i][0] = 0;
                break;
            }
            else dp[i][0] = 1;
        }

        for(int j = 0; j < n; j++){
            if(obstacleGrid[0][j] == 1){
                dp[0][j] = 0;
                break;
            }
            else dp[0][j] = 1;
        }

        //狀態轉移方程
        for(int i = 1; i<m; i++){
            for(int j = 1; j<n; j++){
                if(obstacleGrid[i][j] == 1){
                    dp[i][j] = 0;
                }
                else {
                    dp[i][j] = dp[i-1][j]+dp[i][j-1];
                }
            }
        }

        return dp[m-1][n-1];
    }
};


// recursion+memo 時間複雜度挺差的 O(2*m*n) sc:O(m*n + m+n) 但相對的因為他有剪枝 空間上表現比較好
class Solution {
    //recursion + memo
    vector<vector<int>> memo;
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(); int n = obstacleGrid[0].size();
        if(obstacleGrid[0][0] == 1) return 0;

        //創建memo數組 memo[m][n] 走到此有幾種方法
        memo = vector<vector<int>>(m, vector<int>(n, 0));
        

        for(int i = 0; i < m; i++){
            if(obstacleGrid[i][0] == 1){
                memo[i][0] = 0;
                break;
            }
            else memo[i][0] = 1;
        }

        for(int j = 0; j < n; j++){
            if(obstacleGrid[0][j] == 1){
                memo[0][j] = 0;
                break;
            }
            else memo[0][j] = 1;
        }


        return backtrack(obstacleGrid, m-1, n-1);
    }

    int backtrack(vector<vector<int>>& obstacleGrid, int m, int n){
        //base case
        if(m == 0 || n==0) return memo[m][n];

        if(memo[m][n] >0) return memo[m][n];

        if(obstacleGrid[m][n] == 1) return 0;
 
        memo[m][n] = backtrack(obstacleGrid, m-1, n) + backtrack(obstacleGrid, m, n-1);
     

        return memo[m][n];
    }
};
