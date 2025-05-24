# TC:O(E + V) SC:O(E + V)
class Solution:
    def assignEdgeWeights(self, edges: List[List[int]]) -> int:
        MOD = 10 ** 9 + 7
        n = len(edges) + 1
        g = [[] for _ in range(n + 1)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)
        depth = [0] * (n + 1)
        visited = [False] * (n + 1)
        q = deque([(1, 0)])
        visited[1] = True
        mx_d = 0

        while q:
            u, d = q.popleft()
            depth[u] = d
            mx_d = max(mx_d, d)
            for v in g[u]:
                if not visited[v]:
                    visited[v] = True
                    q.append((v, d + 1))

        if mx_d == 0:
            return 0
        return pow(2, mx_d - 1, MOD)
