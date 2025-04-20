// TC:O((n + q * lgn) * k) SC:O(n * k) 線段樹 無區間更新
class SegmentTree {
    using T = pair<int, array<int,5>>;
    int n;
    int k;
    vector<T> tree;
    T merge_val(T a, T b) const {
        auto [left_num, cnt] = a;
        for (int m = 0; m < k; m++) {
            cnt[(left_num * m) % k] += b.second[m];
        }
        return {(left_num * (b.first % k)) % k, cnt};
    }
    
    T new_val(int val) {
        int m = val % k;
        array<int, 5> cnt{};
        cnt[m] = 1;
        return {m, cnt};
    }

    void maintain(int node) {
        tree[node] = merge_val(tree[node * 2], tree[node * 2 + 1]);
    }

    void build(const vector<int>& a, int node, int l, int r) {
        if (l == r) { 
            tree[node] = new_val(a[l]);
            return;
        }
        int m = (l + r) / 2;
        build(a, node * 2, l, m);
        build(a, node * 2 + 1, m + 1, r);
        maintain(node);
    }

    void update(int node, int l, int r, int i, int val) {
        if (l == r) { 
            tree[node] = new_val(val);
            return;
        }
        int m = (l + r) / 2;
        if (i <= m) { 
            update(node * 2, l, m, i, val);
        } else {  
            update(node * 2 + 1, m + 1, r, i, val);
        }
        maintain(node);
    }

    T query(int node, int l, int r, int ql, int qr) const {
        if (ql <= l && r <= qr) { 
            return tree[node];
        }
        int m = (l + r) / 2;
        if (qr <= m) { 
            return query(node * 2, l, m, ql, qr);
        }
        if (ql > m) { 
            return query(node * 2 + 1, m + 1, r, ql, qr);
        }
        T l_res = query(node * 2, l, m, ql, qr);
        T r_res = query(node * 2 + 1, m + 1, r, ql, qr);
        return merge_val(l_res, r_res);
    }

public:
    SegmentTree(const vector<int>& a, int k) : n(a.size()),k(k), tree(2 << bit_width(a.size() - 1)) {
        build(a, 1, 0, n - 1);
    }

    void update(int i, int val) {
        update(1, 0, n - 1, i, val);
    }

    T query(int ql, int qr) const {
        return query(1, 0, n - 1, ql, qr);
    }
    T get(int i) const {
        return query(1, 0, n - 1, i, i);
    }
};

class Solution {
public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {        
        int n = nums.size(), m = queries.size();
        SegmentTree t(nums, k);
        vector<int> ans;
        for (int i = 0; i < m; i++) {
            int idx = queries[i][0], val = queries[i][1], start = queries[i][2], x = queries[i][3];
            t.update(idx, val);
            auto [_,cnt] = t.query(start, n - 1);
            ans.emplace_back(cnt[x]);
        }
        return ans;
    }
};
