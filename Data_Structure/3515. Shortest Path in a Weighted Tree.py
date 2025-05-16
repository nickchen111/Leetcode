# TC:O((n + q) * lgn) SC:O(n)
class FenwickTree:
    def __init__(self, n: int):
        self.tree = [0] * (n + 1) 
    def update(self, i: int, val: int) -> None:
        while i < len(self.tree):
            self.tree[i] += val
            i += i & -i
    def pre(self, i: int) -> int:
        res = 0
        while i > 0:
            res += self.tree[i]
            i &= i - 1
        return res
    def query(self, l: int, r: int) -> int:
        if r < l:
            return 0
        return self.pre(r) - self.pre(l - 1)
class Solution:
    def treeQueries(self, n: int, edges: List[List[int]], queries: List[List[int]]) -> List[int]:
        '''
        1 ~ n 節點
        給你邊 表明是一棵樹 問你節點 1到某節點 最小邊權為多少?
        並且能夠任意修改邊權 -> 想到BIT 支持單點修改 區間查詢 presum 這種可差分訊息
        如何判斷給的兩個點誰是子節點 誰是父節點 -> 時間戳
        如何判斷目前要查詢的區間 是歸屬於誰? -> 時間戳
        '''
        g = [[] for _ in range(n + 1)]
        for x, y, w in edges:
            g[x].append(y)
            g[y].append(x)
        in_, out, weights = [0] * (n + 1), [0] * (n + 1), [0] * (n + 1)
        clock = 0
        def dfs(u:int, f:int) -> None:
            nonlocal clock
            clock += 1
            in_[u] = clock
            for y in g[u]:
                if y != f:
                    dfs(y, u)
            out[u] = clock
        dfs(1, 0)
        bit = FenwickTree(n)
        def update(x:int, y:int, w:int) -> None:
            if in_[x] > in_[y]: y = x
            d = w - weights[y]
            weights[y] = w
            bit.update(in_[y], d)
            bit.update(out[y] + 1, -d)
        for e in edges:
            update(*e)
        ans = []
        for q in queries:
            if q[0] == 1:
                update(q[1], q[2], q[3])
            else:
                ans.append(bit.pre(in_[q[1]]))
        return ans
