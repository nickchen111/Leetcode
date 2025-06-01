# TC:O((n + q) * lgn) SC:O(n)
max_num = 100001
# 預處理質數
is_prime = [False, False] + [True] * (max_num - 2)
for i in range(2, int(max_num ** 0.5) + 1):
    if is_prime[i]:
        for j in range(i * i, max_num, i):
            is_prime[j] = False
class Node:
    __slots__ = 'val', 'todo'
class LazySegmentTree:
    _TODO_INIT = 0
    def __init__(self, n: int, init_val=0):
        if isinstance(init_val, int):
            init_val = [init_val] * n
        self._n = n
        self._tree = [Node() for _ in range(2 << (n - 1).bit_length())]
        self._build(init_val, 1, 0, n - 1)

    def _merge_val(self, a: int, b: int) -> int:
        return a if a > b else b # 本題是要求哪段區間比較大 又或者說哪個差分出來的區間內的點最大
    # 這段是用來當一個節點已經有懶標記，又來了新的更新操作時，需要將新舊標記合併
    def _merge_todo(self, a: int, b: int) -> int:
        return a + b
        
    def _apply(self, node: int, l: int, r: int, todo: int) -> None:
        cur = self._tree[node]
        cur.val += todo
        cur.todo = self._merge_todo(todo, cur.todo)
        
    def _spread(self, node: int, l: int, r: int) -> None:
        todo = self._tree[node].todo
        if todo == self._TODO_INIT: 
            return
        m = (l + r) // 2
        self._apply(node * 2, l, m, todo)
        self._apply(node * 2 + 1, m + 1, r, todo)
        self._tree[node].todo = self._TODO_INIT 
    def _maintain(self, node: int) -> None:
        self._tree[node].val = self._merge_val(self._tree[node * 2].val, self._tree[node * 2 + 1].val)
        
    def _build(self, a: List[int], node: int, l: int, r: int) -> None:
        self._tree[node].todo = self._TODO_INIT
        if l == r:
            self._tree[node].val = a[l]
            return
        m = (l + r) // 2
        self._build(a, node * 2, l, m)
        self._build(a, node * 2 + 1, m + 1, r)
        self._maintain(node)

    def _update(self, node: int, l: int, r: int, ql: int, qr: int, f: int) -> None:
        if ql <= l and r <= qr:
            self._apply(node, l, r, f)
            return
        self._spread(node, l, r)
        m = (l + r) // 2
        if ql <= m: 
            self._update(node * 2, l, m, ql, qr, f)
        if qr > m:
            self._update(node * 2 + 1, m + 1, r, ql, qr, f)
        self._maintain(node)

    def _query(self, node: int, l: int, r: int, ql: int, qr: int) -> int:
        if ql <= l and r <= qr:
            return self._tree[node].val
        self._spread(node, l, r)
        m = (l + r) // 2
        if qr <= m: 
            return self._query(node * 2, l, m, ql, qr)
        if ql > m: 
            return self._query(node * 2 + 1, m + 1, r, ql, qr)
        l_res = self._query(node * 2, l, m, ql, qr)
        r_res = self._query(node * 2 + 1, m + 1, r, ql, qr)
        return self._merge_val(l_res, r_res)
        
    def update(self, ql: int, qr: int, f: int) -> None:
        self._update(1, 0, self._n - 1, ql, qr, f)
        
    def query(self, ql: int, qr: int) -> int:
        return self._query(1, 0, self._n - 1, ql, qr)
class Solution:
    def maximumCount(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        n = len(nums)
        pos = defaultdict(SortedList)
        for i,x in enumerate(nums):
            if is_prime[x]:
                pos[x].add(i)
        t = LazySegmentTree(n, 0)
        for sl in pos.values():
            if len(sl) > 1:
                t.update(sl[0], sl[-1], 1)
        # 開始做每個數值的計算
        ans = []
        for i, x in queries:
            old = nums[i]
            nums[i] = x 
            # 判斷此數字是否是質數 以及之前是否有區間 先去除
            if is_prime[old]:
                sl = pos[old]
                if len(sl) > 1:
                    t.update(sl[0], sl[-1], -1)
                sl.remove(i)
                if len(sl) > 1:
                    t.update(sl[0], sl[-1], 1)
                elif not sl:
                    del pos[old]
            # 新的區間處理
            if is_prime[x]:
                sl = pos[x]
                if len(sl) > 1:
                    t.update(sl[0], sl[-1], -1)
                sl.add(i)
                if len(sl) > 1:
                    t.update(sl[0], sl[-1], 1)
            
            ans.append(len(pos) + t.query(0, n - 1))
        return ans
