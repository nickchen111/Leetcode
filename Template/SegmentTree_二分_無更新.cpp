// 這份線段樹模板主要紀錄最值與總和
int n, m;
vector<int> mn;
vector<long long> sum;

// 把下标 i 上的元素值增加 val 
void update(int o, int l, int r, int i, int val) {
    if (l == r) {
        mn[o] += val;
        sum[o] += val;
        return;
    }
    int m = (l + r) / 2;
    if (i <= m) {
        update(o * 2, l, m, i, val);
    } else {
        update(o * 2 + 1, m + 1, r, i, val);
    }
    mn[o] = min(mn[o * 2], mn[o * 2 + 1]);
    sum[o] = sum[o * 2] + sum[o * 2 + 1];
}

// 返回区间 [L,R] 内的元素和
long long querySum(int o, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return sum[o];
    }
    long long res = 0;
    int m = (l + r) / 2;
    if (L <= m) {
        res = querySum(o * 2, l, m, L, R);
    }
    if (R > m) {
        res += querySum(o * 2 + 1, m + 1, r, L, R);
    }
    return res;
}
