template<typename T>
class SparseTable {
    vector<vector<int>> st_min;
    vector<vector<int>> st_max;
public:
    // 創建表的build function
    SparseTable (vector<T>& a) {
        size_t n = a.size();
        int sz = bit_width(unsigned(n));
        st_min.resize(n, vector<int>(sz));
        st_max.resize(n, vector<int>(sz));
        // 走2^0步的時候所有點兩個區間加總
        for (int i = 0; i < n; i++) {
            st_min[i][0] = a[i];
            st_max[i][0] = a[i];
        }
        for(int j = 1; j < sz; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st_min[i][j] = min(st_min[i][j-1], st_min[i + (1 << (j - 1))][j-1]); // 改成題目要做的事情
                st_max[i][j] = max(st_max[i][j-1], st_max[i + (1 << (j - 1))][j-1]);
            }
        }
    }
    int query(int l, int r) const { // 左閉右開 查詢完整區間的最大值 只有一個區間不算
        if (l >= r) return 0;
        int k = bit_width((uint32_t) r - l) - 1;
        int mx = max(st_max[l][k], st_max[r - (1 << k)][k]);
        int mn = min(st_min[l][k], st_min[r - (1 << k)][k]);
        return mx - mn;
    }
};


class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        int n = nums.size();
        SparseTable st(nums);
        priority_queue<tuple<int,int,int>> pq;
        for (int i = 0; i < n; i++) {
            pq.emplace(st.query(i, n), i, n);
        }

        long long ans = 0;
        while (k-- && get<0>(pq.top())) {
            auto [d, l, r] = pq.top();
            pq.pop();
            ans += d;
            pq.emplace(st.query(l, r - 1), l, r - 1);
        }

        return ans;
    }
};