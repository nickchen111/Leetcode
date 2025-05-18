// TC:O((n + q) * lgn) SC:O(n)
class Solution {
public:
    vector<int> minimumWeight(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size() + 1;
        int power = bit_width(unsigned(n));
        vector<vector<pair<int, int>>> next(n);
        vector<vector<int>> stjump(n, vector<int>(power, -1));
        vector<int> depth(n, 0), dist(n, 0);

        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            next[u].emplace_back(v, w);
            next[v].emplace_back(u, w);
        }

        auto dfs = [&](this auto&& dfs, int x, int fa) -> void {
            stjump[x][0] = fa;
            for (auto& [y, w] : next[x]) {
                if (y != fa) {
                    depth[y] = depth[x] + 1;
                    dist[y] = dist[x] + w;
                    dfs(y, x);
                }
            }
        };
        dfs(0, -1);

        // Binary Lifting
        for (int j = 1; j < power; ++j) {
            for (int i = 0; i < n; ++i) {
                if (stjump[i][j - 1] != -1) {
                    stjump[i][j] = stjump[stjump[i][j - 1]][j - 1];
                }
            }
        }

        // LCA
        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);
            for (int j = power - 1; j >= 0; --j) {
                if (stjump[u][j] != -1 && depth[stjump[u][j]] >= depth[v]) {
                    u = stjump[u][j];
                }
            }
            if (u == v) return u;
            for (int j = power - 1; j >= 0; --j) {
                if (stjump[u][j] != -1 && stjump[u][j] != stjump[v][j]) {
                    u = stjump[u][j];
                    v = stjump[v][j];
                }
            }
            return stjump[u][0];
        };

        auto get_dist = [&](int u, int v) {
            int anc = lca(u, v);
            return dist[u] + dist[v] - 2 * dist[anc];
        };

        vector<int> ans;
        for (auto& q : queries) {
            int a = q[0], b = q[1], c = q[2];
            int ab = get_dist(a, b);
            int ac = get_dist(a, c);
            int bc = get_dist(b, c);
            int total = (ab + ac + bc) / 2;
            ans.push_back(total);
        }

        return ans;
    }
};
