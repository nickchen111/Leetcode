class SegmentTree:
    def __init__(self, n: int, init_val=0):
        if isinstance(init_val, int):
            init_val = [init_val] * n
        self._n = n
        self._tree = [0] * (2 << (n - 1).bit_length())
        self._build(init_val, 1, 0, n - 1)

    def _build(self, a: List[int], node: int, l: int, r: int) -> None:
        if l == r:
            self._tree[node] = a[l]
            return
        m = (l + r) // 2
        self._build(a, node * 2, l, m)
        self._build(a, node * 2 + 1, m + 1, r)
        self._maintain(node)

    def _maintain(self, node: int) -> None:
        self._tree[node] = max(self._tree[node * 2], self._tree[node * 2 + 1])

    def update(self, index: int, value: int):
        self._update(1, 0, self._n - 1, index, value)

    def _update(self, node: int, l: int, r: int, index: int, value: int):
        if l == r:
            self._tree[node] = value
            return
        mid = (l + r) // 2
        if index <= mid:
            self._update(node * 2, l, mid, index, value)
        else:
            self._update(node * 2 + 1, mid + 1, r, index, value)
        self._maintain(node)

    def find_leftmost_ge(self, x: int) -> int:
        if self._tree[1] < x:
            return -1
        return self._find(1, 0, self._n - 1, x)

    def _find(self, node: int, l: int, r: int, x: int) -> int:
        if l == r:
            return l
        mid = (l + r) // 2
        if self._tree[node * 2] >= x:
            return self._find(node * 2, l, mid, x)
        else:
            return self._find(node * 2 + 1, mid + 1, r, x)

class Solution:
    def numOfUnplacedFruits(self, fruits: List[int], baskets: List[int]) -> int:
        n = len(baskets)
        st = SegmentTree(n, baskets)
        ans = 0
        for fruit in fruits:
            idx = st.find_leftmost_ge(fruit)
            if idx == -1:
                ans += 1
            else:
                st.update(idx, 0)
        return ans
