/*
2858. Minimum Edge Reversals So Every Node Is Reachable
*/

// 1202
// 寫成Bit
class Solution {
    using LL = long long;
public:
    vector<int> minEdgeReversals(int n, vector<vector<int>>& edges) {
        vector<vector<int>> next(n);
        unordered_set<LL> set;
        vector<int> res(n);
        for(auto &e : edges) {
            next[e[0]].push_back(e[1]);
            next[e[1]].push_back(e[0]);
            set.insert(((LL)e[0] << 32) | e[1]);
        }
        int root0 = 0;
        auto dfs0 = [&](auto &&dfs0, int cur, int prev) -> void {
            for(auto &nxt : next[cur]) {
                if(nxt != prev) {
                    if(set.find(((LL)cur<<32) | nxt) == set.end()) {
                        root0 += 1;
                    }
                    dfs0(dfs0, nxt, cur);
                }
            }
        };
        dfs0(dfs0, 0, -1);
        res[0] = root0;
        auto dfs = [&](auto &&dfs, int cur, int prev) -> void {
            for(auto &nxt : next[cur]) {
                if(nxt != prev) {
                    if(set.find(((LL)nxt<<32) | cur) != set.end()) {
                        res[nxt] = res[cur] - 1;
                    }
                    else res[nxt] = res[cur] + 1;
                    dfs(dfs, nxt, cur);
                }
            }
        };
        dfs(dfs, 0, -1);
        return res;
    }
};

// 用unordered_map<int, unordered_set<int>> 包起來
class Solution {
public:
    vector<int> minEdgeReversals(ixnt n, vector<vector<int>>& edges) {
        vector<vector<int>> next(n);
        unordered_map<int, unordered_set<int>> map;
        vector<int> res(n);
        for(auto &e : edges) {
            next[e[0]].push_back(e[1]);
            next[e[1]].push_back(e[0]);
            map[e[0]].insert(e[1]);
        }
        int root0 = 0;
        auto dfs0 = [&](auto &&dfs0, int cur, int prev) -> void {
            for(auto &nxt : next[cur]) {
                if(nxt != prev) {
                    if(map[cur].find(nxt) == map[cur].end()) {
                        root0 += 1;
                    }
                    dfs0(dfs0, nxt, cur);
                }
            }
        };
        dfs0(dfs0, 0, -1);
        res[0] = root0;
        auto dfs = [&](auto &&dfs, int cur, int prev) -> void {
            for(auto &nxt : next[cur]) {
                if(nxt != prev) {
                    if(map[nxt].find(cur) != map[nxt].end()) {
                        res[nxt] = res[cur] - 1;
                    }
                    else res[nxt] = res[cur] + 1;
                    dfs(dfs, nxt, cur);
                }
            }
        };
        dfs(dfs, 0, -1);
        return res;
    }
};

// TC:O(n) SC:O(n+m)
class Solution {
    using LL = long long;
    int count0 = 0;
    vector<int> res;
    unordered_set<LL> set;
    vector<vector<int>> next;
public:
    vector<int> minEdgeReversals(int n, vector<vector<int>>& edges) {
        next.resize(n);
        for(auto edge : edges){
            set.insert(((LL)edge[0]<<32) | edge[1]);
            next[edge[0]].push_back(edge[1]);
            next[edge[1]].push_back(edge[0]);
        }
        res.resize(n);
        DFS(0,-1);
        
        reRoot(0,-1,count0);

        return res;
    }
    void DFS(int cur, int pa){
        for(auto nxt : next[cur]){
            if(nxt == pa) continue;
            if(set.find(((LL)cur << 32) | nxt) == set.end()){
                count0 += 1;
            }
            DFS(nxt, cur);
        }
    }
    void reRoot(int cur, int pa, int count){
        res[cur] = count;
        for(auto nxt : next[cur]){
            int countNow = count;
            if(pa == nxt) continue;
            if(set.find(((LL)cur<<32) | nxt) == set.end()){
                countNow -= 1;                
            }
            if(set.find(((LL)nxt<<32) | cur) == set.end()){
                countNow += 1;
            }
            reRoot(nxt, cur, countNow);
        }
    }
};
