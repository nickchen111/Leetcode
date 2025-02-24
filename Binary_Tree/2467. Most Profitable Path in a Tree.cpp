// TC:O(n) SC:O(n)
class Solution {
public:
    int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount) {
        int n = edges.size() + 1;
        vector<vector<int>> g(n);
        for(auto &e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        // 開始BFS走看看哪個比較好 好像可以設定個時間戳 先讓bob走 反正他走的路徑固定
        vector<int> bob_time(n,n);
        auto dfs_bob = [&](auto &&dfs_bob, int i, int pa, int time) -> bool {
            if(i == 0) {
                bob_time[i] = time;
                return true;
            }
            for(auto &nxt : g[i]) {
                if(nxt != pa) {
                    if(dfs_bob(dfs_bob, nxt, i, time + 1)) {
                        bob_time[i] = time;
                        return true;
                    }
                }
            }
            return false;
        };
        dfs_bob(dfs_bob, bob, -1, 0);
        auto dfs = [&](auto &&dfs, int i, int pa, int time) -> int {
            int ans = 0;
            // 一起抵達
            if(bob_time[i] == time) ans = amount[i] / 2;
            // alice 太晚抵達
            else if(bob_time[i] < time) ans = 0;
            // alice 較早抵達
            else ans = amount[i];
            int ret = INT_MIN/2;
            for(auto &nxt : g[i]) {
                if(nxt != pa) {
                    ret = max(ret, dfs(dfs, nxt, i, time + 1));
                }
            }
            return (ret == INT_MIN/2 ? 0 : ret) + ans;
        };
        return dfs(dfs, 0, -1, 0);
    }
};

/*
a: 0, bob : bob
走一走可能會互相撞到 這種情況該如何做?
我可以在BFS中的每一輪 先去記錄這些點在這一輪被看過 如果當前某人選的點跟Bob想選的點一樣
*/
