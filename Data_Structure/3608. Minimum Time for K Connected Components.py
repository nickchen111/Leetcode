# Union Find + Sort: TC:O(n + mlogm + mlogn) SC:O(n)
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
    def minTime(self, n: int, edges: List[List[int]], k: int) -> int:
        uf = UnionFind(n)
        edges.sort(key = lambda x:x[2], reverse = True)

        for x, y, t in edges:
            uf.merge(x, y)
            if uf.count() < k:
                return t
        return 0
      
# Union Find + Binary Search: TC:O(n * logt * logn) SC:O(n)
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
    def minTime(self, n: int, edges: List[List[int]], k: int) -> int:
        '''
        如果目前component數量就 >= 不用移除
        
        '''
        left, right = 0, -1
        for x, y, t in edges:
            right = max(right, t)
        def check(mid:int) -> bool:
            uf = UnionFind(n)
            for x, y, t in edges:
                if t > mid:
                    uf.merge(x,y)
            return uf.count() >= k
        while left < right:
            mid = (left + right) // 2
            if check(mid):
                right = mid
            else:
                left = mid + 1
        return left
        
            
