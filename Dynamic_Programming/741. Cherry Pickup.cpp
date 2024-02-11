/*
741. Cherry Pickup
*/

// TC:O(n^3) SC:O(n^3)
class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        int dp[n+1][n+1][n+1];
        for(int i = 0; i <= n; i++){
            for(int j = 0; j <= n; j++){
                for(int x = 0; x <= n; x++){
                    dp[i][j][x] = INT_MIN;
                }
            }
        }

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                for(int x = 1; x <= n; x++){
                    int y = i+j-x;
                    if(y < 1 || y > n) continue;
                    if(grid[x-1][y-1] == -1 || grid[i-1][j-1] == -1) continue;
                    if(i==1 && j==1 && x==1){
                        dp[i][j][x] = grid[0][0];
                        continue;
                    }

                    dp[i][j][x] = max(dp[i][j][x], dp[i-1][j][x-1]);
                    dp[i][j][x] = max(dp[i][j][x], dp[i][j-1][x-1]);
                    dp[i][j][x] = max(dp[i][j][x], dp[i-1][j][x]);
                    dp[i][j][x] = max(dp[i][j][x], dp[i][j-1][x]);

                    if(i == x && j == y){
                        dp[i][j][x] += grid[i-1][j-1];
                    }
                    else dp[i][j][x] += grid[i-1][j-1] + grid[x-1][y-1];
                }
            }
        }

        return max(0, dp[n][n][n]);
    }
};

/*
只能往右邊或者下面走 有障礙物就不能走 走到右下角還要再走回去
問說過程最大收益是多少
原本想說那就做兩次迷宮型dp 每一次都收集當下最大收益 然後用一個數組去重構第一次走的路徑 好將走過的路徑設定成0
但是這樣會忽略從下往上走的相交可能性 下面的case可以收集所有1所以不能這樣做
還是只能設定成三惟dp dp[i][j][x]([y]) y可以由i+j-x得來 ij代表由上往下 xy代表由下往上走到這時各自加總的最大收益
i*n+j = 1*5 + 4 = 9
9%5 = 4 col
9/5 = 1 row
[1,1,1,1,0,0,0],
[0,0,0,1,0,0,0],
[0,0,0,1,0,0,1],
[1,0,0,1,0,0,0],
[0,0,0,1,0,0,0],
[0,0,0,1,0,0,0],
[0,0,0,1,1,1,1]]
*/
