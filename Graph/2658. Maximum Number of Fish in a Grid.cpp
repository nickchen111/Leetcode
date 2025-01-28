// TC:O(m*n * ⍺(n) * 2) SC:O(m*n)
class Solution {
public:
    int findMaxFish(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> pa(m*n+1);
        iota(pa.begin(), pa.end(), 0);
        auto find = [&](int x) -> int {
            int rt = x;
            while(rt != pa[rt]) rt = pa[rt];
            if(x != rt) pa[x] = rt;
            return rt;
        };
        auto merge = [&](int x, int y) -> void {
            x = find(x), y = find(y);
            if(x < y) pa[y] = x;
            else pa[x] = y;
        };
        vector<int> dirs = {0,1,0};
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j]) {
                    for(int k = 1; k < dirs.size(); k++) {
                        int nx = i + dirs[k-1], ny = j + dirs[k];
                        if(nx < 0 || ny < 0 || nx >= m || ny >= n || grid[nx][ny] == 0) continue;
                        merge(i*n+j, nx*n+ny);
                    }
                }
            }
        }
        int ans = 0;
        unordered_map<int,int> mp;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j]) {
                    int fa = find(i*n+j);
                    mp[fa] += grid[i][j];
                    ans = max(ans, mp[fa]);
                }
            }
        }
        return ans;
    }
};
