class Solution:
    def assignEdgeWeights(self, edges: List[List[int]]) -> int:
        MOD = 10 ** 9 + 7
        n = len(edges) + 1
        g = [[] for _ in range(n + 1)]
        for x, y in edges:
            g[x].append(y)
            g[y].append(x)
        def dfs(i:int, fa:int) -> int:
            d = 0
            for y in g[i]:
                if y != fa:
                    d = max(d, dfs(y, i) + 1)
            return d
        k = dfs(1, 0)
        return pow(2, k - 1, MOD)
