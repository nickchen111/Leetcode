// TC: O(nlgn) SC:O(n)
template<typename T, typename Compare = less<T>>
class LazyHeap {
    priority_queue<T, vector<T>, Compare> pq;
    unordered_map<T, int> remove_cnt;
    size_t sz = 0;
    void apply_remove() {
        while(!pq.empty() && remove_cnt[pq.top()] > 0) {
            remove_cnt[pq.top()] -= 1;
            pq.pop();
        }
    }
public:
    size_t size() {
        return sz;
    }
    void remove(T x) {
        remove_cnt[x] += 1;
        sz -= 1;
    }
    void push(T x) {
        if (remove_cnt[x] > 1) {
            remove_cnt[x] -= 1;
            
        }
        else pq.emplace(x);
        sz += 1;
    }
    T pop() {
        apply_remove();
        T x = pq.top();
        pq.pop();
        sz -= 1;
        return x;
    }
    T top() {
        apply_remove();
        return pq.top();
    }
    T push_pop(T x) {
        apply_remove();
        pq.push(x);
        x = pq.top();
        pq.pop();
        return x;
    }
};
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<double> ans(n - k + 1);
        LazyHeap<int> left;
        LazyHeap<int, greater<int>> right;
        for(int i = 0; i < n; i++) {
            // 進入窗口
            int in = nums[i];
            if(left.size() == right.size()) {
                left.push(right.push_pop(in));
            }
            else {
                right.push(left.push_pop(in));
            }
            int l = i + 1 - k;
            if (l < 0) continue;
            
            if (k % 2) {
                ans[l] = left.top();
            }
            else ans[l] = ((long long) left.top() + right.top()) / 2.0;

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
};
