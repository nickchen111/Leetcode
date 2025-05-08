// BIT: TC:O((n + m) lgh + nlgn + mlgm) SC:O(h) Binray Search + Map: TC:O(mhlgn + mlgm + nlgn) SC:O(n + h)
template<typename T>
class FenwickTree {
    vector<T> tree;
public:
    // 使用下標 1 到 n
    FenwickTree(int n) : tree(n + 1) {}

    // a[i] 增加 val
    // 1 <= i <= n
    // 時間複雜度 O(log n)
    void update(int i, T val) {
        for (; i < tree.size(); i += i & -i) {
            tree[i] += val;
        }
    }

    // 求前缀和 a[1] + ... + a[i]
    // 1 <= i <= n
    // 時間複雜度 O(log n)
    T pre(int i) const {
        T res = 0;
        for (; i > 0; i &= i - 1) {
            res += tree[i];
        }
        return res;
    }

    // 求區間和 a[l] + ... + a[r]
    // 1 <= l <= r <= n
    // 時間複雜度 O(log n)
    T query(int l, int r) const {
        if (r < l) {
            return 0;
        }
        return pre(r) - pre(l - 1);
    }
};
class Solution {
public:
    vector<int> countRectangles(vector<vector<int>>& rectangles, vector<vector<int>>& points) {
        /*
        問說一堆矩形 每個點被多少個矩形包圍著
        n = 5 * 1e4
        方法1:
        對矩形與點排序按照寬, 邊走邊看哪些點寬小於當前矩形寬就去掉 然後把高加入隊列，之後會對這個隊列做二分判斷有多少元素在裡面
        python 就是用sortedlist, c++認命BIT
        方法2:
        二分 + 利用題目給的高只有100限制
        */
        int n = rectangles.size(), m = points.size();
        // BIT for 高度 兩者皆排序
        ranges::sort(rectangles);
        vector<array<int,3>> points_idx;
        for (int i = 0; i < m; i++) points_idx.push_back({points[i][0], points[i][1], i});
        ranges::sort(points_idx);
        FenwickTree<int> bit(100); // 高度最多100
        for (int i = 0; i < n; i++) {
            bit.update(rectangles[i][1], 1); // 該高度+1
        }
        int p1 = 0, p2 = 0;
        vector<int> ans(m);
        while (p1 < m) {
            // 將寬度不符合標準的矩形去掉
            int pl = points_idx[p1][0], ph = points_idx[p1][1], idx = points_idx[p1][2];
            while (p2 < n && pl > rectangles[p2][0]) {
                bit.update(rectangles[p2][1], -1);
                p2 += 1;
            }
            ans[idx] = bit.pre(100) - bit.pre(ph-1);
            p1 += 1;
        }
        return ans;

        /*
        unordered_map<int, vector<int>> mp;
        unordered_set<int> st;
        for (int i = 0; i < n; i++) {
            mp[rectangles[i][1]].emplace_back(rectangles[i][0]);
            st.insert(rectangles[i][1]); // 只有這些高度
        }
        for(auto &p: mp) {
            ranges::sort(p.second);
        }
        vector<int> ans(m);
        for (int i = 0; i < m; i++) {
            int l = points[i][0], h = points[i][1];
            for (auto &rh : st) {
                if (rh >= h) {
                    ans[i] += (int)mp[rh].size() - (ranges::lower_bound(mp[rh], l) - mp[rh].begin());
                }
            }
        }
        return ans;
        */
    }
};
