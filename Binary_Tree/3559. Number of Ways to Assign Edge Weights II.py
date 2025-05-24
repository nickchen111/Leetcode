# TC:O((n + q) * lgn) SC:O(nlgn)
class Solution:
    def assignEdgeWeights(self, edges: List[List[int]], queries: List[List[int]]) -> List[int]:
        MOD = 10 ** 9 + 7
        n = len(edges) + 1
        LOG = n.bit_length()

        tree = [[] for _ in range(n + 1)]
        for u, v in edges:
            tree[u].append(v)
            tree[v].append(u)

        stjump = [[-1] * LOG for _ in range(n + 1)]
        deep = [0] * (n + 1)
        dist = [0] * (n + 1)

        def dfs(u, p):
            for v in tree[u]:
                if v == p:
                    continue
                deep[v] = deep[u] + 1
                stjump[v][0] = u
                dist[v] = dist[u] + 1
                dfs(v, u)

        dfs(1, 0)

        for j in range(1, LOG):
            for i in range(1, n + 1):
                if stjump[i][j - 1] != -1:
                    stjump[i][j] = stjump[stjump[i][j - 1]][j - 1]

        def lca(u, v):
            if deep[u] < deep[v]:
                u, v = v, u
            for j in range(LOG - 1, -1, -1):
                if stjump[u][j] != -1 and deep[stjump[u][j]] >= deep[v]:
                    u = stjump[u][j]
            if u == v:
                return u
            for j in range(LOG - 1, -1, -1):
                if stjump[u][j] != -1 and stjump[u][j] != stjump[v][j]:
                    u = stjump[u][j]
                    v = stjump[v][j]
            return stjump[u][0]

        def calculate(k):
            return pow(2, k - 1, MOD) if k > 0 else 0

        ans = []
        for u, v in queries:
            anc = lca(u, v)
            k = dist[u] + dist[v] - 2 * dist[anc]
            ans.append(calculate(k))

        return ans
