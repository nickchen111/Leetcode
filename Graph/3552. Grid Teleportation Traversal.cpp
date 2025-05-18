// 0-1BFS TC:O(m * n) SC:O(m * n)
class Solution {
public:
    int minMoves(vector<string>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        if (matrix[m-1][n-1] == '#') return -1;
        vector<pair<int,int>> pos[26]{}; // vector<vector<pair<int,int>>> pos(26) 
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                char c = matrix[i][j];
                if (isupper(c)) {
                    pos[c - 'A'].emplace_back(i, j);
                }
            }
        }
        deque<pair<int,int>> dq{{0,0}};
        vector minDist(m, vector<int>(n, INT_MAX));
        minDist[0][0] = 0;
        vector<int> dirs = {0, 1, 0, -1, 0};
        while (!dq.empty()) {
            auto [x, y] = dq.front();
            dq.pop_front();
            if (x == m - 1 && y == n - 1) return minDist[x][y];
            char c = matrix[x][y];
            if (c != '.') {
                for (auto &[nx, ny] : pos[c - 'A']) {
                    if (minDist[nx][ny] > minDist[x][y]) {
                        minDist[nx][ny] = minDist[x][y];
                        dq.emplace_front(nx, ny);
                    }
                }
                pos[c - 'A'].clear();
            }

            for (int k = 1; k < dirs.size(); k ++) {
                int nx = x + dirs[k - 1], ny = y + dirs[k];
                if (0 <= nx && nx < m && 0 <= ny && ny< n && minDist[nx][ny] > minDist[x][y] + 1 && matrix[nx][ny] != '#') {
                    minDist[nx][ny] = minDist[x][y] + 1;
                    dq.emplace_back(nx,ny);
                }
            }
        }
        return -1;
    }
};

// Dijkstra TC:O(m * nlg(m * n)) SC:O(m * n)
class Solution {
public:
    struct PairHash {
        size_t operator()(const pair<int, int>& p) const {
            return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
        }
    };

    int minMoves(vector<string>& matrix) {
        /*
        規則是 遇到 # 不能走 遇到傳送門可以送到任意相同字上 但是只能傳送到還沒用到的字上 問說最少可以從左上走到右下的次數
        dijkstra!? 
        紀錄每個可以走到的字母 可以用0 - 26 然後hash set處理
        保證第一個字不是障礙物
        */
        int m = matrix.size(), n = matrix[0].size();
        vector<unordered_set<pair<int, int>, PairHash>> pos(26);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                char ch = matrix[i][j];
                if (ch != '.' && ch != '#') {
                    pos[ch - 'A'].insert({i, j});
                }
            }
        }

        vector<vector<int>> minDist(m, vector<int>(n, INT_MAX));
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
        pq.emplace(0, 0, 0);
        vector<int> dirs = {0, 1, 0, -1, 0};

        while (!pq.empty()) {
            auto [cnt, x, y] = pq.top(); pq.pop();
            if (x == m - 1 && y == n - 1) return cnt;
            if (minDist[x][y] <= cnt) continue;
            minDist[x][y] = cnt;

            char ch = matrix[x][y];
            if (ch != '.' && ch != '#') {
                for (auto &[nx, ny] : pos[ch - 'A']) {
                    if (minDist[nx][ny] > cnt) {
                        pq.emplace(cnt, nx, ny);
                    }
                }
                pos[ch - 'A'].clear(); // 傳送門用過就清掉，避免重複
            }

            for (int k = 1; k < 5; k++) {
                int nx = x + dirs[k - 1], ny = y + dirs[k];
                if (nx < 0 || ny < 0 || nx >= m || ny >= n || matrix[nx][ny] == '#') continue;
                if (minDist[nx][ny] > cnt + 1) {
                    pq.emplace(cnt + 1, nx, ny);
                }
            }
        }

        return -1;
    }
};
