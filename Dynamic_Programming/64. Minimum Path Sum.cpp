/*
64. Minimum Path Sum
*/

//iterative TC:O(m*n) SC:O(m*n)
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(); int n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, INT_MAX));
        //base case
        dp[0][0] = grid[0][0];
        for(int i = 1; i<m; i++){
            dp[i][0] = dp[i-1][0]+grid[i][0];
        }
        for(int j = 1; j<n; j++){
            dp[0][j] = dp[0][j-1]+grid[0][j];
        }

        for(int i = 1; i <m; i++){
            for(int j =1; j<n; j++){
                dp[i][j] = min(dp[i][j], min(dp[i-1][j]+grid[i][j], dp[i][j-1]+grid[i][j]));
            }
        }

        return dp[m-1][n-1];
    }
};

//優化空間 SC:O(n)
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(); int n = grid[0].size();
        vector<int> dp(n, INT_MAX);
        //base case
        dp[0] =grid[0][0];
        for(int i = 1; i < n; i++){
            dp[i] = dp[i-1]+grid[0][i];
        }

        for(int i = 1; i <m; i++){
            for(int j =0; j<n; j++){
                dp[j] = dp[j] + grid[i][j];
                if(j-1 >= 0)
                    dp[j] = min(dp[j],dp[j-1]+grid[i][j]);
            }
        }

        return dp[n-1];
    }
};

//recursion+memo
class Solution {
    vector<vector<int>> memo;
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(); int n = grid[0].size();
        memo = vector<vector<int>>(m, vector<int>(n, -1));

        return dp(grid, m-1, n-1);
    }

    int dp(vector<vector<int>>& grid, int i, int j){
        if(i == 0 && j == 0) return grid[0][0];
        if(i < 0 || j < 0) return INT_MAX;

        if(memo[i][j] != -1) return memo[i][j];

        memo[i][j] = min(dp(grid, i-1, j), dp(grid,i, j-1))+grid[i][j];

        return memo[i][j];
    }
};

/*
最小路徑和：
感覺可以用dijkstra or floyd
dp:
dp[i][j]為起點到grid[i][j]的最短距離
*/
