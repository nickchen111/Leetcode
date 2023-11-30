/*
2328. Number of Increasing Paths in a Grid
*/

// TC:O(m*n) SC:O(m*n)
class Solution {
    int m,n;
    vector<vector<int>> dp;
    using LL = long long;
    LL M = 1e9+7;
public:
    int countPaths(vector<vector<int>>& grid) {
        m = grid.size(); n = grid[0].size();

        dp = vector<vector<int>>(m, vector<int>(n,0));
        int res = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                res = (res + DFS(grid,i,j))%M;
            }
        }

        return res;
    }
    vector<int> dirs = {0,1,0,-1,0};
    int DFS(vector<vector<int>>& grid, int x, int y){
        if(dp[x][y] != 0) return dp[x][y];

        dp[x][y] = 1;
        for(int i = 1; i<dirs.size(); i++){
            int nx = x + dirs[i-1];
            int ny = y + dirs[i];
            if(nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
            if(grid[nx][ny] <= grid[x][y]) continue;
            dp[x][y] = (dp[x][y] + DFS(grid,nx,ny))%M;
        }

        return dp[x][y];
    }
};

/*
1 2 4 
2 3 2
5 1 8

記憶化每條路徑起點到某條
*/
