// TC:O(m*n) SC:O(m*n)
class Solution {
public:
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> DIRS = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
        // vector memo(m, vector<vector<vector<vector<int>>>>(n, vector<vector<vector<int>>>(4, vector<vector<int>>(2, vector<int>(3,-1))))); 會TLE
        vector memo(m, vector<array<array<array<int, 3>, 2>, 4>>(n));
        auto dfs = [&](auto &&dfs, int x, int y,int k, bool can_turn, int target) -> int {
            x += DIRS[k][0], y += DIRS[k][1];
            if(x < 0 || y < 0 || x >= m || y >= n || grid[x][y] != target) return 0;
            int &res = memo[x][y][k][can_turn][target];
            if(res) return res;
            res = dfs(dfs, x, y, k, can_turn, 2 - target);
            if(can_turn) {
                res = max(res, dfs(dfs, x, y, (k+1) % 4, false, 2 - target));
            }
            return ++res;
        };
        int ans = 0;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 1) {
                    for(int k = 0; k < 4; k++)
                        ans = max(ans, 1 + dfs(dfs, i, j, k, true, 2));
                }
            }
        }
        return ans;
    }
};
