/*
2684. Maximum Number of Moves in a Grid
*/

// DFS + Memo TC:O(m*n*3) SC:O(m*n)
class Solution {
    int m,n;
    vector<vector<int>> visited;
public:
    int maxMoves(vector<vector<int>>& grid) {
        m = grid.size(); 
        n = grid[0].size();
        visited = vector<vector<int>>(m, vector<int>(n, -1));
        int res = 0;
        for(int i = 0; i < m; i++){
            res = max(res, DFS(grid, i, 0, 0));
        }

        return res;
    }

    int DFS(vector<vector<int>>& grid, int x, int y, int step){

        if(visited[x][y] != -1) return visited[x][y];

        int maxStep = step;
        for(int i = 0; i < 3; i++){
            if(i == 0){
                int nx = x - 1; 
                int ny = y + 1;
                if(nx < 0 || ny >= n || ny < 0 || nx >= m) continue;
                if(grid[x][y] >= grid[nx][ny]) continue;
                maxStep = max(maxStep, DFS(grid, nx, ny, step + 1));
            }

            if(i == 1){
                int nx = x; 
                int ny = y + 1;
                if(nx < 0 || ny >= n || ny < 0 || nx >= m) continue;
                if(grid[x][y] >= grid[nx][ny]) continue;
                maxStep = max(maxStep, DFS(grid, nx, ny, step + 1));
            }
            if(i == 2){
                int nx = x + 1; 
                int ny = y + 1;
                if(nx < 0 || ny >= n || ny < 0 || nx >= m) continue;
                if(grid[x][y] >= grid[nx][ny]) continue;
                maxStep = max(maxStep, DFS(grid, nx, ny, step + 1));
            }
        }
        visited[x][y] = maxStep;

        return maxStep;
    }
};

// DP TC:O(m*n*3) SC:O(m*n)
class Solution {
public:
    int maxMoves(vector<vector<int>>& grid) {
        // DP
        int m = grid.size(); int n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n));

        int res = 0;
        for(int j = n-2; j >= 0; j--){
            for(int i = 0; i < m; i++){
                if(i - 1 >= 0 && grid[i][j] < grid[i-1][j+1]) dp[i][j] = max(dp[i][j], dp[i-1][j+1] + 1);
                if(i + 1 < m && grid[i][j] < grid[i+1][j+1]) dp[i][j] = max(dp[i][j], dp[i+1][j+1] + 1);
                if(grid[i][j] < grid[i][j+1]) dp[i][j] = max(dp[i][j], dp[i][j+1] + 1);
            }
        }

        for(int i = 0; i < m; i++){
            res = max(res, dp[i][0]);
        }

        return res;
        
    }
};
