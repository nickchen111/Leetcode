class Solution:
    def minScore(self, n: int, roads: List[List[int]]) -> int:
        pa = list(range(n + 1))
        def find(x:int) -> int:
            if x != pa[x]:
                pa[x] = find(pa[x])
            return pa[x]
        def merge(x:int, y:int) -> None:
            fx = find(x)
            fy = find(y)
            if fx < fy:
                pa[fy] = fx
            else:
                pa[fx] = fy
            return 
        for a, b, d in roads:
            merge(a, b)
        ans = inf
        for a, b, r in roads:
            if find(a) == 1:
                ans = min(ans, r)
        return ans