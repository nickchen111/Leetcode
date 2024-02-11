/*
1463. Cherry Pickup II
*/

// TC:O(m*n*n*3*3) SC:O(n^2)
class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(n, vector<int>(n, INT_MIN));
        dp[0][n-1] = grid[0][0] + grid[0][n-1];
        int res = dp[0][n-1];
        for(int r = 1; r < m; r++){
            auto dp_old = dp;
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    for(int a = i-1; a <= i+1; a++){
                        for(int b = j-1; b <= j+1; b++){
                            if(a < 0 || b < 0 || a >= n || b >= n) continue;
                            if(i != j){
                                dp[i][j] = max(dp[i][j], dp_old[a][b] + grid[r][i] + grid[r][j]);
                            }
                            else {
                                dp[i][j] = max(dp[i][j], dp_old[a][b] + grid[r][i]);
                            }
                        }
                    }
                    res = max(res, dp[i][j]);
                }
            }
        } 

        return res;
    }
};


/*
兩台機器人 可以往左下 下 右下走 兩台分別一開始在左上跟右上作為起點
要去收集櫻桃 當兩台robot相遇 只會收集到一次的櫻桃數量
問說最多可以收集多少櫻桃
設定一個dp[r][i][j] 機器人在某一row時 兩台分別在 i & j可以獲取的最大收益
*/
