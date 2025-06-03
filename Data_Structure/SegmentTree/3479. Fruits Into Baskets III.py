#TC:O(nlgn) SC:O(n)
class SegmentTree:
    def __init__(self, n: int, init_val=0):
        if isinstance(init_val, int):
            init_val = [init_val] * n
        self._n = n
        self._tree = [0] * (2 << (n - 1).bit_length())
        self._build(init_val, 1, 0, n - 1)

    def _merge_val(self, a: int, b: int) -> int:
        return max(a, b)

    def _maintain(self, node: int) -> None:
        self._tree[node] = self._merge_val(self._tree[node * 2], self._tree[node * 2 + 1])

    def _build(self, a: List[int], node: int, l: int, r: int) -> None:
        if l == r:
            self._tree[node] = a[l] 
            return
        m = (l + r) // 2
        self._build(a, node * 2, l, m)
        self._build(a, node * 2 + 1, m + 1, r) 
        self._maintain(node)

    # def _update(self, node: int, l: int, r: int, i: int, val: int) -> None:
    #     if l == r:
    #         self._tree[node] = self._merge_val(self._tree[node], val)
    #         return
    #     m = (l + r) // 2
    #     if i <= m:
    #         self._update(node * 2, l, m, i, val)
    #     else:
    #         self._update(node * 2 + 1, m + 1, r, i, val)
    #     self._maintain(node)

    def _query_and_update(self, node: int, l: int, r: int, ql: int, qr: int, x:int) -> int:
        # 這題是單點修改 所以很多區間查詢code需要修改
        # if ql <= l and r <= qr:
        if self._tree[node] < x:
            return -1
        if l == r:
            self._tree[node] = -1
            return l
        m = (l + r) // 2
        i = self._query_and_update(node * 2, l, m, ql, qr, x)
        if i < 0:
            i = self._query_and_update(node * 2 + 1, m + 1, r, ql, qr, x)
        self._maintain(node)
        return i
        # if qr <= m:
        #     return self._query(node * 2, l, m, ql, qr)
        # if ql > m:
        #     return self._query(node * 2 + 1, m + 1, r, ql, qr)
        # l_res = self._query(node * 2, l, m, ql, qr)
        # r_res = self._query(node * 2 + 1, m + 1, r, ql, qr)
        # return self._merge_val(l_res, r_res)

    def query(self, ql: int, qr: int, x:int) -> int:
        return self._query_and_update(1, 0, self._n - 1, ql, qr, x)
    
class Solution:
    def numOfUnplacedFruits(self, fruits: List[int], baskets: List[int]) -> int:
        '''
        理解線段樹的好題，每個水果都要去找一個array中最靠左的>=他的數量的藍子裝進去
        計算有多少個水果無法裝入藍子中? 如果暴力解就會需要每次裝一種水果都要iterate一次藍子
        但如果站在二分思想，如果可以在lgn找出最左邊要裝哪個藍子那就可以通過本題
        所以如果這些無序的array可以生成某種結構讓某個數值代表某段區間的最大值那就可以快速找出是否要搜尋某段較大的區間 -> 線段樹結構
        '''
        n = len(fruits)
        tree = SegmentTree(n, baskets)
        ans = 0
        for i, x in enumerate(fruits):
            j = tree.query(0, n - 1, x)
            if j < 0:
                ans += 1
        return ans
