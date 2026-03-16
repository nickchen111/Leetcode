# TC:O(nlogn) 如果用DFS建圖可以做到O(n) SC:O(n)
class UnionFind:
    def __init__(self, n):
        self.fa = list(range(n))
        self.cc = n

    def find(self, x) -> int:
        if self.fa[x] != x:
            self.fa[x] = self.find(self.fa[x])
        return self.fa[x]

    def merge(self, x, y) -> None:
        fx, fy = self.find(x), self.find(y)
        if fx == fy:
            return
        if fx > fy:
            self.fa[fy] = fx
        elif fx < fy:
            self.fa[fx] = fy
        self.cc -= 1
class Solution:
    def maxActivated(self, points: list[list[int]]) -> int:
        '''
        有點像bfs 或者dfs 去處理所有會被影響到的point
        是否能把這些Point轉成下標 就可以看會被傳多遠 但是要選哪個point 這些point之間有多少個可以互聯通
        '''
        n = len(points)
        x_map = defaultdict(list)
        y_map = defaultdict(list)
        for i, (x, y) in enumerate(points):
            x_map[x].append(i)
            y_map[y].append(i)

        uf = UnionFind(n)
        for v in x_map.values():
            for a, b in pairwise(v):
                uf.merge(a, b)
        for v in y_map.values():
            for a, b in pairwise(v):
                uf.merge(a, b)
        cnt = Counter(uf.find(i) for i in range(n))
        mx = mx2 = 0
        for v in cnt.values():
            if v > mx:
                mx, mx2 = v, mx
            elif v > mx2:
                mx2 = v
        return mx + mx2 + 1

                
        
