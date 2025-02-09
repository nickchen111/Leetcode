// 週賽436場第一題 3446
class Solution {
public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        // 第一排在右上，最後一排在左下
        // 每排從左上到右下
        // 令 k=i-j+n，那麽右上角 k=1，左下角 k=m+n-1
        for (int k = 1; k < m + n; k++) {
            // 核心：計算 j 的最小值和最大值
            int min_j = max(n - k, 0); // i=0 的時候，j=n-k，但不能是負數
            int max_j = min(m + n - 1 - k, n - 1); // i=m-1 的時候，j=m+n-1-k，但不能超过 n-1
            vector<int> a;
            for (int j = min_j; j <= max_j; j++) {
                a.push_back(grid[k + j - n][j]); // 根據 k 的定義得 i=k+j-n
            }
            if (min_j > 0) { // 右上角三角形
                ranges::sort(a);
            } else { // 左下角三角形（包括中間對角線）
                ranges::sort(a, greater<int>());
            }
            for (int j = min_j; j <= max_j; j++) {
                grid[k + j - n][j] = a[j - min_j];
            }
        }
        return grid;
    }
};
