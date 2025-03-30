template<typename T, typename Compare = less<T>>
class LazyHeap {
    priority_queue<T, vector<T>, Compare> pq;
    unordered_map<T, int> remove_cnt; // 每個元素剩餘需要删除的次數
    size_t sz = 0; // 實際大小

    // 正式執行删除操作
    void apply_remove() {
        while (!pq.empty() && remove_cnt[pq.top()] > 0) {
            remove_cnt[pq.top()]--;
            pq.pop();
        }
    }

public:
    size_t size() {
        return sz;
    }

    // 删除
    void remove(T x) {
        remove_cnt[x]++; // 懒删除
        sz--;
    }

    // 查看堆顶
    T top() {
        apply_remove();
        return pq.top();
    }

    // 出堆
    T pop() {
        apply_remove();
        sz--;
        T x = pq.top();
        pq.pop();
        return x;
    }

    // 入堆
    void push(T x) {
        if (remove_cnt[x] > 0) {
            remove_cnt[x]--; // 抵消之前的删除
        } else {
            pq.push(x);
        }
        sz++;
    }

    // push(x) 然後 pop()
    T push_pop(T x) {
        apply_remove();
        pq.push(x);
        x = pq.top();
        pq.pop();
        return x;
    }
};
