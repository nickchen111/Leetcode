/*
3373. Maximize the Number of Target Nodes After Connecting Trees II
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
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
        
        vector<pair<int,int>> subtree1(n);
        vector<pair<int,int>> subtree2(m); // even, odd
        
        auto dfs0 = [&](auto &&dfs0, int cur, int prev, vector<vector<int>>& next, vector<pair<int,int>>& subtree) -> pair<int,int> {
            pair<int,int> p = {1, 0}; // 現在節點本身是偶數距離
            
            for(auto &nxt : next[cur]) {
                if(nxt == prev) continue;
                auto e = dfs0(dfs0, nxt, cur, next, subtree);
                // 子節點的偶數距離變成奇數距離，奇數距離變成偶數距離
                p.first += e.second;  // 偶數加子節點的奇數
                p.second += e.first;  // 奇數加子節點的偶數
            }
            subtree[cur] = p;
            return p;
        };
        
        auto dfs1 = [&](auto &&dfs1, int cur, int prev, vector<vector<int>>& next, 
                       vector<pair<int,int>>& subtree, vector<pair<int,int>>& tree) -> void {
            pair<int,int> total = subtree[cur];
            if (prev != -1) {
                auto p = tree[prev];
                p.first -= subtree[cur].second;  // 減去當前節點對父節點的奇數貢獻
                p.second -= subtree[cur].first;  // 減去當前節點對父節點的偶數貢獻
                // 轉換父節點剩餘部分的奇偶性
                total.first += p.second;
                total.second += p.first;
            }
            tree[cur] = total;
            
            for(auto &nxt : next[cur]) {
                if(nxt == prev) continue;
                dfs1(dfs1, nxt, cur, next, subtree, tree);
            }
        };
        
        // 計算每個子樹的貢獻
        dfs0(dfs0, 0, -1, next1, subtree1);
        dfs0(dfs0, 0, -1, next2, subtree2);
        
        // 計算完整樹的貢獻
        vector<pair<int,int>> tree1(n);
        vector<pair<int,int>> tree2(m);
        dfs1(dfs1, 0, -1, next1, subtree1, tree1);
        dfs1(dfs1, 0, -1, next2, subtree2, tree2);
        
        // 找到第二棵樹中最大的偶數距離節點數
        int maxEven = 0;
        for(int i = 0; i < m; i++) {
            maxEven = max(maxEven, tree2[i].second);
        }
        
        // 計算答案
        vector<int> res(n);
        for(int i = 0; i < n; i++) {
            res[i] = tree1[i].first + maxEven;
        }
        
        return res;
    }
};
/*
這題換成需要連接的edge長度是偶數
並且數據需要O(n)處理
自處理的部分 可以reroot ? or 
上一個節點 odd, even 數量是？
*/
