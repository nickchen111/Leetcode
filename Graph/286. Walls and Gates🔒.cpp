/*
286. Walls and Gates🔒
此題就是要找出每個INT空房間離最近的門距離
-1 - 墙壁或障碍物。
0 - 门。
INF - Infinity是一个空房间。我们使用值 2 ^ 31 - 1 = 2147483647 来表示INF，您可以假设到门的距离小于 2147483647。
在代表每个空房间的网格中填入到距离最近门的距离。如果不可能到达门口，则应填入 INF。

ex:
输入：
[[2147483647,-1,0,2147483647],[2147483647,2147483647,2147483647,-1],[2147483647,-1,2147483647,-1],[0,-1,2147483647,2147483647]]
输出：
[[3,-1,0,1],[2,2,1,-1],[1,-1,2,-1],[0,-1,3,4]]
解释：
2D网络为：
INF  -1  0  INF
INF INF INF  -1
INF  -1 INF  -1
  0  -1 INF INF
答案为：
  3  -1   0   1
  2   2   1  -1
  1  -1   2  -1
  0  -1   3   4
*/

//BFS TC:O(m*n) SC:O(m*n)這個BFS遇到門以及-1的狀況 為錯誤的
class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        queue<pair<int, int>> q;
        vector<vector<int>> dirs{{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
      //先將每個門都加入隊列
        for (int i = 0; i < rooms.size(); ++i) {
            for (int j = 0; j < rooms[i].size(); ++j) {
                if (rooms[i][j] == 0) q.push({i, j});   
            }
        }
        while (!q.empty()) {
            int i = q.front().first, j = q.front().second; q.pop();
            for (int k = 0; k < dirs.size(); ++k) {
                int x = i + dirs[k][0], y = j + dirs[k][1];
                if (x < 0 || x >= rooms.size() || y < 0 || y >= rooms[0].size() || rooms[x][y] < rooms[i][j] + 1) continue;//後面那項也是一種防備的取道較大值的方式
                rooms[x][y] = min(roots[x][y],rooms[i][j] + 1);//去記錄與門的距離 取最小值是因為有好幾扇門都有可能會算到同一個房間距離 取最小的那個
                q.push({x, y});
            }
        }
    }
};


//BFS TC:O(m*n) SC:O(m*n) 
class Solution {
public:
    void wallsAndGates(vector<vector<int>> &rooms) {
        //將每個門都加入隊列中
        int m = rooms.size(); int n = rooms[0].size();
        queue<pair<int,int>> q;
        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                if(rooms[i][j] == 0) q.push({i,j});
            }
        }
        //每個門開始遍歷去看能否到空房間並記錄走的距離給他
        vector<int> dirs = {0,1,0,-1,0};
        int depth = 0;
        while(!q.empty()){
            int sz = q.size();
            for(int i = 0; i<sz; i++){
                int x = q.front().frist;
                int y = q.front().second;
                q.pop();
                rooms[x][y] = min(rooms[x][y],depth);
                for(int j = 1; j<dirs.size(); j++){
                    int nx = x+dirs[j-1];
                    int ny = y+dirs[j];
                    if(nx<0 || ny<0 || nx>=m || ny>=n) continue;
                    if(rooms[nx][ny] != INT_MAX) continue;
                    q.push(nx,ny);
                }
            }
            depth++;
        }
    }
};
