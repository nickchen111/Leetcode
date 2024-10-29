/*
2684. Maximum Number of Moves in a Grid
*/

// 遞推 TC:O(m*n + m) SC:O(max(m,n))
class Solution {
public:
    int maxMoves(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> memo(m, vector<int>(n,-1));
        function<int(int x, int y, int prev)> dfs = [&](int x, int y, int prev) -> int {
            if(x >= m || y >= n || x < 0 || y < 0 || grid[x][y] <= prev) return 0;
            if(memo[x][y] != -1) return memo[x][y];
            int res = 1;
            res = res + max({dfs(x+1, y+1, grid[x][y]), dfs(x,y+1, grid[x][y]), dfs(x-1,y+1, grid[x][y])});

            return memo[x][y] = res;
        };

        int ret = 0;
        for(int i = 0; i < m; i++) {
            if(i+1 < m && memo[i+1][1] != -1) {
                ret = max(ret, memo[i+1][1]);
            }

            else if(i+1 < m) ret = max(ret, dfs(i+1, 1, grid[i][0]));

            if(memo[i][1] != -1) ret = max(ret, memo[i][1]);
            else ret = max(ret, dfs(i, 1, grid[i][0]));

            if(i-1 >= 0 && memo[i-1][1] != -1) ret = max(ret, memo[i-1][1]);
            else if(i-1 >= 0) ret = max(ret, dfs(i-1, 1, grid[i][0]));
        }

        return ret;
    }
};


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
