/*
64. Minimum Path Sum
*/

// 遞歸 TC:O(m*n) SC:O(m*n)
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> memo(m, vector<int>(n, -1));
        function<int(int,int)> dfs = [&](int x, int y) -> int {
            if(x >= m || y >= n) return INT_MAX/2;
            if(x == m-1 && y == n -1) return grid[x][y];
            if(memo[x][y] != -1) return memo[x][y];
            int res = INT_MAX/2;
            res = min(dfs(x+1,y), dfs(x,y+1)) + grid[x][y];

            return memo[x][y] = res;
        };

        return dfs(0,0);
    }
};

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
        int m = grid.size(); 
        int n = grid[0].size();
        vector<int> dp(n, INT_MAX/2);
        // base case
        dp[0] = grid[0][0];
        for(int j = 1; j < n; j++) dp[j] = dp[j-1] + grid[0][j];

        for(int i = 1; i < m; i++) {
            dp[0] = dp[0] + grid[i][0];
            for(int j = 1; j < n; j++) {
                dp[j] = min(dp[j], dp[j-1]) + grid[i][j];
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

// dijkstra TC:O(m*n*lgmn) SC:O(m*n)
class Solution {
public:
    struct state{
        int x;
        int y;
        int dist;
        state(int x, int y, int dist){
            this->dist = dist;
            this->y = y;
            this->x = x;
        }

        bool operator>(const state& other) const{
            return dist > other.dist;
        }
    };
    int minPathSum(vector<vector<int>>& grid) {
        //grid 算是他們的加權
        int m = grid.size(); int n = grid[0].size();

        //計算出每個點到起點的最短距離
        vector<vector<int>> mindist(m, vector<int>(n, INT_MAX));
        mindist[0][0] = grid[0][0];
        priority_queue<state, vector<state>, greater<state>> pq;
        pq.push(state(0,0,grid[0][0]));

        //bfs
        while(!pq.empty()){
            state cur = pq.top(); pq.pop();
            int curx = cur.x;
            int cury = cur.y;
            int curDist = cur.dist;

            if(curDist > mindist[curx][cury]) continue;
            if(cur.x == m-1 && cur.y == n-1) return curDist;

            for(auto adj: neighbor(grid, curx, cury)){
                int Nextx = adj[0];
                int Nexty = adj[1];
                int NextDist = mindist[curx][cury] + grid[Nextx][Nexty];
                if(NextDist <  mindist[Nextx][Nexty]){
                    mindist[Nextx][Nexty] = NextDist;
                    pq.push(state(Nextx,Nexty,NextDist));
                }
            }
        }
        return mindist[m-1][n-1];//到不了！？
    }

    vector<vector<int>> dirs = {{1,0},{0,1}};//不是往下就是往右
    vector<vector<int>> neighbor(vector<vector<int>>& grid, int x, int y){
        int m = grid.size(); int n = grid[0].size();
        vector<vector<int>> res;
        for(auto dir:dirs){
            int nx = x+dir[0];
            int ny = y+dir[1];
            if(nx >=m || ny >=n) continue;
            res.push_back({nx,ny});
        }

        return res;
    }



};

/*
最小路徑和：
感覺可以用dijkstra or floyd
*/

/*
最小路徑和：
感覺可以用dijkstra or floyd
dp:
dp[i][j]為起點到grid[i][j]的最短距離
*/
