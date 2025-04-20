// TC:O(nlgn) SC:O(n)
class SegmentTree {
    vector<int> mx;
    void maintain(int o) {
        mx[o] = max(mx[o * 2], mx[o*2 + 1]);
    }
    void build(const vector<int>& a, int o, int l, int r) {
        if (l == r) {
            mx[o] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(a, o * 2, l, m);
        build(a, o * 2 + 1, m+1, r);
        maintain(o);
    }
public:
    SegmentTree(vector<int>& a) {
        int n = a.size();
        mx.resize(4 * n); // mx.resize(2 << bit_width((unsigned) (n - 1)));
        build(a, 1, 0, n-1);
    }
    int findFirstAndUpdate(int o, int l, int r, int x) {
        if (mx[o] < x) return -1;
        if(l == r) {
            mx[o] = -1; // 單點更新
            return l;
        }
        int m = (l + r) / 2;
        int i = findFirstAndUpdate(o * 2, l, m, x);
        if (i < 0) {
            i = findFirstAndUpdate(o * 2 + 1, m + 1, r, x);
        }
        maintain(o);
        return i;
    }
};

class Solution {
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        SegmentTree t(baskets);
        int ans = 0, n = fruits.size();
        for(auto &x : fruits) {
            if (t.findFirstAndUpdate(1, 0, n-1, x) < 0) {
                ans += 1;
            }
        }
        return ans;
    }
};
