// Binary Search TC:O(nlgM) M為最大的邊權 SC:O(n)
class Solution {
public:
    int minMaxWeight(int n, vector<vector<int>>& edges, int threshold) {
        int res = -1;
        vector<int> visited(n, false);
        vector<vector<pair<int,int>>> g(n);
        for(auto &e : edges) {
            g[e[1]].push_back({e[0], e[2]});
        }
        auto check = [&](int mid) -> bool {
            // vector<int> outdegree(n, 0);
            // priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;
            // while(!pq.empty()) {
            //     auto [w, x, y] = pq.top();
            //     pq.pop();
            //     if(outdegree[x] < threshold) {
            //         g[y].push_back(x);
            //         outdegree[x] += 1;
            //     }
            // }
            
            // 檢查從其他節點是否都能到達節點0
            auto dfs = [&](auto&& dfs, int u) -> void {
                visited[u] = mid;
                for(auto &[v,w] : g[u]) {
                    if(visited[v] != mid && w <= mid) dfs(dfs, v);
                }
            };
            dfs(dfs, 0);
            for(int i = 0; i < n; i++) if(visited[i] != mid) return false;
            return true;
        };
        
        int left = 0, right = 1e6;
        while(left < right) {
            int mid = left + (right - left) / 2;
            if(check(mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        if(!check(left)) return -1;
        return left;
    }
};

// 最佳解 Dijkstra TC:O(nlgn) M為最大的邊權 SC:O(n)
class Solution {
public:
    int minMaxWeight(int n, vector<vector<int>>& edges, int threshold) {
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
        pq.push({0,0});
        vector<vector<pair<int,int>>> g(n);
        for(auto &e : edges) {
            g[e[1]].push_back({e[0], e[2]}); // 反向圖
        }
        vector<int> minDist(n, INT_MAX);
        while(!pq.empty()) {
            auto [w, x] = pq.top();
            pq.pop();
            if(minDist[x] <= w) continue;
            minDist[x] = w;
            for(auto &[nxt, nw] : g[x]) {
                if(minDist[nxt] > max(w, nw)) {
                    pq.push({max(w, nw), nxt});
                }
            }
        }
        int res = INT_MIN;
        for(int i = 0; i < n; i++) {
            res = max(res, minDist[i]);
        }
        return res == INT_MAX ? -1 : res;
    }
};
