// TC:O(nm) SC:O(n + m)
class Solution {
public:
    int magnificentSets(int n, vector<vector<int>>& edges) {
        vector<vector<int>> next(n);
        for(auto &e : edges) {
            next[e[0] - 1].emplace_back(e[1] - 1);
            next[e[1] - 1].emplace_back(e[0] - 1);
        }
        vector<int> color(n);
        vector<int> node;
        int clock = 0;
        vector<int> time(n);
        auto bfs = [&](int i) -> int {
            int depth = 0;
            time[i] = ++clock;
            vector<int> q = {i};
            while (!q.empty()) {
                vector<int> nxt;
                for (int x : q)
                    for (int y : next[x])
                        if (time[y] != clock) { // 没有在同一次 BFS 中訪問過
                            time[y] = clock;
                            nxt.push_back(y);
                        }
                q = move(nxt);
                ++depth;
            }
            return depth;
        };
        auto dfs = [&](auto &&dfs, int i, int c) -> bool {
            node.emplace_back(i);
            color[i] = c;
            for(auto &nxt : next[i]) {
                if(color[nxt] == c || (color[nxt] == 0 && !dfs(dfs, nxt, 3-c))) return false;
            }
            return true;
        };
        int ans = 0;
        for(int i = 0; i < n; i++) {
            if(color[i]) continue;
            node.clear();
            if(!dfs(dfs, i, 1)) return -1;
            int maxDepth = 0;
            for(int &x : node) {
                maxDepth = max(maxDepth, bfs(x));
            }
            ans += maxDepth;
        }
        return ans;
    }
};


/*
從樣例可以發現樹是一定可以
如果是圖 有環的話 odd不行 even可以
|y - x| = 1 的性質可以得證 每走一步編號的odd even性質一定變了
隨便畫個圖 都可以證明出來 所以會想到可以用二分圖的做法把節點染色
*/
