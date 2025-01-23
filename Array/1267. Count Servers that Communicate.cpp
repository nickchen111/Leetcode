// TC:O(n * m) SC:O(n + m)
class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), ans = 0;
        vector<int> row(n);
        vector<int> col(m);
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                row[j] += grid[i][j];
                col[i] += grid[i][j];
            }
        }
        for(int i = 0; i < m; i ++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] && (row[j] > 1 || col[i] > 1)) ans += 1;
            }
        }
        return ans;
    }
};
