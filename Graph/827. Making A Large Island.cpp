// DFS TC:O(n^2) SC:O(n^2)
class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<int> area;
        vector<int> dirs = {0, 1, 0, -1, 0};
        auto dfs = [&](auto &&dfs, int i, int j) -> int {
            grid[i][j] = area.size() + 2;
            int size = 1;
            for(int k = 1; k < dirs.size(); k++) {
                int nx = i + dirs[k-1], ny = j + dirs[k];
                if(0 <= nx && nx < n && 0 <= ny && ny < n && grid[nx][ny] == 1) size += dfs(dfs, nx,ny);
            }
            return size;
        };
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++) 
                if(grid[i][j] == 1) 
                    area.emplace_back(dfs(dfs, i, j));
        if(area.empty()) return 1;
        unordered_set<int> set;
        int ans = 0;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++) 
                if(grid[i][j] == 0) {
                    int size = 1;
                    set.clear();
                    for(int k = 1; k < dirs.size(); k++) {
                        int nx = i + dirs[k-1], ny = j + dirs[k];
                        if(0 <= nx && nx < n && 0 <= ny && ny < n && grid[nx][ny] && set.insert(grid[nx][ny]).second) {
                            size += area[grid[nx][ny] - 2];
                        } 
                    }
                    ans = max(ans, size);
                }

        return ans ? ans : n * n;
    }
};

// UF TC:O(n^2 * ⍺(n)) SC:O(n^2)
class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> pa(m*n);
        iota(pa.begin(), pa.end(), 0);
        vector<int> rank(m*n, 1);
        
        function<int(int)> find = [&](int x) -> int {
            if(x != pa[x]) {
                pa[x] = find(pa[x]);
            }
            return pa[x];
        };
        
        auto merge = [&](int x, int y) -> void {
            x = find(x), y = find(y);
            if(x != y) {
                if(rank[x] < rank[y]) {
                    pa[x] = y;
                    rank[y] += rank[x];
                }
                else {
                    pa[y] = x;
                    rank[x] += rank[y];
                }
            }
        };
        
        vector<int> dirs = {0, 1, 0, -1, 0};
        int ans = 1;
        
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j]) {
                    for(int k = 1; k < dirs.size(); k++) {
                        int nx = i + dirs[k-1], ny = j + dirs[k];
                        if(nx < 0 || ny < 0 || nx >= m || ny >= n || !grid[nx][ny]) continue;
                        merge(i*n+j, nx*n+ny);
                    }
                    ans = max(ans, rank[find(i*n+j)]);
                }
            }
        }
        unordered_set<int> parents;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 0) {
                    int size = 1;
                    parents.clear();
                    for(int k = 1; k < dirs.size(); k++) {
                        int nx = i + dirs[k-1], ny = j + dirs[k];
                        if(nx < 0 || ny < 0 || nx >= m || ny >= n || !grid[nx][ny]) continue;
                        int p = find(nx*n+ny);
                        if(parents.insert(p).second) {
                            size += rank[p];
                        }
                    }
                    ans = max(ans, size);
                }
            }
        }
        
        return ans;
    }
};
