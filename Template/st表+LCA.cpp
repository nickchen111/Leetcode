// 一般array 模板
template<typename T>
class SparseTable {
    vector<vector<int>> st;
public:
    // 創建表的build function
    SparseTable (vector<T>& a) {
        int n = a.size() - 1;
        int sz = bit_width(unsigned(n));
        st.resize(n, vector<int>(sz));
        // 走2^0步的時候所有點兩個區間加總
        for (int i = 0; i < n; i++) {
            st[i][0] = a[i].r - a[i].l + a[i+1].r - a[i+1].l; // 轉成題目要做的事情
        }
        for(int j = 1; j < sz; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[i][j] = max(st[i][j-1], st[i + (1 << (j - 1))][j-1]); // 改成題目要做的事情
            }
        }
    }
    int query(int l, int r) { // 左閉右開 查詢完整區間的最大值 只有一個區間不算
        if (l >= r) return 0;
        int k = bit_width(unsigned(r - l)) - 1;
        return max(st[l][k], st[r - (1 << k)][k]);
    }
};


// LCA 修改模板
class Solution {
public:
    vector<int> minimumWeight(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size() + 1;
        int power = bit_width(unsigned(n));
        vector<vector<pair<int, int>>> next(n);
        vector<vector<int>> stjump(n, vector<int>(power, -1));
        vector<int> deep(n, 0), dist(n, 0); // dist 用來當作root 到 i 的weight和 想成前綴和

        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            next[u].emplace_back(v, w);
            next[v].emplace_back(u, w);
        }

        // DFS 建立深度與父節點表
        function<void(int, int)> dfs = [&](int u, int p) {
            // 拿到外面做liting即可
            // stjump[u][0] = p;
            // for(int step = 1; (1 << step) <= deep[u]; step++) {
            //     if (stjump[u][step-1] != -1) {
            //         stjump[u][step] = stjump[stjump[u][step-1]][step-1];
            //     }
            // }
            for (auto& [v, w] : next[u]) {
                if (v == p) continue;
                deep[v] = deep[u] + 1;
                stjump[v][0] = u; // 走一步放在這裡
                dist[v] = dist[u] + w;
                dfs(v, u);
            }
        };
        dfs(0, -1);

        // Binary Lifting 預處理
        for (int j = 1; j < power; ++j) {
            for (int i = 0; i < n; ++i) {
                if (stjump[i][j - 1] != -1) {
                    stjump[i][j] = stjump[stjump[i][j - 1]][j - 1];
                }
            }
        }

        // LCA 查詢
        auto lca = [&](int u, int v) {
            if (deep[u] < deep[v]) swap(u, v);
            for (int j = power - 1; j >= 0; --j) {
                if (stjump[u][j] != -1 && deep[stjump[u][j]] >= deep[v]) {
                    u = stjump[u][j];
                }
            }
            if (u == v) return u;
            for (int j = power - 1; j >= 0; --j) {
                if (stjump[u][j] != -1 && stjump[u][j] != stjump[v][j]) {
                    u = stjump[u][j];
                    v = stjump[v][j];
                }
            }
            return stjump[u][0];
        };

        // auto get_dist = [&](int u, int v) {
        //     int anc = lca(u, v);
        //     return dist[u] + dist[v] - 2 * dist[anc];
        // };

        // vector<int> ans;
        // for (auto& q : queries) {
        //     int a = q[0], b = q[1], c = q[2];
        //     int ab = get_dist(a, b);
        //     int ac = get_dist(a, c);
        //     int bc = get_dist(b, c);
        //     int total = (ab + ac + bc) / 2;
        //     ans.push_back(total);
        // }

        // return ans;
    }
};


// LCA 模板
class TreeAncestor {
    vector<vector<int>> next;
    vector<int> deep;
    vector<vector<int>> stjump;
    int power;
public:
    TreeAncestor(int n, vector<int>& parent) {
        // 建造圖，如果要知道自己之前的parent 回頭traverse n^2
        next.resize(n);
        deep.resize(n);
        power = log2(n); // 或者可以直接bit_width(unsigned(n));
        stjump.resize(n, vector<int>(power+1));
        for(int i = 0; i < parent.size(); i++) {
            if(parent[i] != -1) {
                next[parent[i]].push_back(i);
            }
        }
        dfs(0, 0);
        
    }
    
    int getKthAncestor(int node, int k) {
        if(deep[node] <= k) return -1;
        int s = deep[node] - k; // 想抵達的深度
        for(int p = power; p >= 0; p--) {
            if(deep[stjump[node][p]] >= s) {
                node = stjump[node][p];
            }
        }

        return node;
    }
    int log2(int n) {
        int ans = 0;
        while((1<<ans) <= (n >> 1)) {
            ans ++;
        }

        return ans;
    }
    void dfs(int cur, int prev) {
        if(cur == 0) deep[cur] = 1;
        else deep[cur] = deep[prev] + 1;
        stjump[cur][0] = prev;
        for(int p = 1; (1 << p) < deep[cur]; p++) {
            stjump[cur][p] = stjump[stjump[cur][p-1]][p-1];
        }
        for(auto &nxt : next[cur]) {
            dfs(nxt, cur);
        }
    }
    // 如何LCA計算兩點的LCA for 在線查詢
    int LCA(int a, int b){
        if(deep[a] < deep[b]) {
            int tmp = a;
            a = b;
            b = tmp;
        }
        for(int p = power; p >= 0; p--) {
            if(deep[stjump[a][p]] >= deep[b]) {
                a = stjump[a][p];
            }
        }
    
        if(a == b) return a;
        for(int p = power; p >= 0; p--) {
            if(stjump[a][p] != stjump[b][p]) {
                a = stjump[a][p];
                b = tjump[b][p];
            }
        }
    
        return stjump[a][0];
      
    }
};
