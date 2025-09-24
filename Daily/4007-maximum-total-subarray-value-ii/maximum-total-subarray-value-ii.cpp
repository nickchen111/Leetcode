struct Node {
    int mx, mn;
};

class SegmentTree {
    int n;
    vector<Node> tree;

    Node merge_val(const Node& a, const Node& b) const {
        return {max(a.mx, b.mx), min(a.mn, b.mn)};
    }

    void maintain(int node) {
        tree[node] = merge_val(tree[node*2], tree[node*2+1]);
    }

    void build(const vector<int>& a, int node, int l, int r) {
        if (l == r) {
            tree[node] = {a[l], a[l]};
            return;
        }
        int m = (l + r) / 2;
        build(a, node*2, l, m);
        build(a, node*2+1, m+1, r);
        maintain(node);
    }

    Node query(int node, int l, int r, int ql, int qr) const {
        if (ql <= l && r <= qr) return tree[node];
        int m = (l + r) / 2;
        if (qr <= m) return query(node*2, l, m, ql, qr);
        if (ql > m) return query(node*2+1, m+1, r, ql, qr);
        Node left = query(node*2, l, m, ql, qr);
        Node right = query(node*2+1, m+1, r, ql, qr);
        return merge_val(left, right);
    }

public:
    SegmentTree(const vector<int>& a) : n(a.size()), tree(4*a.size()) {
        build(a, 1, 0, n-1);
    }

    Node query(int l, int r) const {
        return query(1, 0, n-1, l, r);
    }
};

class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        int n = nums.size();
        SegmentTree st(nums);

        // 優先隊列存 {最大值, 左邊界, 右邊界}
        priority_queue<tuple<int,int,int>> pq;
        for (int i = 0; i < n; i++) {
            auto node = st.query(i, n-1);
            pq.emplace(node.mx - node.mn, i, n-1);
        }

        long long ans = 0;
        while (k-- && !pq.empty() && get<0>(pq.top()) > 0) {
            auto [d, l, r] = pq.top();
            pq.pop();
            ans += d;
            // cout << d << endl;
            if (l <= r-1) {
                auto node = st.query(l, r-1);
                pq.emplace(node.mx - node.mn, l, r-1);
            }
        }
        return ans;
    }
};
