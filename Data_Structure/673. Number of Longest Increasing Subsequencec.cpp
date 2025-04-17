// TC:O(n * (lgm + lgn) ) SC:O(m) m 為去重後的數量
using PII = pair<int,int>;
template<typename T>
class FenwickTree {
    vector<T> tree;
public:
    FenwickTree(int n, T init = T{}) : tree(n + 1, init) {}
    T merge(const T& a, const T& b) {
        if (a.first > b.first) return a;
        else if (a.first < b.first) return b;
        return {a.first, a.second + b.second};
    }
    void update(int i, T val) {
        for (; i < tree.size(); i += i & -i) {
            tree[i] = merge(tree[i], val);
        }
    }
    T pre (int i) {
        T ans = T{};
        while (i > 0) {
            if (tree[i].first > ans.first) {
                ans = tree[i];
            }
            else if (tree[i].first == ans.first) {
                ans.second += tree[i].second;
            }
            i &= i - 1;
        }
        return ans;
    }
};

class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();
        auto b = nums;
        sort(b.begin(), b.end());
        b.erase(unique(b.begin(), b.end()), b.end());
        int m = b.size();
        FenwickTree<PII> t(m);
        auto getIdx = [&](int x) -> int {
            return ranges::lower_bound(b, x) - b.begin() + 1; // 1 - index 
        };
        int mxLen = 0, ans = 0;
        for (int i = 0; i < n; i++) {
            int idx = getIdx(nums[i]);
            auto [curLen, curCnt] = t.pre(idx - 1);
            if (curLen == 0) curCnt = 1; // 當下這個點的長度
            PII cur = {curLen + 1, curCnt};
            if (cur.first > mxLen) {
                mxLen = curLen + 1;
                ans = cur.second;
            }
            else if (cur.first == mxLen) {
                ans += cur.second;
            }
            t.update(idx, cur);
        }
        return ans;
    }
};
