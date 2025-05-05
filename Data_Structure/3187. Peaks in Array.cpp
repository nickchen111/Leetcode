// TC:O((n + q) log n) SC:O(n)
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
    vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) {
        /*
        問說按照query順序 每當queries[i][0] = 1 時判斷出他給出的區間有多少個peak
        queries[i][0] = 2 時要去更改array的某個index
        問說按照queries[i][0] = 1 的每個順序有多少個peak
        很明BIT, 因為是問說一段區間內的總和 所以可以用BIT維護
        */
        int n = nums.size();
        // 按照index 去設計BIT
        FenwickTree<int> bit(n);
        for (int i = 1; i < n - 1; i++) {
            if(nums[i] > nums[i - 1] && nums[i] > nums[i + 1]) {
                bit.update(i, 1); //當前位置增加1
            }
        }

        vector<int> ans;
        for (auto &q : queries) {
            if (q[0] == 1) {
                int l = q[1], r = q[2];
                ans.emplace_back(bit.query(l + 1, r - 1));
            } else {
                int idx = q[1], val = q[2];
                if (idx - 1 >= 0 && idx + 1 < n) {
                    if (nums[idx + 1] < nums[idx] && nums[idx - 1] < nums[idx])
                        bit.update(idx, -1);
                    if (nums[idx + 1] < val && nums[idx - 1] < val)
                        bit.update(idx, 1);
                }
                // 判斷他左右的狀況
                if (idx - 2 >= 0) {
                    if (nums[idx - 2] < nums[idx - 1] && nums[idx - 1] > nums[idx])
                        bit.update(idx - 1, -1);
                    if (nums[idx - 2] < nums[idx - 1] && nums[idx - 1] > val)
                        bit.update(idx - 1, 1);
                }
                
                if (idx + 2 < n) {
                    if (nums[idx + 2] < nums[idx + 1] && nums[idx + 1] > nums[idx])
                        bit.update(idx + 1, -1);
                    if (nums[idx + 2] < nums[idx + 1] && nums[idx + 1] > val)
                        bit.update(idx + 1, 1);
                }
                nums[idx] = val;
            }
        }
        return ans;
    }
};
