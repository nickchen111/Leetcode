/*
2577. Minimum Time to Visit a Cell In a Grid
*/

// TC:O((m*n)*lg(m*n)) SC:O(m*n)
class Solution {
    struct State {
        int x, y, cnt;
        State(int x, int y, int cnt): x(x), y(y), cnt(cnt) {}
    };
public:
    int minimumTime(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        if(m > 1 && n > 1 && grid[1][0] > 1 && grid[0][1] > 1) return -1;  // 無法移動的情況

        auto cmp = [](const State& a, const State& b) {
            return a.cnt > b.cnt;
        };

        priority_queue<State, vector<State>, decltype(cmp)> pq(cmp);
        vector<vector<int>> minDist(m, vector<int>(n, INT_MAX));
        pq.push(State(0, 0, 0));
        vector<int> dirs = {0, 1, 0, -1, 0};

        while (!pq.empty()) {
            auto [x, y, cnt] = pq.top();
            pq.pop();

            if (x == m - 1 && y == n - 1) return cnt;
            if (minDist[x][y] <= cnt) continue;
            minDist[x][y] = cnt;

            for (int i = 1; i < dirs.size(); i++) {
                int nx = x + dirs[i - 1];
                int ny = y + dirs[i];
                if (nx < 0 || ny < 0 || nx >= m || ny >= n) continue;

                int nxtCnt = cnt + 1;
                if (grid[nx][ny] > nxtCnt) {
                    nxtCnt = grid[nx][ny] + ((grid[nx][ny] - nxtCnt) % 2);
                }
                if (minDist[nx][ny] > nxtCnt) {
                    pq.push(State(nx, ny, nxtCnt));
                }
            }
        }

        return -1;
    }
};
