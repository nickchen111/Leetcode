class LazySegmentTree {
    using T = tuple<long long, long long, int, int>;
    using F = pair<int, int>;

    // 懒标记初始值
    const F TODO_INIT = {-1, -1};

    struct Node {
        T val;
        F todo;
    };

    int n;
    vector<Node> tree;

    // 合并两个 val
    T merge_val(T a, T b) const {
        auto [sum_min_a, sum_max_a, l_min, l_max] = a;
        auto [sum_min_b, sum_max_b, _, _] = b;
        return {sum_min_a + sum_min_b, sum_max_a + sum_max_b, l_min, l_max};
    }

    // 把懒标记作用到 node 子树（本例为区间加）
    void apply(int node, int l, int r, F todo) {
        Node& cur = tree[node];
        // 计算 tree[node] 区间的整体变化
        auto [todo_min, todo_max] = todo;
        auto& [sum_min, sum_max, l_min, l_max] = cur.val;
        auto& [cur_todo_min, cur_todo_max] = cur.todo;
        if (todo_min >= 0) {
            sum_min = 1LL * todo_min * (r - l + 1);
            l_min = todo_min;
            cur_todo_min = todo_min;
        }
        if (todo_max >= 0) {
            sum_max = 1LL * todo_max * (r - l + 1);
            l_max = todo_max;
            cur_todo_max = todo_max;
        }
    }

    // 把当前节点的懒标记下传给左右儿子
    void spread(int node, int l, int r) {
        Node& cur = tree[node];
        F todo = cur.todo;
        if (todo == TODO_INIT) { // 没有需要下传的信息
            return;
        }
        int m = (l + r) / 2;
        apply(node * 2, l, m, todo);
        apply(node * 2 + 1, m + 1, r, todo);
        cur.todo = TODO_INIT; // 下传完毕
    }

    // 合并左右儿子的 val 到当前节点的 val
    void maintain(int node) {
        tree[node].val = merge_val(tree[node * 2].val, tree[node * 2 + 1].val);
    }

    // 用 a 初始化线段树
    // 时间复杂度 O(n)
    void build(int node, int l, int r) {
        Node& cur = tree[node];
        cur.todo = TODO_INIT;
        if (l == r) { // 叶子
            return;
        }
        int m = (l + r) / 2;
        build(node * 2, l, m); // 初始化左子树
        build(node * 2 + 1, m + 1, r); // 初始化右子树
        maintain(node);
    }

    void update(int node, int l, int r, int ql, int qr, F f) {
        if (ql <= l && r <= qr) { // 当前子树完全在 [ql, qr] 内
            apply(node, l, r, f);
            return;
        }
        spread(node, l, r);
        int m = (l + r) / 2;
        if (ql <= m) { // 更新左子树
            update(node * 2, l, m, ql, qr, f);
        }
        if (qr > m) { // 更新右子树
            update(node * 2 + 1, m + 1, r, ql, qr, f);
        }
        maintain(node);
    }

    T query(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) { // 当前子树完全在 [ql, qr] 内
            return tree[node].val;
        }
        spread(node, l, r);
        int m = (l + r) / 2;
        if (qr <= m) { // [ql, qr] 在左子树
            return query(node * 2, l, m, ql, qr);
        }
        if (ql > m) { // [ql, qr] 在右子树
            return query(node * 2 + 1, m + 1, r, ql, qr);
        }
        T l_res = query(node * 2, l, m, ql, qr);
        T r_res = query(node * 2 + 1, m + 1, r, ql, qr);
        return merge_val(l_res, r_res);
    }

    int find_last(int node, int l, int r, int ql, int qr, int low_d) {
        if (l > qr || r < ql || get<3>(tree[node].val) - get<2>(tree[node].val) < low_d) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        spread(node, l, r);
        int m = (l + r) / 2;
        int idx = find_last(node * 2 + 1, m + 1, r, ql, qr, low_d);
        if (idx < 0) {
            idx = find_last(node * 2, l, m, ql, qr, low_d);
        }
        return idx;
    }

public:
    // 线段树维护一个长为 n 的数组（下标从 0 到 n-1）
    LazySegmentTree(int n) : n(n), tree(2 << bit_width((uint32_t) n - 1)) {
        build(1, 0, n - 1);
    }

    // 用 f 更新 [ql, qr] 中的每个 a[i]
    // 0 <= ql <= qr <= n-1
    // 时间复杂度 O(log n)
    void update(int ql, int qr, F f) {
        update(1, 0, n - 1, ql, qr, f);
    }

    // 返回用 merge_val 合并所有 a[i] 的计算结果，其中 i 在闭区间 [ql, qr] 中
    // 0 <= ql <= qr <= n-1
    // 时间复杂度 O(log n)
    T query(int ql, int qr) {
        return query(1, 0, n - 1, ql, qr);
    }

    // 返回 [ql, qr] 内最后一个 sum_max - sum_min >= low_d 的下标
    // 0 <= ql <= qr <= n-1
    // 时间复杂度 O(log n)
    int find_last(int ql, int qr, int low_d) {
        return find_last(1, 0, n - 1, ql, qr, low_d);
    }
};

class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        // 二分 + 滑动窗口 + 单调队列
        // 1438. 绝对差不超过限制的最长连续子数组（改成求子数组个数）
        auto check = [&](int low_d) -> bool {
            deque<int> min_q, max_q;
            int cnt = 0, left = 0;

            for (int i = 0; i < nums.size(); i++) {
                int x = nums[i];

                // 1. 右边入
                while (!min_q.empty() && x <= nums[min_q.back()]) {
                    min_q.pop_back();
                }
                min_q.push_back(i);

                while (!max_q.empty() && x >= nums[max_q.back()]) {
                    max_q.pop_back();
                }
                max_q.push_back(i);

                // 2. 左边出
                while (nums[max_q.front()] - nums[min_q.front()] >= low_d) {
                    left++;
                    if (min_q.front() < left) { // 队首不在窗口中
                        min_q.pop_front();
                    }
                    if (max_q.front() < left) { // 队首不在窗口中
                        max_q.pop_front();
                    }
                }

                cnt += left;
                if (cnt >= k) {
                    return true;
                }
            }
            return false;
        };

        auto [mn, mx] = ranges::minmax(nums);
        int left = 0, right = mx - mn + 1;
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            (check(mid) ? left : right) = mid;
        }
        int low_d = left;

        // 单调栈
        int n = nums.size();
        vector<int> left_less_eq(n), left_great_eq(n);
        stack<int> st1, st2;
        st1.push(-1); // 哨兵
        st2.push(-1);
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            while (st1.size() > 1 && nums[st1.top()] > x) {
                st1.pop();
            }
            left_less_eq[i] = st1.top();
            st1.push(i);

            while (st2.size() > 1 && nums[st2.top()] < x) {
                st2.pop();
            }
            left_great_eq[i] = st2.top();
            st2.push(i);
        }

        // Lazy 线段树
        LazySegmentTree t(n);
        long long cnt = 0, sum = 0;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            t.update(left_less_eq[i] + 1, i, pair(x, -1));
            t.update(left_great_eq[i] + 1, i, pair(-1, x));
            int l = t.find_last(0, i, low_d);
            if (l >= 0) {
                cnt += l + 1;
                auto [sum_min, sum_max, _, _] = t.query(0, l);
                sum += sum_max - sum_min;
            }
        }

        return sum - (cnt - k) * low_d; // 减掉多算的
    }
};
