// TC:O(n * lgn) SC:O(n)
template<typename T>
class FenwickTree {
    vector<T> tree;
public:
    FenwickTree(int n) : tree(n + 1) {}
    // 更新範圍的區間數量 增量去走
    void update (int i, T x) {
        for (; i < tree.size(); i += i & -i) {
            tree[i] += x;
        }
    }
    T pre (int i) {
        T ans = 0;
        while (i > 0) {
            ans += tree[i];
            i &= i-1;
        }
        return ans;
    }
};
class Solution {
    using ll = long long;
public:
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        /*
        題意: 計算長度3的nums1 nums2公共子序列有多少個
        但是LCS 通常會是n^2
        要想說LCS有什麼性質可以搞成LIS
        這題數字範圍固定0 ~ n - 1 可以發現因為都是獨特元素，所以可以轉成index去存就變成index
        可以從LCS 轉成LIS
        再來就是要想怎麼計算有多少個長度為3的IS, 不能用貪心+二分 他是拿來算LIS
        三個 -> 想到前後綴分解 枚舉其中一個然後去找有多少個比她小，右邊有多少個比他大，排序會想到用OrderSet 但是這題要找出數量 所以multiset不適合
        因為需要有排序 並且會做區間更新(少掉一個數字對維護的區間都有影響) 以及單點查詢(只需要知道小於某個值的數字有多少個)
        所以可以用BIT
        */

        // 創建index數組 以nums1為基準
        int n = nums1.size();
        vector<int> arr(n); // index數組
        for (int i = 0; i < n; i++) {
            arr[nums1[i]] = i;
        }
        // 創建BIT數組 用物件吧
        FenwickTree<ll> t(n + 1);
        // FenwickTree<ll> right (n + 1);
        ll ans = 0;
        for (int i = 0; i < n - 1; i++) {
            // left.update(arr[i-1] + 1, 1); // 代表那個index之後都 + 1, 因為是1 index 所以+1
            // right.update(arr[i] + 1, -1);
            ll y = arr[nums2[i]];
            ll less = t.pre(y); 
            ans = ans + less * (n - 1 - y - (i - less)); // 這裡根據乘法原理去選 right應該是要選比他大的, 比y小的有less個 代表有 i - less個比y大 n - (i - less) - y 就是右邊比他大的數量  or ans = ans + left.pre(arr[i] + 1) * (right.pre(n) - right.pre(arr[i] + 1));
            t.update(y+1, 1);
        } 
        return ans;
    }
};


// 模擬python 的 sortlist 分塊技術 做到n * sqrt(n) 此題會超時
class BlockSortedList {
private:
    static const long long BLOCK_SIZE = 100;  // 每塊大小（可調）
    vector<vector<long long>> blocks;         // 每塊是一個排序的 vector
    int size = 0;

    void rebuild() {
        // 將所有元素拉平，重新分塊
        vector<long long> all;
        for (auto& block : blocks) {
            all.insert(all.end(), block.begin(), block.end());
        }
        blocks.clear();
        for (int i = 0; i < (int)all.size(); i += BLOCK_SIZE) {
            int end = min((long long)i + BLOCK_SIZE, (long long)all.size());
            blocks.emplace_back(all.begin() + i, all.begin() + end);
        }
    }

public:
    void add(int x) {
        for (auto& block : blocks) {
            if (block.empty() || x <= block.back()) {
                auto it = lower_bound(block.begin(), block.end(), x);
                block.insert(it, x);
                size++;
                if ((long long)block.size() > 2 * BLOCK_SIZE) {
                    rebuild(); // 平衡塊數
                }
                return;
            }
        }
        // 沒插入成功 => 插入最後一塊或新建
        if (blocks.empty() || !blocks.back().empty()) {
            blocks.emplace_back();
        }
        blocks.back().push_back(x);
        size++;
    }

    void discard(int x) {
        for (auto& block : blocks) {
            auto it = lower_bound(block.begin(), block.end(), x);
            if (it != block.end() && *it == x) {
                block.erase(it);
                size--;
                if ((int)block.size() < BLOCK_SIZE / 2) {
                    rebuild(); // 平衡塊數
                }
                return;
            }
        }
    }

    long long bisect_left(int x) {
        long long idx = 0;
        for (auto& block : blocks) {
            if (block.empty() || block.back() < x) {
                idx += block.size();
            } else {
                return idx + lower_bound(block.begin(), block.end(), x) - block.begin();
            }
        }
        return idx;
    }

    long long bisect_right(int x) {
        long long idx = 0;
        for (auto& block : blocks) {
            if (block.empty() || block.back() <= x) {
                idx += block.size();
            } else {
                return idx + upper_bound(block.begin(), block.end(), x) - block.begin();
            }
        }
        return idx;
    }

    long long get_size() const {
        return size;
    }

    void print() const {
        for (auto& block : blocks) {
            for (int x : block) {
                cout << x << " ";
            }
        }
        cout << endl;
    }
};
class Solution {
public:
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> idx(n);
        for (int i = 0; i < n; i++) {
            idx[nums2[i]] = i;
        }
        BlockSortedList left;
        left.add(idx[nums1[0]]);
        BlockSortedList right;
        for (int i = 1; i < n; i++) {
            right.add(idx[nums1[i]]);
        }

        long long ans = 0;
        for (int i = 1; i < n; i++) {
            long long x = idx[nums1[i]];
            right.discard(x);
            long long left_count = left.bisect_left(x);
            long long right_count = n - i - 1 - right.bisect_right(x);
            ans += left_count * right_count;
            left.add(x);
        } 
        return ans;
    }
};
