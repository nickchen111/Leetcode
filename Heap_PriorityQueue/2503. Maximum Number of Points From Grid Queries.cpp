// Heap TC:O((mnlgmn + k)+ klgk) SC:O(mn)
class Solution {
public:
    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
        /*
        首先肯定離線排序 先從較小的數值開始
        有兩個想法
        1. Dijstra 去拿數字
        2. Union Find 去把可以到達的數字串一起
        */

        int m = grid.size(), n = grid[0].size(), k = queries.size();
        vector<int> idx(k);
        iota(idx.begin(), idx.end(), 0);
        ranges::sort(idx, [&](int i, int j) { return queries[i] < queries[j]; });
        
        vector<int> ans(k);
        int cnt = 0;
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
        pq.emplace(grid[0][0], 0, 0);
        grid[0][0] = 0; // 充當visited數組
        vector<int> dirs = {0, 1, 0, -1, 0};
        for (int i = 0; i < k; i++) {
            int curQuery = queries[idx[i]];
            while (!pq.empty() && get<0>(pq.top()) < curQuery) {
                auto [cellVal, x, y] = pq.top();
                cnt += 1;
                pq.pop();
                for (int t = 1; t < dirs.size(); t++) {
                    int nx = x + dirs[t-1];
                    int ny = y + dirs[t];
                    if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny]) {
                        pq.emplace(grid[nx][ny], nx, ny);
                        grid[nx][ny] = 0;
                    }
                }
            }
            ans[idx[i]] = cnt;
        }
        return ans;
    }
};

// Union Find  
class Solution {
    const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
public:
    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
        const int m = grid.size(), n = grid[0].size(), mn = m * n;
        vector<int> pa(mn), size(mn, 1);
        iota(pa.begin(), pa.end(), 0);
        auto find = [&](int x) -> int { 
            int rt = x;
            while (rt != pa[rt])
                rt = pa[rt];
            while (x != pa[x]) {
                int tmp = pa[x];
                pa[x] = rt;
                x = tmp;
            }
            return rt;
        };
        auto merge = [&](int from, int to) {
            from = find(from);
            to = find(to);
            if (from != to) {
                pa[from] = to;
                size[to] += size[from];
            }
        };

        array<int, 3> a[mn];
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                a[i * n + j] = {grid[i][j], i, j};
        sort(a, a + mn);
        int k = queries.size(), id[k];
        iota(id, id + k, 0);
        sort(id, id + k, [&](int i, int j) { return queries[i] < queries[j]; });

        vector<int> ans(k);
        int j = 0;
        for (int i : id) {
            int q = queries[i];
            for (; j < mn && a[j][0] < q; ++j) {
                int x = a[j][1], y = a[j][2];
                for (auto &d : dirs) {
                    int x2 = x + d[0], y2 = y + d[1];
                    if (0 <= x2 && x2 < m && 0 <= y2 && y2 < n && grid[x2][y2] < q)
                        merge(x * n + y, x2 * n + y2);
                }
            }
            if (grid[0][0] < q)
                ans[i] = size[find(0)];
        }
        return ans;
    }
};
