// 模板
template<typename T>
class FenwickTree {
    vector<T> tree;
public:
    // 使用下標 1 到 n
    FenwickTree(int n) : tree(n + 1) {}

    // a[i] 增加 val
    // 1 <= i <= n
    // 时间複雜度 O(log n)
    void update(int i, T val) {
        for (; i < tree.size(); i += i & -i) {
            tree[i] += val;
        }
    }

    // 求前缀和 a[1] + ... + a[i]
    // 1 <= i <= n
    // 时间複雜度 O(log n)
    T pre(int i) const {
        T res = 0;
        for (; i > 0; i &= i - 1) {
            res += tree[i];
        }
        return res;
    }

    // 求區间和 a[l] + ... + a[r]
    // 1 <= l <= r <= n
    // 时间複雜度 O(log n)
    T query(int l, int r) const {
        if (r < l) {
            return 0;
        }
        return pre(r) - pre(l - 1);
    }
};

// 附上離散化的方式 需配合sort去重 對應index + 二分
class BIT {
private:
    vector<int> tree;
public:
    BIT (int n) : tree(n) {}
    void add (int x, int val) {
        while (x < tree.size()) {
            tree[x] += val;
            x += x & -x;
        }
    }
    int query (int x) {
        int ans = 0;
        while (x > 0) {
            ans += tree[x];
            x -= x & -x;
        }
        return ans;
    }
};
class Solution {
public:
    long long numberOfPairs(vector<int>& a, vector<int>& nums2, int diff) {
        /*
        1. 樹狀數組  
        2. 歸併排序  
        3. 講怎麼做到 nums[i] <= 1e9

        1. nums1[i] - nums1[j] <= nums2[i] - nums2[j] + diff  
        2. nums1[i] - nums2[i] <= nums1[j] - nums2[j] + diff  
        3. 設 a[i] = nums1[i] - nums2[i]  
        4. a[i] <= a[j] + diff  
        5. 從左到右遍歷 a[i]，統計每個元素的出現次數  
            統計 <= a[i] + diff 的元素個數，就是答案要求的數對個數  
                a[i] 加到統計的資料結構裡面  
        6. 我們需要一個資料結構，能夠添加元素，並查詢 <= x 的元素個數  
        7. 樹狀數組 線段樹 名次樹 Python SortedList

        樹狀數組

        1. 樹狀數組  
        2. 線段樹的想法是，把區間表示成若干區間的並集  
        樹狀數組的想法是，把區間表示成兩個前綴區間的差集  
        前綴區間又可以表示成若干個區間的並集  
        */

        int n = a.size();
        for(int i = 0; i < n; i++) a[i] -= nums2[i];
        vector<int> b = a;
        sort(b.begin(), b.end());
        b.erase(unique(b.begin(), b.end()), b.end());
        int m = b.size();
        // auto t = new BIT(m + 1);
        BIT t(m + 1); // 這裡可以不用寫成 BIT<int> t(m+1) 是因為我套的是已經決定好用int的 而不是第一個模板要帶入資料型別的T
        long long ans = 0L;
        for (auto &x : a) {
            ans += t.query(ranges::upper_bound(b, x + diff) - b.begin());
            t.add(ranges::lower_bound(b, x) - b.begin() + 1, 1);
        }
        return ans;
    }
};
