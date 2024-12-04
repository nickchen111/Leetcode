/*
3372. Maximize the Number of Target Nodes After Connecting Trees I
*/


// TC:O(n*k + m*k) SC:O(n + m)
class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2, int k) {
        int n = edges1.size()+1;
        int m = edges2.size()+1;
        vector<int> pre1(n);
        vector<int> pre2(m);
        auto build = [](vector<vector<int>>& edges,  vector<int>& pre, int k) -> void {
            int n = edges.size()+1;
            vector<vector<int>> next(n);
            for(auto &e : edges) {
                next[e[0]].push_back(e[1]);
                next[e[1]].push_back(e[0]);
            }
            auto dfs = [&](auto &&dfs, int cur, int prev, int step, int idx) -> void {
                if(step > k) return;
                pre[idx] += 1;

                for(auto &nxt : next[cur]) {
                    if(nxt == prev) continue;
                    dfs(dfs, nxt, cur, step+1, idx);
                }
            };
            for(int i = 0; i < n; i++) {
                dfs(dfs, i, -1, 0, i);
            }
        };
        build(edges1, pre1, k);
        build(edges2, pre2, k-1);
        
        int maxVal = 0;
        for(int i = 0; i < m; i++) {
            maxVal = max(maxVal, pre2[i]);
        }
        vector<int> res(n);
        for(int i = 0; i < n; i++) {
            res[i] = pre1[i] + maxVal;
        }
        
        return res;
    }
};

// TC:O(n*k + m*k) SC:O(n + m) 比較不優雅一點比賽寫法
class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2, int k) {
        int n = edges1.size()+1;
        int m = edges2.size()+1;
        vector<vector<int>> next1(n);
        vector<vector<int>> next2(m);
        for(auto &e : edges1) {
            next1[e[0]].push_back(e[1]);
            next1[e[1]].push_back(e[0]);
        }
        for(auto &e : edges2) {
            next2[e[0]].push_back(e[1]);
            next2[e[1]].push_back(e[0]);
        }
        // 連過去另一邊的可以traverse 去判斷每個當連接點 可以走k步的node有多少個
        vector<int> pre1(n);
        vector<int> pre2(m);
        auto dfs0 = [&](auto &&dfs0, int cur, int prev, int step, vector<vector<int>>& next, vector<int>& pre, int idx) -> void {
            if(step == k) return;
            
            pre[idx] += 1;
            
            for(auto &nxt : next[cur]) {
                if(nxt == prev) continue;
                dfs0(dfs0, nxt, cur, step+1, next, pre, idx);
            }
        };
        for(int i = 0; i < m; i++) {
            dfs0(dfs0, i, -1, 0, next2, pre2, i);
        }
        int maxVal = 0;
        for(int i = 0; i < m; i++) {
            maxVal = max(maxVal, pre2[i]);
        }
        vector<int> res(n);
        auto dfs1 = [&](auto&& dfs1, int cur, int prev, int step, vector<int>& pre, int idx) -> void {
            if (step > k) return;
            pre[idx]++;
            for (int nxt : next1[cur]) {
                if (nxt == prev) continue;
                dfs1(dfs1, nxt, cur, step + 1, pre, idx);
            }
        };
        for(int i = 0; i < n; i++) {
            dfs1(dfs1, i, -1, 0, pre1, i);
            res[i] = pre1[i] + maxVal;
        }
        
        return res;
    }
};

// 移根寫法 TC:O((n + m)*k) SC:O((n + m)*k)
class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2, int k) {
        int n = edges1.size()+1;
        int m = edges2.size()+1;
        vector<vector<int>> dp1(n, vector<int>(k > 0 ? k + 1 : 1, 0)); // 定義為i走j步可以走到的點有多少個
        vector<vector<int>> dp2(m, vector<int>(k > 1 ? k : 1, 0));
        auto build = [](vector<vector<int>>& edges,  vector<vector<int>>& dp, int k) -> void {
            int n = edges.size()+1;
            vector<vector<int>> next(n);
            for(auto &e : edges) {
                next[e[0]].push_back(e[1]);
                next[e[1]].push_back(e[0]);
            }
            vector<vector<int>> subtree(n, vector<int>(k+1));
            for(int i = 0; i < n; i++) {
                subtree[i][0] = 1;
            }
            auto dfs0 = [&](auto &&dfs0, int cur, int prev) -> void {
                for(auto &nxt : next[cur]) {
                    if(nxt != prev) {
                        dfs0(dfs0, nxt, cur);
                        for(int j = 1; j <= k; j++) {
                            subtree[cur][j] += subtree[nxt][j-1];
                        }
                    }
                }
            };
            dfs0(dfs0, 0, -1);
            
            for(int i = 0; i <= k; i++) {
                dp[0][i] = subtree[0][i];
            }
            auto dfs = [&](auto &&dfs, int cur, int prev) -> void {
                for(auto &nxt : next[cur]) {
                    if(nxt != prev) {
                        dp[nxt][0] = subtree[nxt][0];
                        if(k >= 1) dp[nxt][1] = subtree[nxt][1] + dp[cur][0];
                        for(int j = 2; j <= k; j++) {
                            dp[nxt][j] = subtree[nxt][j] + dp[cur][j-1] - subtree[nxt][j-2];
                        }
                        dfs(dfs, nxt, cur);
                    }
                }
            };
            dfs(dfs, 0, -1);
        };
        build(edges1, dp1, k);
        if(k > 0) build(edges2, dp2, k-1);
        
        int maxVal = 0;
        for(int i = 0; i < m; i++) {
            int sum = 0;
            for(int j = 0; j <= k-1; j++){
                sum += dp2[i][j];
            }
            maxVal = max(maxVal, sum);
        }
        
        vector<int> res(n);
        for(int i = 0; i < n; i++) {
            int sum = 0;
            for(int j = 0; j <= k; j++) {
                sum += dp1[i][j];
            }
            res[i] = sum + maxVal;
        }
        
        return res;
    }
};
