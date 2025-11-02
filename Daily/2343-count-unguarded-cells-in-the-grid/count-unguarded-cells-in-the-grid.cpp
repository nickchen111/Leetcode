class Solution {
public:
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        vector<vector<int>> grid(m, vector<int>(n, 0)); // 0: unoccupied, 1: guard, 2: wall, 3: guarded
        
        // 填充守衛和牆的位置
        for (auto& g : guards) grid[g[0]][g[1]] = 1;
        for (auto& w : walls) grid[w[0]][w[1]] = 2;
        
        // 定義方向：上、下、左、右
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        // 根據守衛標記被監視的區域
        for (auto& g : guards) {
            for (auto& d : directions) {
                int x = g[0] + d.first, y = g[1] + d.second;
                while (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] != 1 && grid[x][y] != 2) {
                    grid[x][y] = 3; // 標記為被監視
                    x += d.first;
                    y += d.second;
                }
            }
        }
        
        // 計算未被監視的格子數量
        int count = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0) ++count;
            }
        }
        return count;
    }
};

/*
將所有guards先 UF起來 然後每個guards都去看他的上下左右是否有
每到一個free pot 判斷他上下左右是否有G
*/