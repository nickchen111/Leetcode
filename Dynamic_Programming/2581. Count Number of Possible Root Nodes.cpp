/*
2581. Count Number of Possible Root Nodes
*/

// 1203
class Solution {
    using LL = long long;
public:
    int rootCount(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) {
        int n = edges.size() + 1;
        unordered_set<LL> set;
        for(auto &g : guesses) {
            set.insert(((LL)g[0]<<32) | g[1]);
        }
        vector<vector<LL>> next(n);
        for(auto &e : edges) {
            next[e[0]].push_back(e[1]);
            next[e[1]].push_back(e[0]);
        }
        int root0 = 0;
        vector<int> validRoot(n);
        auto dfs0 = [&](auto &&dfs0, LL cur, LL prev) -> void {
            for(auto &nxt : next[cur]) {
                if(nxt != prev) {
                    if(set.find((cur << 32) | nxt) != set.end()) {
                        root0 += 1;
                    }
                    dfs0(dfs0, nxt, cur);
                }
            }
        };
        dfs0(dfs0, 0, -1);
        validRoot[0] = root0;
        int res = root0 >= k;
        auto dfs = [&](auto &&dfs, LL cur, LL prev) -> void {
            for(auto &nxt : next[cur]) {
                if(nxt != prev) {
                    if(set.find((nxt<<32) | cur) == set.end() && set.find((cur<<32) | nxt) != set.end()) {
                        validRoot[nxt] = validRoot[cur] - 1;
                    }
                    else if(set.find((nxt<<32) | cur) != set.end() && set.find((cur<<32) | nxt) == set.end()) {
                        validRoot[nxt] = validRoot[cur] + 1;
                    }
                    else validRoot[nxt] = validRoot[cur];
                    res += (validRoot[nxt] >= k);
                    dfs(dfs, nxt, cur);
                }
            }
        };
        dfs(dfs, 0, -1);
        
        return res;
    }
};

/*
所以問題轉變成 某個點當root Bob猜的edge有哪些是對的 並且至少要有k個猜對

*/

// TC:O(n) SC:O(n+m)
class Solution {
    using LL = long long;
    vector<vector<int>> next;
    unordered_set<LL> set;
    int res = 0;
    int count0 = 0;
public:
    int rootCount(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) {
        int n = edges.size();
        next.resize(n+1);
        for(auto edge : edges){
            next[edge[0]].push_back(edge[1]);
            next[edge[1]].push_back(edge[0]);
        }

        for(auto g : guesses){
            set.insert(((LL)g[0]<<32) | g[1]);
        }
        DFS(0, -1);
        reRoot(0,-1, k, count0);
        
        return res;
    }
    void DFS(int cur, int pa){
        
        for(auto nxt : next[cur]){
            if(nxt == pa) continue;
            if(set.find(((LL)cur<<32) | nxt) != set.end()) {
                count0 += 1;
            }
            DFS(nxt, cur);
        }

    }
    void reRoot(int cur, int pa, int k, int count){

        if(count >= k) res += 1;
        for(auto nxt : next[cur]){
            if(nxt == pa) continue;
            int countNow = count;
            if(set.find(((LL)cur<<32) | nxt) != set.end()) {
                countNow -= 1;
            }
            if(set.find(((LL)nxt<<32) | cur) != set.end()) {
                countNow += 1;
            }
            reRoot(nxt, cur, k, countNow);
        }
    }
};
