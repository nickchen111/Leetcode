const int MX = 1000001;
int core[MX];
int init = [] {
    for (int i = 1; i < MX; i++) {
        if (core[i] == 0) {
            for (int j = 1; i * j * j < MX; j++) {
                core[i * j * j] = i;
            }
        }
    }
    return 0;
}();

class Solution {
    using ll = long long;
public:
    long long sumOfAncestors(int n, vector<vector<int>>& edges, vector<int>& nums) {
        vector<vector<int>> g(n);
        for (auto &e : edges) {
            g[e[0]].emplace_back(e[1]);
            g[e[1]].emplace_back(e[0]);
        }
        ll ans = 0;
        unordered_map<int,int> cnt;
        auto dfs = [&](this auto&& dfs, int cur, int prev) -> void {
            int c = core[nums[cur]];
            ans += cnt[c];
            cnt[c] += 1;
            for (auto &nxt : g[cur]) {
                if (prev == nxt) continue;
                dfs(nxt, cur);
            }
            cnt[c] -= 1;
        };
        dfs(0, -1);
        return ans;
    }
};