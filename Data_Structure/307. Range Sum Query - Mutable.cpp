// TC:O(lgn) SC:O(n)
template<typename T>
class FenWickTree {
    vector<T> tree;
public:
    FenWickTree(int n) : tree(n + 1) {}
    void update(int i, T v) {
        // update 就是往上增加
        while (i < tree.size()) {
            tree[i] += v;
            i += i & -i;
        }
    }
    T pre(int i) {
        T ans = 0;
        while (i > 0) {
            ans += tree[i];
            i -= i & -i; // i &= (i-1)
        }
        return ans;
    }
    T query (int l, int r) {
        return pre(r + 1) - pre(l);
    }
};
class NumArray {
    FenWickTree<int> t;
    vector<int> arr;
public:
    NumArray(vector<int>& nums) : t(nums.size()), arr(nums) {
        for (int i = 0; i < nums.size(); i++) {
            t.update(i + 1, nums[i]);
        }
    }
    
    void update(int index, int val) {
        int diff = val - arr[index];
        arr[index] = val;
        t.update(index + 1, diff);
    }
    
    int sumRange(int left, int right) {
        return t.query(left, right);
    }
};
