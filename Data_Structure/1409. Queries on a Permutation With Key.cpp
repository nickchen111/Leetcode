// TC:O((n + q) * lgn) SC:O(n)
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
    vector<int> processQueries(vector<int>& queries, int m) {
        /*
        每次去找某個數字在資料結構中的位置，然後將該數字移到第一項
        問說每次找的數字的位置array
        涉及到數字的搜尋與更新位置 慢一點做這些事情就是 O(n)
        是否可以lgn做到?
        思考用index or 數字本身當作BIT節點
        要知道某個數字的index 只需要知道他前面有幾個數字即可
        所以應該是用數字本身當作節點
        後來被數字轉移卡住，我一個數字轉移還是需要針對前面所有數字+1 並且不知道該節點要怎麼按照樹狀樹組表達方式移到前面
        看了題解，大概含義是想像正常生活中排隊，要把人抓到前頭，我們只需要移動一人即可，因為他前面還有很多空間
        這給我們的啟發就是預留前面空間
        */
        int n = queries.size();
        FenwickTree<int> bit(m + n);
        vector<int> pos(m + 1);
        for (int i = 1; i <= m; i++) {
            pos[i] = i + n;
            bit.update(i + n, 1);
        }
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            int &cur = pos[queries[i]];
            bit.update(cur, -1);//移除
            ans.emplace_back(bit.pre(cur));
            cur = n - i;
            bit.update(cur, 1);
        }
        return ans;

    }
};
