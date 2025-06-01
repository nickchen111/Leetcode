# 實際調用
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
        return a + b 
        
    def _merge_todo(self, a: int, b: int) -> int:
        return a + b 
        
    def _apply(self, node: int, l: int, r: int, todo: int) -> None:
        cur = self._tree[node]
        cur.val += todo * (r - l + 1)
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
        
# 講解 入門 線段樹模板
class Solution:
    def handleQuery(self, nums1: List[int], nums2: List[int], queries: List[List[int]]) -> List[int]:
        '''
        lazy 線段樹入門
        問題： 一個數組，更新一個子數組的值(都加上一個數，把子數組內的值取反)
                      查詢一個子數組的值(求和，最大值...)

        兩大思想:
        1. 挑選O(n)特殊區間 使得任意一個區間可以被拆分成O(lgn)個特殊區間(用最近公共祖先思考)
            挑選O(n)特殊區間: build
        2. lazy 更新 / 延遲更新
        lazy tag : 用一個數組維護每個區間需要更新的值，如果這個值 = 0 表示不需要更新操作 
        值 != 0 表示更新操作在這個區間停住了 就不繼續遞歸後續的子區間
        如果後面又多了一個更新，破壞了lazy tag區間 那麼這個區間就得繼續遞歸更新下去
        '''
        n = len(nums1)
        cnt1 = [0] * (4 * n)
        todo = [False] * (4 * n)
        def maintain(o:int) -> None:
            cnt1[o] = cnt1[o * 2] + cnt1[o * 2 + 1]
        def build(o:int, l:int, r:int) -> None: # add:int
            if l == r:
                cnt1[o] = nums1[l]
                return
            m = (l + r) // 2
            build(o * 2, l, m)
            build(o * 2 + 1, m + 1, r)
            # maintain
            maintain(o)
        # 更新[L,R] 查詢一樣概念
        def do(o:int, l:int, r:int) -> None:
            cnt1[o] = r - l + 1 - cnt1[o]
            todo[o] = not todo[o] # 區間翻轉
        def update(o:int, l:int, r:int, L: int, R:int) -> None: # add:int 
            if L <= l and r <= R: # 當你查詢的區間完全包含當前遞歸到的區間不論查詢or更新就都不用繼續走了
                do(o, l, r)
                # todo[o] += add 原本會寫成 todo = [0] * (4 * n) 但這題的更新只是
                return
            m = (l + r) // 2
            # 需要繼續遞歸，就把todo[o]的內容傳下去(給左右兒子)
            if todo[o]:
                do(o * 2, l, m)
                do(o * 2 + 1, m + 1, r)
                # todo[o * 2] += todo[o]
                # todo[o * 2 + 1] += todo[o]
                todo[o] = False # 0

            if L <= m:
                update(o * 2, l, m, L, R)
            if m < R:
                update(o * 2 + 1, m + 1, r, L, R)
            # maintain
            maintain(o)
        build(1,0,n-1) # 1 - index
        ans = []
          s = sum(nums2)
          for op, l, r in queries:
              if op == 1: update(1, 0, n-1, l, r)
              elif op == 2: s += l * cnt1[1]
              else: ans.append(s)
          return ans
