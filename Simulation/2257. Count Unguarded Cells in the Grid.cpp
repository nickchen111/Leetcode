/*
2257. Count Unguarded Cells in the Grid
*/

// TC:O(m*n*max(m,n)) SC:O(m*n)
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

// Set + 二分 但很慢
class Solution {
public:
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        vector<set<int>> row_guard(m); // 每一row 在哪些col上有guard
        vector<set<int>> col_guard(n); 
        vector<set<int>> row_wall(m);
        vector<set<int>> col_wall(n);
        vector<vector<int>> matrix(m, vector<int>(n,0));
        for(int i = 0; i < guards.size(); i++) {
            matrix[guards[i][0]][guards[i][1]] = 1;
            row_guard[guards[i][0]].insert(guards[i][1]);
            col_guard[guards[i][1]].insert(guards[i][0]);
        }
        for(int i = 0; i < walls.size(); i++) {
            matrix[walls[i][0]][walls[i][1]] = 2;
            row_wall[walls[i][0]].insert(walls[i][1]);
            col_wall[walls[i][1]].insert(walls[i][0]);
        }
        int count = 0;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(matrix[i][j] == 0) {
                    bool flag = 0; // 代表有人監視 直接pass
                    auto iter1 = row_guard[i].lower_bound(j);
                    auto iter2 = row_wall[i].lower_bound(j);
                    if(iter1 != row_guard[i].begin()) {
                        iter1 = prev(iter1);
                        if(iter2 != row_wall[i].begin()) iter2 = prev(iter2);
                        else {
                            flag = 1;
                        }
                        if(*iter2 < *iter1) flag = 1;
                    }

                    if(flag) continue;
                    iter1 = row_guard[i].upper_bound(j);
                    if(iter1 != row_guard[i].end()) {
                        iter2 = row_wall[i].upper_bound(j);
                        if(iter2 == row_wall[i].end()) {
                            flag = 1;
                        }
                        else {
                            if(*iter2 > *iter1) {
                                flag = 1;
                            }
                        }
                    }
                    if(flag) continue;
                    iter1 = col_guard[j].lower_bound(i);
                    if(iter1 != col_guard[j].begin()) {
                        iter1 = prev(iter1);
                        iter2 = col_wall[j].lower_bound(i);
                        if(iter2 == col_wall[j].begin()) {
                            flag = 1;
                        }
                        else {
                            iter2 = prev(iter2);
                            if(*iter2 < *iter1) {
                                flag = 1;
                            }
                        }
                    }
                    if(flag) continue;
                    iter1 = col_guard[j].lower_bound(i);
                    if(iter1 != col_guard[j].end()) {
                        iter2 = col_wall[j].lower_bound(i);
                        if(iter2 == col_wall[j].end()) {
                            flag = 1;
                        }
                        else {
                            if(*iter2 > *iter1) {
                                flag = 1;
                            }
                        }
                    }
                    if(flag) continue;
                    count += 1;
                }
            }
        }

        return count;
    }
};
