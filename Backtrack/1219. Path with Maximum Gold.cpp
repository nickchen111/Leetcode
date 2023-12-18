/*
1219. Path with Maximum Gold
*/


// TC:O(m*n*m*n) SC:O(m*n)
class Solution {
    vector<bool> visited;
    int m,n;
public:
    int getMaximumGold(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        visited.resize(m*n);
        int res = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] != 0){
                    visited[i*n+j] = 1;
                    res = max(res, DFS(grid,i,j,grid[i][j]));
                    visited[i*n+j] = 0;
                }
            }
        }

        return res;
    }
    vector<int> dirs = {0,1,0,-1,0};
    int DFS(vector<vector<int>>& grid, int x, int y, int score){
        if(grid[x][y] == 0)  return 0;

        int res = score;
        for(int i = 1; i < dirs.size(); i++){
            int nx = x + dirs[i-1];
            int ny = y + dirs[i];
            if(nx < 0 || ny < 0 || nx >= m || ny >= n)  continue;
            if(visited[nx*n+ny]) continue;
            visited[nx*n+ny] = 1;
            res = max(res, DFS(grid,nx,ny, score + grid[nx][ny]));
            visited[nx*n+ny] = 0;
        }

        return res;
    }
};

/*
可以從任意點出發要收集最多黃金 限制為
1. 0 empty pos cannot traverse
2. can go down up left right
3. cannot visit same position
*/
