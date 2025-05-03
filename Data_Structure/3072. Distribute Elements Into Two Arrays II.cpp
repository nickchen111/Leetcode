// TC:O(n * (lgm + lgn)) SC:O(n)
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

class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        /*
        有一個Function會去計算某個數字丟進去某個資料結構中大於該數字的數字量有多少個
        第一次先丟arr1, 第二次丟arr2 之後就按照規則看哪個經過function後數字量多丟哪個
        如果相等丟arr1
        最後就是問arr1 + arr2 會是啥？
        兩種想法
        1. 用類似orderset的方式去做, python可以用SortedList 應該更快 底層感覺是bucket sort 但是效率很好
        2. 樹狀數組離散化
        */

        // 首先需要針對數字去重 然後做離散化
        vector<int> b = nums;
        sort(b.begin(), b.end());
        b.erase(unique(b.begin(), b.end()), b.end());
        int m = b.size();
        FenwickTree<int> arr1(m), arr2(m);
        int n = nums.size();
        vector<int> ans1{nums[0]}, ans2{nums[1]};
        arr1.update(ranges::lower_bound(b, nums[0]) - b.begin() + 1, 1);
        arr2.update(ranges::lower_bound(b, nums[1]) - b.begin() + 1, 1);
        for (int i = 2; i < n; i++) {
            // 當前index
            int idx = ranges::lower_bound(b, nums[i]) - b.begin() + 1;
            int l1 = arr1.pre(m);
            int l2 = arr2.pre(m);
            int cnt1 = l1 - arr1.pre(idx);
            int cnt2 = l2 - arr2.pre(idx);
            if (cnt1 > cnt2 || cnt1 == cnt2 && l1 <= l2) {
                ans1.emplace_back(nums[i]);
                arr1.update(idx, 1);
            }
            else {
                ans2.emplace_back(nums[i]);
                arr2.update(idx, 1);
            }
        }
        ans1.insert(ans1.end(), ans2.begin(), ans2.end());
        return ans1;
    }
};
