// TC:O((n + q) * lgn) SC:O(nlgn)
struct Pair {int l, r;};
class SparseTable {
    vector<vector<int>> st;
public:
    // 創建表的build function
    SparseTable (vector<Pair>& a) {
        int n = a.size() - 1;
        int sz = bit_width(unsigned(n));
        st.resize(n, vector<int>(sz));
        // 走2^0步的時候所有點兩個區間加總
        for (int i = 0; i < n; i++) {
            st[i][0] = a[i].r - a[i].l + a[i+1].r - a[i+1].l;
        }
        for(int j = 1; j < sz; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[i][j] = max(st[i][j-1], st[i + (1 << (j - 1))][j-1]);
            }
        }
    }
    int query(int l, int r) { // 左閉右開 查詢完整區間的最大值 只有一個區間不算
        if (l >= r) return 0;
        int k = bit_width(unsigned(r - l)) - 1;
        return max(st[l][k], st[r - (1 << k)][k]);
    }
};
class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.size();
        int total1 = 0;
        vector<Pair> a = {{-1, -1}}; // 哨兵
        int start = 0;
        for(int i = 0; i < n; i++) {
            if (i == n-1 || s[i] != s[i+1]) {
                if (s[i] == '1') {
                    total1 += i - start + 1;
                }
                else {
                    a.emplace_back(start, i + 1); // 左閉右開
                }
                start = i + 1;
            }
        }
        a.emplace_back(n + 1, n + 1);
        auto merge = [](int x, int y) -> int {
            return x > 0 && y > 0 ? x + y : 0;
        };

        SparseTable st(a);
        vector<int> ans(queries.size());
        for (int qi = 0; qi < queries.size(); qi++) {
            int ql = queries[qi][0], qr = queries[qi][1] + 1;
            int i = ranges::lower_bound(a, ql, {}, [](const Pair& p) { return p.l; }) - a.begin();
            int j = ranges::upper_bound(a, qr, {}, [](const Pair& p) { return p.r; }) - a.begin() - 1;
            int mx = 0;
            if (i <= j) {
                mx = max({
                    st.query(i, j),
                    merge(a[i-1].r - ql, a[i].r - a[i].l),
                    merge(qr - a[j+1].l, a[j].r - a[j].l),
                });
            }
            else if(i == j + 1) {
                mx = merge(a[i - 1].r - ql, qr - a[j + 1].l);
            }
            ans[qi] = total1 + mx;
        }
        return ans;
    }
};
