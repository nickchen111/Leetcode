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