/*
3286. Find a Safe Walk Through a Grid
*/

// BFS + Deque: TC:O(m*n*helalth) SC:O(m*n)
class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size();
        int n = grid[0].size();

        deque<array<int,3>> dq;
        vector<int> maxVal(m*n+1);
        dq.push_front({health + (grid[0][0] == 1 ? -1 : 0), 0, 0});
        vector<int> dirs = {0,1,0,-1,0};
        while(!dq.empty()){
            int curHealth = dq.front()[0];
            int x = dq.front()[1];
            int y = dq.front()[2];
            dq.pop_front();
            if(x == m-1 && y == n-1 && curHealth > 0) return true;
            if(maxVal[x*n+y] >= curHealth) continue;
            maxVal[x*n+y] = curHealth;
            for(int i = 1; i < dirs.size(); i++){
                int nx = x + dirs[i-1];
                int ny = y + dirs[i];
                if(nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
                if(grid[nx][ny] == 1){
                    if(maxVal[nx*n+ny] >= curHealth - 1) continue;
                    if(curHealth - 1 > 0) dq.push_back({curHealth - 1, nx, ny}); 
                }
                else {
                    if(maxVal[nx*n+ny] >= curHealth) continue;
                    dq.push_front({curHealth, nx, ny});
                }
            }
        }

        return false;
    }
};
// BFS + Dijkstra: TC:O(m * n * H * log(m*n)) SC:O(m*n)
class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> minCost(m, vector<int>(n));

        priority_queue<array<int,3>, vector<array<int,3>>, less<>> pq;
        pq.push({health + (grid[0][0] == 1 ? -1 : 0), 0, 0});
        vector<int> dirs = {0,1,0,-1,0};
        while(!pq.empty()){
            int curHealth = pq.top()[0];
            int x = pq.top()[1];
            int y = pq.top()[2];
            pq.pop();
            if(x == m-1 && y == n-1) return true;
            if(minCost[x][y] > curHealth) continue;
            minCost[x][y] = curHealth;

            for(int i = 1; i < dirs.size(); i++){
                int nx = x + dirs[i-1];
                int ny = y + dirs[i];
                if(nx < 0 || ny < 0 || nx >= m || ny >= n || minCost[nx][ny] >= curHealth + (grid[nx][ny] == 1 ? -1 : 0) || curHealth + (grid[nx][ny] == 1 ? -1 : 0) <= 0) continue;
                int nxtHealth = curHealth + (grid[nx][ny] == 1 ? -1 : 0);
                minCost[nx][ny] = nxtHealth;
                pq.push({nxtHealth, nx, ny});
            }        
        }

        return false;

    }
};

// DFS + Memo:TC:O(m*n*healrth) SC:O(m*n)
class Solution {
    vector<vector<int>> grid;
    int m, n;
    vector<vector<int>> memo;
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        m = grid.size();
        n = grid[0].size();
        this -> grid = grid;
        memo.resize(m, vector<int>(n,0));

        
        return DFS(health + (grid[0][0] == 1 ? -1 : 0), 0,0);
    }

    vector<int> dirs = {0,1,0,-1,0};
    bool DFS(int curhealth, int x, int y){
        if(x == m-1 && y == n-1) return true;
        if(memo[x][y] >= curhealth) return false;
        memo[x][y] = curhealth;

        for(int i = 1; i < dirs.size(); i++){
            int nx = x + dirs[i-1];
            int ny = y + dirs[i];
            if(nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
            int nxthealth = curhealth + (grid[nx][ny] == 1 ? -1 : 0);
            if(nxthealth <= 0 || memo[nx][ny] >= nxthealth) continue;
            if(DFS(nxthealth, nx,ny)) return true;
        }

        return false;
    }
};
