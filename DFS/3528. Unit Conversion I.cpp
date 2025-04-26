// TC:O(N + E) SC:O(N + E)
class Solution {
    using ll = long long;
    ll MOD = 1e9 + 7;
public:
    vector<int> baseUnitConversions(vector<vector<int>>& conversions) {
        /*
        給你一堆某個字轉到某個字的關係 ex: 
        */
        int n = conversions.size() + 1;
        vector<vector<pair<ll, ll>>> next(n);
        for(auto & c : conversions) {
            next[c[0]].emplace_back(c[1], c[2]); // 題目保證不用反過來
        }
        vector<int> ans(n);
        auto dfs = [&](this auto&& dfs, int u, int f, int v) -> void {
            ans[u] = v;
            for (auto & [nxt, nw] : next[u]) {
                if (nxt != f) {
                    dfs(nxt, u, (v * nw) % MOD);
                }
            }
        };
        dfs(0, -1, 1);
        return ans;
    }
};
