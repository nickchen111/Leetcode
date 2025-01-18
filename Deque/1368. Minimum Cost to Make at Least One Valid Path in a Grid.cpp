// Deque TC:O(n) SC:O(n)
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<vector<int>>> minDist(m, vector<vector<int>>(n, vector<int>(4, INT_MAX/2))); // 右左下上
        struct tuple {int c, x, y, dir;};
        // auto cmp = [](const tuple& a, const tuple& b) { return a.c > b.c; };
        // priority_queue<tuple, vector<tuple>, decltype(cmp)> pq;
        deque<tuple> dq;
        // pq.push({0,0,0, grid[0][0]-1});
        vector<pair<int,int>> dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        dq.push_back({0,0,0, grid[0][0]-1});
        while(!dq.empty()) {
            auto [c, x, y, dir] = dq.front();
            dq.pop_front();
            if(minDist[x][y][dir] <= c) continue;
            // cout << c << ' ' << x << ' ' << y << ' ' << dir << endl;
            if(x == m-1 && y == n-1) return c;
            minDist[x][y][dir] = c;
            // 嘗試轉向
            for(int i = 0; i < 4; i++) {
                if(i == dir) continue;
                if(minDist[x][y][i] > c + 1) {
                    dq.push_back({c+1, x, y, i});
                }
            }
            int nx = x + dirs[dir].first;
            int ny = y + dirs[dir].second;
            if(nx < 0 || ny < 0 || nx >= m || ny >= n || minDist[nx][ny][grid[nx][ny]-1] <= c) continue;
            dq.push_front({c,nx,ny,grid[nx][ny]-1});
        }
        return -1;
    }
};

// Dijkstra TC:O(nlgn) SC:O(n)
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<vector<int>>> minDist(m, vector<vector<int>>(n, vector<int>(4, INT_MAX/2))); // 右左下上
        struct tuple {int c, x, y, dir;};
        auto cmp = [](const tuple& a, const tuple& b) { return a.c > b.c; };
        priority_queue<tuple, vector<tuple>, decltype(cmp)> pq;
        pq.push({0,0,0, grid[0][0]-1});
        vector<pair<int,int>> dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        while(!pq.empty()) {
            auto [c, x, y, dir] = pq.top();
            pq.pop();
            if(minDist[x][y][dir] <= c) continue;
            // cout << c << ' ' << x << ' ' << y << ' ' << dir << endl;
            if(x == m-1 && y == n-1) return c;
            minDist[x][y][dir] = c;
            // 嘗試轉向
            for(int i = 0; i < 4; i++) {
                if(i == dir) continue;
                if(minDist[x][y][i] > c + 1) {
                    pq.push({c+1, x, y, i});
                }
            }
            int nx = x + dirs[dir].first;
            int ny = y + dirs[dir].second;
            if(nx < 0 || ny < 0 || nx >= m || ny >= n || minDist[nx][ny][grid[nx][ny]-1] <= c) continue;
            pq.push({c,nx,ny,grid[nx][ny]-1});
        }
        return -1;
    }
};
