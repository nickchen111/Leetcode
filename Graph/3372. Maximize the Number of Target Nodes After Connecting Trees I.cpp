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
        vector<vector<int>> next1(n);
        vector<vector<int>> next2(m);
        auto build = [](vector<vector<int>>& edges, vector<vector<int>>& next, vector<int>& pre, int k) -> void {
            int n = edges.size()+1;
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
        build(edges1, next1, pre1, k);
        build(edges2, next2, pre2, k-1);
        
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
