/*
2812. Find the Safest Path in a Grid
*/

// TC:O(m*n*lg2n) SC:O(m*n)
class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        if(grid[0][0] == 1) return 0;
        
        queue<pair<int,int>> q;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == 1) q.push({i,j});
            }
        }
        vector<int> dirs = {0,1,0,-1,0};
        int left = 0;
        int right = m+n;
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                int x = q.front().first;
                int y = q.front().second;
                q.pop();

                for(int i = 1; i < dirs.size(); i++){
                    int nx = x + dirs[i-1];
                    int ny = y + dirs[i];
                    if(nx < 0 || ny < 0 || nx >= m || ny >= n || grid[nx][ny] != 0) continue;
                    grid[nx][ny] = grid[x][y] + 1;
                    q.push({nx,ny});
                }
            }
        }
        
        while(left < right){
            int mid = left + (right - left+1)/2;
            
            if(check(mid, grid, 0, 0)){
                left = mid;
            }
            else right = mid - 1;
        }

        return left;
    }
    bool check(int mid, vector<vector<int>>& grid, int x, int y){
        int m = grid.size();
        int n = grid[0].size();
        if(grid[0][0] <= mid) return false;
        vector<bool> visited(m*n+1);
        visited[0] = 1;
        queue<pair<int,int>> q;
        q.push({0,0});
        
        vector<int> dirs = {0,1,0,-1,0};
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                int x = q.front().first;
                int y = q.front().second;
                q.pop();
                if(x == m-1 && y == n-1) return true;
                 for(int i = 1; i < dirs.size(); i++){
                    int nx = x + dirs[i-1];
                    int ny = y + dirs[i];
                    if(nx < 0 || ny < 0 || nx >= m || ny >= n || grid[nx][ny] <= mid || visited[nx*n+ny]) continue;
                    visited[nx*n+ny] = 1;
                    q.push({nx,ny});
                }
            }
        }
       

        return false;
        
    }
};

/*
從左上走到右下所有的路徑的點中 取距離thief最小的距離 但是要maximize他
先以有盜賊的格子為起點 一層一層定義周圍的安全格子的最小距離

*/
