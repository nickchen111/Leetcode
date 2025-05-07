/*
3342. Find Minimum Time to Reach Last Room II
*/

// TC:O(n*m* lg(n*m)) SC:O(n*m)
class Solution {
public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        /*
        從左上移動到右下 最少需要多少時間 Dijkstra 
        每動一次會根據上次的時間改變這次要移動的時間 1 2 1 2 交替
        那要如何設計呢?
        首先一樣會有一個array 紀錄當前走到該點的最小時間
        PQ部分會有四個變量 x, y, 這次要交替的時間，抵達該點時間
        演算法內部在跑的過程會是根據目前可走的點去動態更新最大時間 然後再後面重新跑一次
        將可以被納入的點加入PQ
        TC 會是 2mnlgmn
        */
        int m = moveTime.size(), n = moveTime[0].size();
        vector<vector<int>> minCost(m, vector<int>(n, INT_MAX/2));
        priority_queue<array<int,3>, vector<array<int,3>>, greater<>> pq;
        pq.push({0,0,0});
        vector<int> dirs = {0,1,0,-1,0};
        while(!pq.empty()) {
            auto [c, x, y] = pq.top();
            int step = (x + y) % 2 + 1;
            pq.pop();
            if (x == m - 1 && y == n - 1) return c;
            if (minCost[x][y] <= c) continue;
            minCost[x][y] = c;
            for (int k = 1; k < dirs.size(); k++) {
                int nx = x + dirs[k-1];
                int ny = y + dirs[k];
                int nxtStep = 3 - step;
                if (nx < 0 || nx >= m || ny < 0 || ny >= n || minCost[nx][ny] != INT_MAX/2) continue;
                int nc = max(c, moveTime[nx][ny])  + step;
                pq.push({nc, nx, ny});
            }
        }
        return -1;
    }
};
