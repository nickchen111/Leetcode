// TC:O((n + q) * lgn) SC:O(n)
template<typename T>
class Fenw {
    vector<T> tree;
public:
    Fenw(int n): tree(n+1, 0) {}

    void update(int i, T val) {
        for (; i < tree.size(); i += i & -i)
            tree[i] += val;
    }
    T pre(int i) {
        T res = 0;
        for (; i > 0; i -= i & -i)
            res += tree[i];
        return res;
    }
};
 
class Solution {
public:
    vector<int> treeQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        /*
        這題問你1走到任意點的最短距離，並且edge weight可能會改變，所以需要一個資料結構可以支持區間更新以及單點查詢
        -> BIT
        那要如何把樹上問題轉成數組內的區間? 要用DFS時間戳來表示
        1.  首先先把鄰接表創建好 
        2. 跑DFS 時間戳 可得到區間
        3. 藉由這些區間創建BIT
        4. 開始跑queries
        3 2 5 2 -> 3 -1 3 -3 差分 後面減掉前面
        */
        vector<vector<int>> nxt(n + 1);
        for(auto &e : edges) {
            nxt[e[0]].emplace_back(e[1]);
            nxt[e[1]].emplace_back(e[0]);
        }
        vector<int> in(n + 1), out(n + 1);
        int clock = 0;
        auto dfs = [&](this auto&& dfs, int x, int fa) -> void {
            in[x] = ++clock; // 進來時間
            for (auto &y : nxt[x]) {
                if (y != fa) {
                    dfs(y, x);
                }
            }
            out[x] = clock; // 離開時間
        };
        dfs(1, 0);
        vector<int> weight(n+1); // 要變化的數值都先存在子節點中
        Fenw<int> diff(n);
        auto update = [&](int x, int y, int w) -> void {
            if (in[x] > in[y]) y = x; // 保證y是子節點
            int d = w - weight[y];
            weight[y] = w;
            diff.update(in[y], d);
            diff.update(out[y] + 1, -d);
        };
        for (auto &e : edges) {
            update(e[0], e[1], e[2]);
        }
        vector<int> ans;
        for (auto &q : queries) {
            if (q[0] == 1) {
                update(q[1], q[2], q[3]);
            }
            else ans.emplace_back(diff.pre(in[q[1]]));
        }
        return ans;
    }
};

