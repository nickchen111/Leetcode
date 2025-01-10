// Heap TC:O((mnlgmn + k)+ klgk) SC:O(mn)
class Solution {
public:
    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
        int m = grid.size(), n = grid[0].size();
        int k = queries.size();
        
        vector<int> ans(k);
        vector<pair<int, int>> query_with_index;
        
        for (int i = 0; i < k; i++) {
            query_with_index.push_back({queries[i], i});
        }
        
        sort(query_with_index.begin(), query_with_index.end());
        
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<int> dirs = {0, 1, 0, -1, 0};
        
        // 優先隊列處理 BFS，按數值排序
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
        pq.push({grid[0][0], 0, 0});
        visited[0][0] = true;
        
        int count = 0;
        int prev_query = 0;
        
        for (auto [limit, index] : query_with_index) {
            while (!pq.empty() && get<0>(pq.top()) < limit) {
                auto [val, x, y] = pq.top();
                pq.pop();
                count++;
                
                for (int i = 0; i < 4; i++) {
                    int nx = x + dirs[i];
                    int ny = y + dirs[i + 1];
                    if (nx >= 0 && ny >= 0 && nx < m && ny < n && !visited[nx][ny]) {
                        visited[nx][ny] = true;
                        pq.push({grid[nx][ny], nx, ny});
                    }
                }
            }
            ans[index] = count;
        }
        
        return ans;
    }
};

// Union Find 
class Solution {
public:
    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
        int m = grid.size(), n = grid[0].size();
        int k = queries.size(), mn = m*n;
        
        vector<int> size(mn,1);
        vector<int> pa(mn);
        iota(pa.begin(), pa.end(), 0);
        auto find = [&](int x) -> int {
            int rt = x;
            while(rt != pa[rt]) rt = pa[rt];
            if(x != rt) pa[x] = rt;
            return rt;
        };
        auto merge = [&](int fr, int to) -> void {
            fr = find(fr), to = find(to);
            if(fr < to) {
                pa[to] = fr;
                size[fr] += size[to];
            }
            else if((fr > to)){
                pa[fr] = to;
                size[to] += size[fr];
            }
        };

        vector<pair<int,int>> query(k);
        for(int i = 0; i < k; i++) {
            query[i] = {queries[i], i};
        }
        sort(query.begin(), query.end());
        vector<tuple<int,int,int>> edges;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(i) edges.push_back({max(grid[i][j], grid[i-1][j]), i*n + j, (i-1)*n + j});
                if(j) edges.push_back({max(grid[i][j], grid[i][j-1]), i*n + j, i*n + j - 1});
            }
        }
        sort(edges.begin(), edges.end());
        vector<int> ans(k);
        int j = 0;
        for(int i = 0; i < k; i++) {
            int limit = query[i].first, idx = query[i].second;
            while(j < edges.size() && get<0>(edges[j]) < limit) {
                merge(get<1>(edges[j]), get<2>(edges[j]));
                j++;
            }
            if(grid[0][0] < limit) ans[idx] = size[0];
        }

        return ans;
    }
};
