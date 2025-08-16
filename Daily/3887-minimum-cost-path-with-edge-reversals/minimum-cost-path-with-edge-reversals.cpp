class Solution {
public:
    int minCost(int n, vector<vector<int>>& edges) {
        vector<vector<pair<int,int>>> g(n);
        vector<vector<pair<int,int>>> in(n);

        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            g[u].emplace_back(v, w); 
            in[v].emplace_back(u, w);
        }

        using T = pair<int,int>; // cost, node
        priority_queue<T, vector<T>, greater<T>> pq;

        vector<int> dist(n, INT_MAX);
        dist[0] = 0;
        pq.emplace(0, 0);
        while (!pq.empty()) {
            auto [cost, u] = pq.top();
            pq.pop();

            if (u == n - 1) {
                return cost;
            }
            if (cost > dist[u]) continue;

            for (auto [v, w] : g[u]) {
                int nxtCost = cost + w;
                if (nxtCost < dist[v]) {
                    dist[v] = nxtCost;
                    pq.emplace(nxtCost, v);
                }
            }

            
            for (auto [v, w] : in[u]) {
                int nxtCost = cost + 2 * w;
                if (nxtCost < dist[v]) {
                    dist[v] = nxtCost;
                    pq.emplace(nxtCost, v);
                }
            }
        }

        return -1;
    }
};