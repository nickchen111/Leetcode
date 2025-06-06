# TC:O(U + qlgU) SC:O(U)
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

    def _update(self, node: int, l: int, r: int, i: int, val: int) -> None:
        if l == r:
            self._tree[node] = val
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
    def getResults(self, queries: List[List[int]]) -> List[bool]:
        '''
        問說某段區間內最長的區間段是多少?
        將某一段區間最大值修改 可以用一個有序集合 python用SortedList 去找他前後兩點位置去更新最大長度
        並且題目要求的某點之前位置可以分成有完全包含跟沒有
        '''
        m = max(q[1] for q in queries) + 1
        t = [0] * m
        # 逆向 + 樹狀數組
        def update(i: int, val: int) -> None:
            while i < len(t):
                t[i] = max(t[i], val)
                i += i & -i
        def pre_max(i: int) -> int:
            res = 0
            while i > 0:
                res = max(t[i], res)
                i &= i - 1
            return res
        pos = [0] + sorted(q[1] for q in queries if q[0] == 1)
        for x, y in pairwise(pos):
            update(y, y - x)
        sl = SortedList(pos)
        sl.add(m)
        ans = []
        for q in reversed(queries):
            x = q[1]
            i = sl.bisect_left(q[1])
            pre = sl[i - 1]
            if q[0] == 1: # 去除障礙物
                sl.remove(q[1])
                nxt = sl[i]
                update(nxt, nxt - pre)
            else:
                mx = max(pre_max(pre), q[1] - pre)
                ans.append(True if mx >= q[2] else False)
        return ans[::-1]
        
        '''
        線段樹
        tree = SegmentTree(m, 0)
        sl = SortedList([0, m])
        ans = []
        for q in queries:
            # 需要去判斷距離x的左邊障礙物是哪個
            i = sl.bisect_left(q[1])
            pre = sl[i - 1]
            if q[0] == 1: # 新增障礙物上去
                nxt = sl[i]
                sl.add(q[1])
                tree.update(q[1], q[1] - pre)
                tree.update(nxt, nxt - q[1])
            else:
                mx = max(tree.query(0, pre), q[1] - pre)
                ans.append(True if mx >= q[2] else False)
        return ans
        '''
