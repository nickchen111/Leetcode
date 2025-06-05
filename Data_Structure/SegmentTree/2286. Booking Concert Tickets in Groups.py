# TC:O((n + q)lgn) SC:O(n)
class BookMyShow:
    '''
    题意（换一个场景）
    一开始有 n 个空水桶，每个水桶的容量都是 m 升。水桶编号从 0 到 n−1。
    gather：在前 maxRow 个水桶中，找第一个还能装至少 k 升水的水桶，往里面倒入 k 升水。如果有这样的水桶，返回水桶编号，以及在倒水前，水桶有多少升水；如果没有这样的水桶，返回空列表。
    scatter：往前 maxRow 个水桶中倒入总量为 k 升的水。从左到右选择没有装满的水桶依次倒入。如果无法倒入总量为 k 升的水，则不执行操作，并返回 false；否则执行操作，并返回 true。
    '''
    def __init__(self, n: int, m: int):
        self.n = n
        self.m = m
        self.min = [0] * (2 << n.bit_length())
        self.sum = [0] * (2 << n.bit_length())
    def find_first(self, node: int, l: int, r: int, qr:int, x:int) -> int:
        if self.min[node] > x:
            return -1
        if l == r:
            return l
        m = (l + r) // 2
        if self.min[node * 2] <= x:
            return self.find_first(node * 2, l, m, qr, x)
        if qr > m:
            return self.find_first(node * 2 + 1, m + 1, r, qr, x)
        return -1
    def query_sum(self, node:int, l:int, r:int, ql:int, qr:int) -> int:
        if ql <= l and r <= qr:
            return self.sum[node]
        m = (l + r) // 2
        ans = 0
        if ql <= m:
            ans = self.query_sum(node * 2, l, m, ql, qr)
        if qr > m:
            ans += self.query_sum(node * 2 + 1, m + 1, r, ql, qr)
        return ans
    def update(self, node:int, l:int, r:int, qr:int, val:int) -> None: #在某個水瓶裝水
        if l == r:
            self.min[node] += val
            self.sum[node] += val
            return
        m = (l + r) // 2
        if qr <= m:
            self.update(node * 2, l, m, qr, val)
        else:
            self.update(node * 2 + 1, m + 1, r, qr, val)
        self.min[node] = min(self.min[node * 2], self.min[node * 2 + 1])
        self.sum[node] = self.sum[node * 2] + self.sum[node * 2 + 1]
    def gather(self, k: int, maxRow: int) -> List[int]:
        # 在前maxRow水桶中找出第一個還能裝k的水桶 返回他的編號以及裝之前已經裝多少水
        r = self.find_first(1, 0, self.n - 1, maxRow, self.m - k) 
        if r < 0:
            return []
        c = self.query_sum(1, 0, self.n - 1, r, r)
        self.update(1, 0, self.n - 1, r, k) # 倒水
        return [r, c]

    def scatter(self, k: int, maxRow: int) -> bool:
        s = self.query_sum(1, 0, self.n - 1, 0, maxRow)
        if (maxRow + 1) * self.m - s < k:
            return False
        # 從第一個還沒有裝滿水的開始
        i = self.find_first(1, 0, self.n - 1, maxRow, self.m - 1)
        while k:
            left = min(self.m - self.query_sum(1, 0, self.n - 1, i, i), k)
            self.update(1, 0, self.n - 1, i, left)
            k -= left
            i += 1 # i = self.find_first(1, 0, self.n - 1, maxRow, self.m - 1) 沒有比較快 
        return True
