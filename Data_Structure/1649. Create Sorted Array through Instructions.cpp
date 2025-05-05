// BIT TC:O(nlgn) SC:O(n)
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
    using ll = long long;
    ll MOD = 1e9 + 7;
public:
    int createSortedArray(vector<int>& instructions) {
        /*
        方法1:
        這題很明顯可以用BIT做 因為需要每次插入一個數字就去判斷比她大的數字有多少個以及比他小的
        然後取最小的當作cost 問說最後cost多少
        方法2:
        如果是python 還可以用sortedList做
        方法3:
        Divide and Conquer 分治法 把一個大的東西拆解成小問題
        */
        int n = instructions.size();
        // 這題要將數字做BIT
        int mx = *max_element(instructions.begin(), instructions.end());
        FenwickTree<int> bit(mx);
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            int val = instructions[i];
            int sm = bit.pre(val - 1); // 小的
            int lg = bit.pre(mx) - bit.pre(val); // 大的
            ans = (ans + (ll) min(sm, lg)) % MOD;
            bit.update(val, 1);
        }
        return ans;
    }
};

// Divdie and Conquer + Binary Search TC:O(nlgnlgn) SC:O(n)
class Solution {
    using ll = long long;
    ll MOD = 1e9 + 7;
public:
    int createSortedArray(vector<int>& instructions) {
        /*
        方法1:
        這題很明顯可以用BIT做 因為需要每次插入一個數字就去判斷比她大的數字有多少個以及比他小的
        然後取最小的當作cost 問說最後cost多少
        方法2:
        如果是python 還可以用sortedList做
        方法3:
        Divide and Conquer 分治法 把一個大的東西拆解成小問題
        想法目前是走到一個divide 過程 判斷一下在這個index比他小的有序的數組中 去做二分 可以判斷出哪些比他小
        決定完以後繼續conquer 將前面兩段merge起來
        */
        int n = instructions.size();
        vector<int> sorted = instructions;
        vector<ll> cost(n);
        auto DivideAndConquer = [&](this auto &&DivideAndConquer, int l, int r) -> void {
            if (l >= r) {
                return;
            }
            int m = l + ((r - l) >> 1);
            DivideAndConquer(l, m);
            DivideAndConquer(m + 1, r);
            // 將前一個array做二分
            for (int i = m + 1; i <= r; i++) {
                int val = instructions[i];
                auto iter = lower_bound(sorted.begin() + l, sorted.begin() + m + 1, val);
                cost[i] += iter - (sorted.begin() + l);
            }
            inplace_merge(sorted.begin() + l, sorted.begin() + m + 1, sorted.begin() + r + 1);
        };
        DivideAndConquer(0, n - 1);
        ll ans = 0;
        unordered_map<int, ll> cnt;
        for (int i = 0; i < n; i++) {
            ans = ans + (ll) min(cost[i], i - cost[i] - cnt[instructions[i]]);
            ans %= MOD;
            cnt[instructions[i]] += 1;
        }
        return ans;
    }
};
