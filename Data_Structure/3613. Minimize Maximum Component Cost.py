# Union Find + Sort: TC:O(n + mlogm + mlogn) SC:O(n) Union Find + Binary Search: TC:O(n * logt * logn) SC:O(n)
class UnionFind:
    def __init__(self, n: int):
        self._fa = list(range(n))
        self.cc = n

    def find(self, x: int) -> int:
        if self._fa[x] != x:
            self._fa[x] = self.find(self._fa[x])
        return self._fa[x]

    def merge(self, from_: int, to: int) -> None:
        x, y = self.find(from_), self.find(to)
        if x == y:
            return
        if x < y:
            self._fa[y] = x
        else:
            self._fa[x] = y
        self.cc -= 1
    def count(self) -> int:
        return self.cc
class Solution:
    def minCost(self, n: int, edges: List[List[int]], k: int) -> int:
        if len(edges) == 0:
            return 0
        if n == k:
            return 0
        '''
        切越多 分出的組越多 會比k還大
        '''
        edges.sort(key = lambda x : x[2])
        uf = UnionFind(n)
        ans = 0
        for x, y, w in edges:
            if uf.count() == k:
                break
            uf.merge(x, y)
            ans = max(ans, w)
        return ans
        def check(mid :int) -> bool:
            uf = UnionFind(n)
            ans = inf
            for x, y, w in edges:
                if uf.count() == k:
                    break
                if w > mid:
                    continue
                uf.merge(x, y)
                ans = max(ans, w)
            return True if uf.count() <= k else False 
        while left < right:
            mid = (left + right) // 2
            if check(mid):
                right = mid
            else:
                left = mid + 1
        return left
        
        
