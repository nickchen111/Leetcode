// Stack TC:O(n) SC:O(1)
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        // stack<int> stack;
        int top = -1;
        int ans = 0;
        // 原地修改
        for (int i = 0; i < n; i++) {
            while(top >= 0 && nums[top] > nums[i]) {
                top -= 1;
                ans += 1;
            }
            if ((top < 0 || nums[i] > nums[top]) && nums[i] != 0) {
                top += 1;
                nums[top] = nums[i];
            }
        }
        return ans + top + 1;
        /*
        for (int i = 0; i < n; i++) {
            while(!stack.empty() && stack.top() > nums[i]) {
                stack.pop();
                ans += 1;
            }
            if ((stack.empty() || nums[i] > stack.top()) && nums[i] != 0) {
                stack.push(nums[i]);
            }
        }
        return ans + (int)stack.size();
        */
    }
};


// BIT TC:O(nlgn) SC:O(n)
template<typename T>
class FenwickTree {
    vector<T> tree;
public:
    FenwickTree(int n) : tree(n + 1) {}
    
    void update(int i, T val) {
        for (; i < tree.size(); i += i & -i) {
            tree[i] += val;
        }
    }
    T pre(int i) const {
        T res = 0;
        for (; i > 0; i &= i - 1) {
            res += tree[i];
        }
        return res;
    }
    T query(int l, int r) const {
        if (r < l) {
            return 0;
        }
        return pre(r) - pre(l - 1);
    }
};
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        set<int> st;
        unordered_map<int, vector<int>> pos;
        FenwickTree<int> bit(n);
        for (int i = 0; i < n; i++) {
            if (nums[i] > 0) {
                pos[nums[i]].push_back(i);
                st.insert(nums[i]);
            }
            else bit.update(i + 1, 1);
        }
        int ans = 0;
        for (auto &i : st) {
            int last_pos = -1, segments = 0;
            for (int &p : pos[i]) {
                if (last_pos == -1) {
                    last_pos = p;
                    segments += 1;
                }
                else {
                    if (bit.query(last_pos + 2, p) > 0) {
                        segments += 1;
                    }
                }
                last_pos = p;
            }
            ans += segments;
            for (int &p : pos[i]) {
                bit.update(p + 1, 1);
            }
        }
        return ans;
    }
};

// Hash Map + Sort + 二分
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, vector<int>> pos;
        for (int i = 0; i < n; i++) {
            pos[nums[i]].push_back(i); // 每個數字有哪些位置
        }
        vector<int> vals;
        for (auto &kv : pos) {
            vals.push_back(kv.first);
        }
        sort(vals.begin(), vals.end());
        
        int ans = 0;
        set<int> deleted;
    
        for (int v : vals) {
            auto &vec = pos[v];
            if (v == 0) {
                for (int idx : vec) deleted.insert(idx);
                continue;
            }
            int segments = vec.empty() ? 0 : 1;
            for (int k = 1; k < (int)vec.size(); k++) {
                int p = vec[k-1], q = vec[k];
                auto it = deleted.lower_bound(p + 1);
                if (it != deleted.end() && *it < q) {
                    segments++;
                }
            }
            ans += segments;
            for (int idx : vec) {
                deleted.insert(idx);
            }
        }
        
        return (int)ans;
    }
};
