class Solution {
public:
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        unordered_map<int, vector<int>> next;
        unordered_map<int, int> deg;
        vector<vector<int>> res;
        for(auto &pair : pairs) {
            next[pair[0]].push_back(pair[1]);
            deg[pair[0]] -= 1;
            deg[pair[1]] += 1;
        }
        auto dfs = [&](auto &&dfs, int cur) -> void {
            vector<int> &e = next[cur];
            while(!e.empty()) {
                int nxt = e.back();
                e.pop_back();
                dfs(dfs, nxt);
                res.push_back({cur,nxt});
            }
        };
        for(auto it = deg.begin(); it != deg.end(); it++) {
            if(it->second == -1) dfs(dfs, it->first);
        }
        if(res.empty()) dfs(dfs, deg.begin()->first);
        reverse(res.begin(), res.end());

        return res;
    }
};
