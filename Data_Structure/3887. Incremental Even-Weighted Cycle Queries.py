# TC:O(nlogn) SC:O(n)
class UnionFind:
    def __init__(self, n: int):
        self.fa = list(range(n))  # fa[x] 是 x 的代表元
        self.dis = [0] * n  # dis[x] = 從 x 到 fa[x] 的路徑異或和

    def find(self, x: int) -> int:
        fa = self.fa
        if fa[x] != x:
            root = self.find(fa[x])
            self.dis[x] ^= self.dis[fa[x]]
            fa[x] = root
        return fa[x]

    def merge(self, from_: int, to: int, value: int) -> bool:
        x, y = self.find(from_), self.find(to)
        dis = self.dis
        if x == y:
            return dis[from_] ^ dis[to] == value
        dis[x] = value ^ dis[to] ^ dis[from_]
        self.fa[x] = y
        return True


class Solution:
    def numberOfEdgesAdded(self, n: int, edges: List[List[int]]) -> int:
        uf = UnionFind(n)
        ans = 0
        for x, y, w in edges:
            if uf.merge(x, y, w):
                ans += 1
        return ans
