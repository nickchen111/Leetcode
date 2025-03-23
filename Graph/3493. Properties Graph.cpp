// TC:O(n^3) SC:O(n^2)
class Solution {
public:
    int numberOfComponents(vector<vector<int>>& properties, int k) {
        int n = properties.size();
        vector<unordered_set<int>> set(n);
        vector<vector<int>> g(n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < properties[i].size(); j++) {
                set[i].insert(properties[i][j]);
            }
        }
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                int cnt = 0;
                for(int node : set[i]) {
                    if(set[j].count(node)) {
                        cnt += 1;
                        if (cnt == k) {
                            break;
                        }
                    }
                }
                if(cnt == k) {
                    g[i].emplace_back(j);
                    g[j].emplace_back(i);
                }
            }
        }
        vector<bool> visited(n);
        auto dfs = [&](auto &&dfs, int cur) -> void {
            visited[cur] = true;
            for(auto &nxt : g[cur]) {
                if(visited[nxt]) continue;
                dfs(dfs, nxt);
            }
        };
        int ans = 0;
        for(int i = 0; i < n; i++) {
            if(visited[i]) continue;
            ans += 1;
            dfs(dfs, i);
        }
        return ans;
    }
};
