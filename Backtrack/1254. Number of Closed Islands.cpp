/*
1254. Number of Closed Islands
*/

 
//DFS TC:O(m*n) SC:O(m*n)
class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        //dfs
        int m = grid.size(); int n = grid[0].size();
        //把邊邊的島嶼吃掉
        for(int i = 0; i<m; i++){
            DFS(grid, i, 0);
            DFS(grid, i, n-1);
        }

        for(int j = 1; j<n; j++){
            DFS(grid, 0, j);
            DFS(grid,m-1,j);
        }


        int res = 0;
        for(int i = 1; i<m; i++){
            for(int j = 1; j<n; j++){
                if(grid[i][j] == 0){
                    res++;
                    DFS(grid, i, j);
                }
            }
        }

        return res;
    }

    void DFS(vector<vector<int>>& grid, int x, int y){
        int m = grid.size(); int n = grid[0].size();

        if(x < 0 || y < 0 || x>=m || y >=n) return;
        if(grid[x][y] == 1) return;//原本就是海水了

        grid[x][y] = 1;
        DFS(grid, x+1, y);
        DFS(grid, x, y+1);
        DFS(grid, x-1, y);
        DFS(grid, x, y-1);
    }
};


//BFS
class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        //dfs
        int m = grid.size(); int n = grid[0].size();
        //把邊邊的島嶼吃掉
        for(int i = 0; i<m; i++){
            if(grid[i][0] == 0) BFS(grid, i, 0);
            if(grid[i][n-1] == 0) BFS(grid, i, n-1);
        }

        for(int j = 1; j<n; j++){
            if(grid[0][j] == 0) BFS(grid, 0, j);
            if(grid[m-1][j] == 0) BFS(grid, m-1, j);
        }


        int res = 0;
        for(int i = 1; i<m; i++){
            for(int j = 1; j<n; j++){
                if(grid[i][j] == 0){
                    res++;
                    BFS(grid, i, j);
                }
            }
        }

        return res;
    }

    void BFS(vector<vector<int>>& grid, int x, int y){
        int m = grid.size(); int n = grid[0].size();
        queue<pair<int,int>> q;
        vector<vector<int>> dirs = {{0,1},{1,0},{-1,0},{0,-1}};
        q.push({x,y});
        while(!q.empty()){
            int x = q.front().first;
            int y = q.front().second;
            q.pop();
            grid[x][y] = 1;
            for(auto dir:dirs){
                int nx = x+dir[0];
                int ny = y+dir[1];
                if(nx < 0 || ny < 0 || nx>=m || ny >=n) continue;
                if(grid[nx][ny] == 1) continue;

                q.push({nx,ny});
            }
        }
    }
};
