/*
2290. Minimum Obstacle Removal to Reach Corner
*/

// TC:O((m*n)*lg(m*n)) SC:O(m*n)
class Solution {
    struct State {
        int x, y, cnt;
        State(int x, int y, int cnt) : x(x), y(y), cnt(cnt) {}
    };
    
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        auto cmp = [](const State& a, const State& b) {
            return a.cnt > b.cnt;
        };

        priority_queue<State, vector<State>, decltype(cmp)> pq(cmp);

        vector<vector<int>> minDist(m, vector<int>(n, INT_MAX/2));
        pq.push(State(0,0,0));
        vector<int> dirs = {0,1,0,-1,0};
        while(!pq.empty()) {
            int sz = pq.size();
            while(sz--) {
                State cur = pq.top();
                pq.pop();
                if(minDist[cur.x][cur.y] <= cur.cnt) continue;
                minDist[cur.x][cur.y] = cur.cnt;
                if(cur.x == m-1 && cur.y == n-1) return cur.cnt;

                for(int i = 1; i < dirs.size(); i++) {
                    int nx = cur.x + dirs[i-1];
                    int ny = cur.y + dirs[i];
                    if(nx < 0 || ny < 0 || nx >= m || ny >= n || minDist[nx][ny] <= cur.cnt + (grid[nx][ny] == 1)) continue;
                    pq.push(State(nx, ny, (cur.cnt + (grid[nx][ny] == 1))));
                }
            }
        }

        return -1;
    }
};
