// TC:O(n + qlgn) SC:O(n)
class Solution {
    long long MOD = 1e9 + 7;
    vector<array<long long, 4>> t;
    // f00, f01, f10, f11 來定義打家劫舍分治的限制 第一個數字代表頭可取不可取 第二個代表尾
    // 需要 update, maintain, build
    void maintain(int o) { // 更新陣列狀況
        auto &a = t[o * 2];
        auto &b = t[o * 2 + 1];
        t[o] = {
            max(a[0] + b[2], a[1] + b[0]),
            max(a[0] + b[3], a[1] + b[1]),
            max(a[2] + b[2], a[3] + b[0]),
            max(a[2] + b[3], a[3] + b[1]),
        };
    }
    void build(vector<int>& nums, int o, int l, int r) {
        if(l == r) {
            t[o][3] = max(nums[l], 0);
            return;
        }
        int m = (l + r) / 2;
        build(nums, o * 2, l, m);
        build(nums, o * 2 + 1, m + 1, r);
        maintain(o);
    }
    void update(int o, int l, int r, int val, int i) {
        if (l == r) {
            t[o][3] = max(val, 0);
            return;
        }
        int m = (l + r) / 2;
        if (i <= m) {
            update(o * 2, l, m, val, i);
        }
        else {
            update(o * 2 + 1, m + 1, r, val, i);
        }
        maintain(o);
    }
public:
    int maximumSumSubsequence(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), m = queries.size();
        long long ans = 0;
        t.resize(4 * n);
        build(nums, 1, 0, n - 1);
        for(int i = 0; i < m; i++) {
            update(1, 0, n-1, queries[i][1], queries[i][0]);
            ans += t[1][3];
        }
        return ans % MOD;
    }
};
