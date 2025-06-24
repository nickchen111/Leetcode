# TC:O(nlgU) U為nums最大值 SC:O(U)
class SegmentTree:
    def __init__(self, n: int):
        self._n = n
        self._tree = [0] * (2 << (n - 1).bit_length())

    def _merge_val(self, a: int, b: int) -> int:
        return max(a, b)

    def _maintain(self, node: int):
        self._tree[node] = self._merge_val(self._tree[node * 2], self._tree[node * 2 + 1])

    def _update(self, node: int, l: int, r: int, idx: int, val: int):
        if l == r:
            self._tree[node] = self._merge_val(self._tree[node], val)
            return
        m = (l + r) // 2
        if idx <= m:
            self._update(node * 2, l, m, idx, val)
        else:
            self._update(node * 2 + 1, m + 1, r, idx, val)
        self._maintain(node)

    def _query(self, node: int, l: int, r: int, ql: int, qr: int) -> int:
        if qr < l or r < ql:
            return 0
        if ql <= l and r <= qr:
            return self._tree[node]
        m = (l + r) // 2
        lval = self._query(node * 2, l, m, ql, qr)
        rval = self._query(node * 2 + 1, m + 1, r, ql, qr)
        return self._merge_val(lval, rval)

    def update(self, idx: int, val: int):
        self._update(1, 0, self._n - 1, idx, val)

    def query(self, l: int, r: int) -> int:
        return self._query(1, 0, self._n - 1, l, r)

class Solution:
    def lengthOfLIS(self, nums: List[int], k: int) -> int:
        '''
        問最長遞增子序列但滿足以下條件
        1. 嚴格遞增
        2. 相鄰兩個元素差不超過k
        每走過一個數字就是在問說在我這個數字nums[i] - k ~ nums[i] - 1 之間的最長遞增子序列長度是多少
        所以需要維護一個區間訊息意涵某區間的最值 -> 線段樹
        '''
        mx = max(nums)
        tree = SegmentTree(mx + 2)
        ans = 0
        for x in nums:
            l = max(1, x - k)
            r = x - 1
            max_dp = tree.query(l, r) if l <= r else 0
            tree.update(x, max_dp + 1)
            ans = max(ans, max_dp + 1)
        return ans
