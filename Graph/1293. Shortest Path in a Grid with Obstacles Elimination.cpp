/*
1293. Shortest Path in a Grid with Obstacles Elimination
*/


// TC:O(m*n*k) SC:O(m*n*k)
class Solution {
    bool visited[41][41][1601];
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int m = grid.size(); int n = grid[0].size();
        
        if(m == 1 && n == 1) return 0;
        
        queue<vector<int>> q; // x y chance;
        q.push({0,0,0});
        
        int step = -1;
        vector<int> dirs = {0,1,0,-1,0};
        unordered_set<int> set;
        while(!q.empty()){
            int len = q.size();
            step++;
            while(len--){
                int x = q.front()[0];
                int y = q.front()[1];
                int chance = q.front()[2];
                q.pop();

                for(int t = 1; t<dirs.size(); t++){
                    int nx = x + dirs[t-1];
                    int ny = y + dirs[t];
                    
                    if(nx < 0 || ny < 0 || nx >= m || ny >=n) continue;
                    if(nx == m-1 && ny == n-1) return step+1;

                    if(grid[nx][ny] == 1){
                        if(chance == k) continue;
                        if(visited[nx][ny][chance+1] == 1) continue;
                        visited[nx][ny][chance+1] = 1;
                        q.push({nx, ny, chance+1});
                    }
                    else if(grid[nx][ny] == 0){
                        if(visited[nx][ny][chance] == 1) continue;
                        visited[nx][ny][chance] = 1;
                        q.push({nx, ny, chance});
                    }

                   
                }
            }
        }

        return -1;
    }
};
