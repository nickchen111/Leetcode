/*
2538. Difference Between Maximum and Minimum Price Sum
*/

// TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long maxOutput(int n, vector<vector<int>>& edges, vector<int>& price) {
        vector<vector<LL>> next(n);
        for(int i = 0; i < edges.size(); i++) {
            next[edges[i][0]].push_back(edges[i][1]);
            next[edges[i][1]].push_back(edges[i][0]);
        }
        LL res = 0;
        auto dfs = [&](auto &&dfs, int cur, int prev) -> pair<LL, LL> {
            LL p = price[cur];
            LL max_s1 = p;
            LL max_s2 = 0;
            for(auto &nxt : next[cur]) {
                if(nxt == prev) continue;
                auto [s1, s2] = dfs(dfs, nxt, cur);
                res = max({res, max_s1 +s2, max_s2 + s1});
                max_s1 = max(max_s1, s1 + p);
                max_s2 = max(max_s2, s2 + p);
            }
            return {max_s1, max_s2};
        };
        dfs(dfs, 0, -1);

        return res;
    }
};
