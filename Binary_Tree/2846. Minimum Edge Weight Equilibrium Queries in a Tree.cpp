// 2025.04.25
class Solution {
    using PII = pair<int,int>;
public:
    vector<int> minOperationsQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        /*
        這題就是要求 兩個點之間最多有多少個相同的數字，那麼他們之間的距離扣掉相同數字數量就是每次query答案
        n = q = 1e4, w = 26
        */
        vector<vector<PII>> next(n);
        for (auto &e : edges) {
            next[e[0]].emplace_back(e[1], e[2]);
            next[e[1]].emplace_back(e[0], e[2]);
        }
        int power = bit_width(unsigned(n));
        vector stjump(n, vector<int>(power + 1)); // 每個點開跳可以跳到哪
        vector<int> deep(n); // 每個節點深度 方便你去鎖定LCA
        vector presum(n, vector<int>(27)); // 走到每個點時他的prefix sum狀況
        auto dfs = [&](this auto&&dfs, int u, int f, int w) -> void { // 去創建deep，presum, stjump
            if (u != 0) {
                for (int i = 1; i <= 26; i++) {
                    presum[u][i] = presum[f][i];
                }
                deep[u] = deep[f] + 1;
                presum[u][w] += 1;
            }
            else deep[u] = 1;
            stjump[u][0] = f;
            for (int p = 1; (1 << p) < deep[u]; p++) {
                stjump[u][p] = stjump[stjump[u][p-1]][p-1];
            }
            for (auto &[nxt, nxt_w] : next[u]) {
                if (nxt != f) dfs(nxt, u, nxt_w);
            }
        };
        dfs(0, 0, 0);
        auto LCA = [&](int a, int b) -> int {
            if (deep[a] < deep[b]) {
                int tmp = a;
                a = b;
                b = tmp;
            }
            for (int p = power; p >= 0; p--) {
                if (deep[stjump[a][p]] >= deep[b]) {
                    a = stjump[a][p];
                }
            }
            if (b == a) return a;
            for (int p = power; p >= 0; p --) {
                if (stjump[a][p] != stjump[b][p]) {
                    a = stjump[a][p];
                    b = stjump[b][p];
                }
            }
            return stjump[a][0];
        };
        vector<int> ans;
        for (auto &q : queries) {
            int a = q[0], b = q[1];
            int lca = LCA(a, b);
            int sum = 0, maxFreq = 0;
            for (int j = 1; j <= 26; j++) {
                int tmp = presum[a][j] + presum[b][j] - presum[lca][j] * 2;
                maxFreq = max(maxFreq, tmp);
                sum += tmp;
            }
            ans.emplace_back(sum - maxFreq);
        }
        return ans;
    }
};

// TC: O(n*lgn + m*(lgn + 26)) SC:O(n * max(power, 27))
class Solution {
    using PII = pair<int,int>;
public:
    vector<int> minOperationsQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        vector<vector<PII>> next(n);
        for(auto &e : edges) {
            next[e[0]].push_back({e[1], e[2]});
            next[e[1]].push_back({e[0], e[2]});
        }
        auto log2 = [](int n) -> int{
            int ans = 0;
            while((1<<ans) <= (n>>1)) {
                ans += 1;
            }
            return ans;
        };
        int power = log2(n);
        // 計算從起點到終點presum 以及順便求st表還有deep
        vector<vector<int>> stjump(n, vector<int>(power+1));
        vector<int> deep(n);
        vector<vector<int>> presum(n, vector<int>(27));
        auto dfs = [&](auto &&dfs, int u, int w, int f) -> void {
            if(u != 0) {
                for(int i = 1; i <= 26; i++) {
                    presum[u][i] = presum[f][i];
                }
                presum[u][w] += 1;
                deep[u] = deep[f] + 1;
            }
            else deep[u] = 1;
            stjump[u][0] = f;
            for(int p = 1; (1<<p) <= deep[u]; p++) {
                stjump[u][p] = stjump[stjump[u][p-1]][p-1];
            }

            for(auto &[nxt, nxt_weight] : next[u]) {
                if(nxt != f)
                    dfs(dfs, nxt, nxt_weight, u);
            }
        };
        dfs(dfs, 0, 0, 0);
        // 預處理LCA
        auto LCA = [&](int a, int b) -> int {
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

            if(b == a) return a;
            for(int p = power; p >= 0; p--) {
                if(stjump[a][p] != stjump[b][p]) {
                    a = stjump[a][p];
                    b = stjump[b][p];
                }
            }

            return stjump[a][0];
        };
        int m = queries.size();
        vector<int> res(m);
        for(int i = 0; i < m; i++) {
            int a = queries[i][0];
            int b = queries[i][1];
            int lca = LCA(a, b);
            vector<int> cur_presum(27);
            int maxFreq = 0;
            int sum = 0;
            for(int j = 1; j <= 26; j++) {
                cur_presum[j] = presum[a][j] + presum[b][j] - 2 * presum[lca][j];
                maxFreq = max(maxFreq, cur_presum[j]);
                sum += cur_presum[j];
            }
            res[i] = sum - maxFreq;
        }

        return res;
    }
};

/*
一棵樹上的邊有權重
給一段query 問你這個區間內 要把所有邊權改成相同所需花費的改動次數最少多少
所以需要在lgn or constant 做這件事
會想知道說這段節點有的字母count數 可以從頂向下presum計算
計算結果兩段 - root到兩段的共同祖先*2 就會是他的數量 取最多數量的

*/
