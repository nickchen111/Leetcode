# 二分 + Union Find TC:O((n + m) * lognlogU) SC:O(n)
class Solution:
    def maxStability(self, n: int, edges: List[List[int]], k: int) -> int:
        '''
        不一定要把edge加入 但如果沒辦法連到所有節點就要加入
        1. 有些是必定要加入的
        2. 不一定要加入的就要挑選較大的strength去加入 並且如果還有ｋ就可以把它 * 2 
        貪心的想法是先加入必須加入的edge 去對他 * 2 
        找出之中最小的就是答案 最大中找最小？ 二分猜 在判斷是否可以聯通？！
        如何判斷某個edge是必須的？
        '''
        class UnionFind:
            def __init__(self, n):
                self.parent = list(range(n))
                self.components = n
            
            def find(self, x):
                if self.parent[x] != x:
                    self.parent[x] = self.find(self.parent[x])
                return self.parent[x]
            
            def union(self, x, y):
                px, py = self.find(x), self.find(y)
                if px == py:
                    return False
                if px < py:
                    px, py = py, px
                self.parent[py] = px
                self.components -= 1
                return True
            
            def connected(self):
                return self.components == 1
        must_edges = []
        min_s, max_s = inf, -inf
        uf_all = UnionFind(n)
        uf_must = UnionFind(n)
        for u, v, s, must in edges:
            if must == 1 and not uf_must.union(u, v):
                return -1
            uf_all.union(u, v)
            min_s = min(min_s, s)
            max_s = max(max_s, s)
        if not uf_all.connected():
            return -1

        def check(mid):
            uf = UnionFind(n)
            avalibleEdges = []
            cnt = 0
            for u, v, s, must in edges:
                if must == 1:
                    if s >= mid:
                        uf.union(u, v)
                    else:
                        return False
            for u, v, s, must in edges:
                if must == 0:
                    if s >= mid:
                        uf.union(u, v) # 不需升級
                    elif s * 2 >= mid:
                        avalibleEdges.append((u, v, s))
            for u, v, s, needUpgrade in avalibleEdges:
                if uf.find(u) != uf.find(v):
                    if cnt < k:
                        uf.union(u, v)
                        cnt += 1
                        if uf.connected():
                            return True
            return uf.connected()
        left, right = min_s, max_s * 2 + 1
        ans = -1
        while left < right:
            mid = (left + right + 1) // 2
            if check(mid):
                left = mid
            else:
                right = mid - 1
        return left
# Kruskal + Union Find TC:O(mlogm + (n + m)logn) SC:O(n)
class UnionFind:
    def __init__(self, n: int):
        self._fa = list(range(n))
        self.cc = n

    def find(self, x: int) -> int:
        if self._fa[x] != x:
            self._fa[x] = self.find(self._fa[x])
        return self._fa[x]

    def merge(self, from_: int, to: int) -> bool:
        x, y = self.find(from_), self.find(to)
        if x == y: 
            return False
        self._fa[x] = y
        self.cc -= 1
        return True


class Solution:
    def maxStability(self, n: int, edges: List[List[int]], k: int) -> int:
        uf = UnionFind(n)
        all_uf = UnionFind(n)
        min_s1 = inf
        for x, y, s, must in edges:
            if must:
                if not uf.merge(x, y):
                    return -1
                min_s1 = min(min_s1, s)
            all_uf.merge(x, y)

        if all_uf.cc > 1:
            return -1
        if uf.cc == 1:
            return min_s1
        edges.sort(key=lambda e: -e[2])
        a = []
        for x, y, s, must in edges:
            if not must and uf.merge(x, y):
                a.append(s)

        # 答案為如下三者的最小值：
        # 1. must = 1 中的最小邊權
        # 2. a 中最小邊權 * 2
        # 3. a 中第 k+1 小邊權
        ans = min(min_s1, a[-1] * 2)
        if k < len(a):
            ans = min(ans, a[-1 - k])
        return ans

