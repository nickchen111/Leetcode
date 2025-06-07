#TC:O((n + q * lgn) * k) SC:O(n * k)
class SegmentTree:
    def __init__(self, n: int, init_val=0, k: int=1):
        if isinstance(init_val, int):
            init_val = [init_val] * n
        self._n = n
        self._k = k
        self._tree = [None] * (2 << (n - 1).bit_length())
        self._build(init_val, 1, 0, n - 1)

    def _merge_val(self, a: int, b: int) -> Tuple[int, List[int]]:
        cnt = a[1].copy()
        left_mul = a[0]
        for rx, c in enumerate(b[1]):
            cnt[(left_mul * rx) % self._k] += c
        return (left_mul * b[0]) % self._k, cnt

    def new_val(self, val:int) -> Tuple[int, List[int]]:
        mul = val % self._k
        cnt = [0] * self._k
        cnt[mul] += 1
        return mul, cnt

    def _maintain(self, node: int) -> None:
        self._tree[node] = self._merge_val(self._tree[node * 2], self._tree[node * 2 + 1])

    def _build(self, a: List[int], node: int, l: int, r: int) -> None:
        if l == r:
            self._tree[node] = self.new_val(a[l])
            return
        m = (l + r) // 2
        self._build(a, node * 2, l, m)
        self._build(a, node * 2 + 1, m + 1, r) 
        self._maintain(node)

    def _update(self, node: int, l: int, r: int, i: int, val: int) -> None:
        if l == r:
            self._tree[node] = self.new_val(val)
            return
        m = (l + r) // 2
        if i <= m:
            self._update(node * 2, l, m, i, val)
        else:
            self._update(node * 2 + 1, m + 1, r, i, val)
        self._maintain(node)

    def _query(self, node: int, l: int, r: int, ql: int, qr: int) -> int:
        if ql <= l and r <= qr:
            return self._tree[node]
        m = (l + r) // 2
        if qr <= m:
            return self._query(node * 2, l, m, ql, qr)
        if ql > m:
            return self._query(node * 2 + 1, m + 1, r, ql, qr)
        l_res = self._query(node * 2, l, m, ql, qr)
        r_res = self._query(node * 2 + 1, m + 1, r, ql, qr)
        return self._merge_val(l_res, r_res)

    def update(self, i: int, val: int) -> None:
        self._update(1, 0, self._n - 1, i, val)

    def query(self, ql: int, qr: int) -> int:
        return self._query(1, 0, self._n - 1, ql, qr)
      
    def get(self, i: int) -> int:
        return self._query(1, 0, self._n - 1, i, i)
class Solution:
    def resultArray(self, nums: List[int], k: int, queries: List[List[int]]) -> List[int]:
        n = len(nums)
        t = SegmentTree(n, nums, k)
        ans = []
        for q in queries:
            index, val, start, x = q
            t.update(index, val)
            _, cnt = t.query(start, n - 1)
            ans.append(cnt[x])
        return ans
