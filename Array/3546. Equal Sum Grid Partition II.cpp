// TC:O(m * n) SC:O(m * n)
class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        long long total = 0;
        int m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                total += grid[i][j];

        auto check = [&](const vector<vector<int>>& a) -> bool {
            long long s = 0;
            for (int i = 0; i < (int)a.size() - 1; i++) {
                for (int x : a[i]) s += x;
                if (s * 2 == total) return true;
            }
            return false;
        };
        if (check(grid)) return true;
        vector<vector<int>> transposed(n, vector<int>(m));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                transposed[j][i] = grid[i][j];

        return check(transposed);
    }
};
