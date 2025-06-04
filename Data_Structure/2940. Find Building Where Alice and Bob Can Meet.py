# Heap 最小堆 TC:O(n + qlgq) SC:O(n) 單調棧二分: TC:O(n + qlgn) SC:O(n + q) 線段樹二分: TC:O(n + qlgn) SC:O(n)
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

    def _query(self, node: int, l: int, r: int, ql: int, qr: int, h:int) -> int:
        if self._tree[node] <= h:
            return -1
        if l == r:
            return l
        m = (l + r) // 2
        if ql > m:
            return self._query(node * 2 + 1, m + 1, r, ql, qr, h)
        l_res = self._query(node * 2, l, m, ql, qr, h)
        if l_res != -1:
            return l_res
        return self._query(node * 2 + 1, m + 1, r, ql, qr, h)

    def query(self, ql: int, qr: int, h:int) -> int:
        return self._query(1, 0, self._n - 1, ql, qr, h)

class Solution:
    def leftmostBuildingQueries(self, heights: List[int], queries: List[List[int]]) -> List[int]:
        '''
        人可以跳去右邊 如果下一個建築比較高
        問說 a 與 b 可以跳去哪個最左邊的建築
        暴力的想法就是兩個人每次的query都走走看，這樣會是nq複雜度
        1. 線段樹去找出某段區間比我小的最左邊元素下標
        2. 因為不會做區間更新，這題也可以設計一個單調棧然後做offline query排序
        '''
        n = len(heights)
        # 最小堆
        ans = [-1] * len(queries)
        qs =[ [] for _ in heights]
        for i, (a, b) in enumerate(queries):
            if a > b:
                a, b = b, a
            if a == b or heights[a] < heights[b]:
                ans[i] = b
            else:
                qs[b].append((heights[a], i)) # 要比較的高度, 實際idx
        h = []
        for i, x in enumerate(heights):
            while h and h[0][0] < x:
                # 堆頂的 heights[a] 可以跳到 heights[i]
                ans[heappop(h)[1]] = i
            for q in qs[i]:
                heappush(h, q)  # 後面再回答
        return ans
        '''
        # 離線 + 單調棧二分
        ans = [-1] * len(queries)
        qs =[ [] for _ in heights]
        for i, (a, b) in enumerate(queries):
            if a > b:
                a, b = b, a
            if a == b or heights[a] < heights[b]:
                ans[i] = b
            else:
                qs[b].append((heights[a], i)) # 要比較的高度, 實際idx
        st = []
        for i in range(n - 1, -1, -1):
            for ha, idx in qs[i]: # 在這個高度下我可以從st拿出的最靠左的比我高高度為何?
                j = bisect_left(st, -ha, key=lambda i: -heights[i])  - 1 # 取反以後就是要找小於-ha的第一個下標
                if j >= 0:
                    ans[idx] = st[j]
            while len(st) > 0 and heights[i] >= heights[st[-1]]:
                st.pop()
            st.append(i) # 會是大到小排序
        return ans
        '''

        '''
        #線段樹 二分
        tree = SegmentTree(n, heights)
        ans = []
        for i, j in queries:
            i, j = min(i, j), max(i, j)
            if i == j:
                ans.append(i)
                continue
            if heights[i] < heights[j]:
                ans.append(j)
            else:
                if j + 1 >= n:
                    ans.append(-1)
                    continue
                ans.append(tree.query(j + 1, n - 1, heights[i]))
        return ans
        '''
        
        
