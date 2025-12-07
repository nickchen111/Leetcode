class Solution:
    def maxSubgraphScore(self, n, edges, good):
        g = [[] for _ in range(n)]
        for x, y in edges:
            g[x].append(y)
            g[y].append(x)

        val = [1 if good[i] == 1 else -1 for i in range(n)]

        dp = [0] * n
        up = [0] * n

        def dfs1(u, p):
            res = val[u]
            for v in g[u]:
                if v == p: continue
                dfs1(v, u)
                res += max(0, dp[v])
            dp[u] = res

        dfs1(0, -1)

        def dfs2(u, p):
            pref = []
            for v in g[u]:
                if v == p: continue
                pref.append(max(0, dp[v]))

            total = sum(pref)

            for v in g[u]:
                if v == p: continue
                without_v = total - max(0, dp[v])
                up[v] = max(0, up[u] + val[u] + without_v)

                dfs2(v, u)

        dfs2(0, -1)

        ans = [0] * n
        for i in range(n):
            ans[i] = dp[i] + max(0, up[i])

        return ans
