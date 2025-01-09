/*
2812. Find the Safest Path in a Grid
*/

// 2025.01.09 Union Find TC:O(n*n* ⍺(n)) SC:O(n*n)
class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> matrix;
        matrix.resize(n, vector<int>(n,-1));
        vector<pair<int,int>> q;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 1) {
                    matrix[i][j] = 0;
                    q.push_back({i,j});
                }
            }
        }
        vector<int> dirs = {0,1,0,-1,0};
        vector<vector<pair<int,int>>> groups;
        groups.push_back(q);
        while(!q.empty()) {
            int sz = q.size();
            vector<pair<int,int>> tmp; 
            while(sz--) {
                auto [x, y] = q.back();
                q.pop_back();
                for(int i = 1; i < dirs.size(); i++) {
                    int nx = x + dirs[i-1];
                    int ny = y + dirs[i];
                    if(nx < 0 || ny < 0 || nx >= n || ny >= n || matrix[nx][ny] != -1) continue;
                    matrix[nx][ny] = (int)groups.size();
                    tmp.push_back({nx,ny});
                }
            }
            groups.push_back(tmp);
            q = tmp;
        }
        vector<int> pa(n*n+1);
        iota(pa.begin(), pa.end(), 0);
        auto find = [&](int x) -> int {
            int rt = x;
            while(pa[rt] != rt) rt = pa[rt];
            if(x != rt) pa[x] = rt;
            return rt;
        };
        auto union_ = [&](int x, int y) -> void {
            x = find(x), y = find(y);
            if(x < y) pa[y] = x;
            else pa[x] = y;
        }; 

        for(int i = groups.size() - 2; i > 0; i--) {
            for(int j = 0; j < groups[i].size(); j++) {
                for (int k = 1; k < dirs.size(); k++) {
                    int x = groups[i][j].first + dirs[k-1], y = groups[i][j].second + dirs[k];
                    if (0 <= x && x < n && 0 <= y && y < n && matrix[x][y] >= matrix[groups[i][j].first][groups[i][j].second])
                        pa[find(x * n + y)] = find(groups[i][j].first * n + groups[i][j].second);
                }
            }
            if(find(0) == find((n-1) * n + n - 1)) return i;
        }
        return 0;
    }
};


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
