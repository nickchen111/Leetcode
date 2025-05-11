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

// Presum
class Solution {
    using ll = long long;
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        // 二维前缀和
        vector<vector<ll>> presum(m+1, vector<ll>(n+1, 0));
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                presum[i][j] = presum[i-1][j] + presum[i][j-1] - presum[i-1][j-1] + (ll) grid[i-1][j-1];
            }
        }
        auto sumRegion = [&](int row1, int col1, int row2, int col2) -> int {
            return presum[row2+1][col2+1] - presum[row1][col2+1] - presum[row2+1][col1] + presum[row1][col1];
        };
        for (int i = 0; i < m - 1; i++) {
            int upperSum = sumRegion(0, 0, i, n - 1);
            int lowerSum = sumRegion(i + 1, 0, m - 1, n - 1);
            if (upperSum == lowerSum) {
                return true;
            }
        }
        for (int j = 0; j < n - 1; j++) {
            int leftSum = sumRegion(0, 0, m - 1, j);
            int rightSum = sumRegion(0, j + 1, m - 1, n - 1);
            if (leftSum == rightSum) {
                return true;
            }
        }
        
        return false;
    }
};
