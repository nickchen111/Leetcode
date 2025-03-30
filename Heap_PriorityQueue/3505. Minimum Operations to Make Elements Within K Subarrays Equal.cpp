// TC:O(nlgn + n * (n-kx)) SC:O(n)
using ll = long long;
template<typename T, typename Compare = less<T>>
class LazyHeap {
    priority_queue<T, vector<T>, Compare> pq;
    unordered_map<T, int> remove_cnt;
    T s = 0; // 元素總和
    size_t sz = 0;
    void apply_remove() {
        while(!pq.empty() && remove_cnt[pq.top()] > 0) {
            remove_cnt[pq.top()] -= 1;
            pq.pop();
        }
    }
public:
    ll sum() {
        return s;
    }
    size_t size() {
        return sz;
    }
    void remove(T x) {
        remove_cnt[x] += 1;
        sz -= 1;
        s -= x;
    }
    void push(T x) {
        if (remove_cnt[x] > 1) {
            remove_cnt[x] -= 1;
        }
        else pq.emplace(x);
        s += x;
        sz += 1;
    }
    T pop() {
        apply_remove();
        T x = pq.top();
        pq.pop();
        sz -= 1;
        s -= x;
        return x;
    }
    T top() {
        apply_remove();
        return pq.top();
    }
    T push_pop(T x) {
        apply_remove();
        pq.push(x);
        s += x;
        x = pq.top();
        s -= x;
        pq.pop();
        return x;
    }
};

class Solution {
    vector<ll> medianSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<ll> ans(n - k + 1);
        LazyHeap<ll> left;
        LazyHeap<ll, greater<ll>> right;
        for(int i = 0; i < n; i++) {
            // 進入窗口
            ll in = nums[i];
            if(left.size() == right.size()) {
                left.push(right.push_pop(in));
            }
            else {
                right.push(left.push_pop(in));
            }
            int l = i + 1 - k;
            if (l < 0) continue;
            // 開始計算 也就是 左邊的元素 sz / 2 下取整 右邊元素有 sz/2 同樣下取整
            
            ans[l] = (left.size() * left.top() - left.sum()) + (right.sum() - right.size() * left.top());
           
            // 出窗口
            int out = nums[l];
            if(out <= left.top()) {
                left.remove(out);
                if(left.size() < right.size()) {
                    left.push(right.pop());
                }
            }
            else {
                right.remove(out);
                if (right.size() + 1 < left.size()) {
                    right.push(left.pop());
                }
            }
        }
        return ans;
    }
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        /*
        至少選k個不重疊區間，每個區間x長度 讓他們的數字都要相等所需操作+-1的最少次數
        1. 首先每個區間需要的操作次數會可以藉由中位數定理與懶刪除推維護後在O(1)求出
        2. 選擇k個不重疊區間選完所有數組內數字則是由劃分型DP 約束劃分個數的作法可以求出
        */
        int n = nums.size();
        vector<ll> dis = medianSlidingWindow(nums, x);
        vector dp(k+1, vector<ll>(n+1));
        for(int i = 1; i <= k; i++) {
            dp[i][i * x - 1] = LLONG_MAX/2;
            for(int j = i * x; j <= n - (k - i) * x; j++) {//後面需要保留 假設x = 2, k = 3, i = 1 -> 2 * 2個數字 總共假設 6個 只能走到2
                dp[i][j] = min(dp[i][j-1], dp[i-1][j-x] + dis[j - x]);
            }
        }
        return dp[k][n];
    }
};
