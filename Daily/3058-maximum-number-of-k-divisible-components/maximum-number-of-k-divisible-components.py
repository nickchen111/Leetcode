class Solution:
    def maxKDivisibleComponents(self, n: int, edges: List[List[int]], values: List[int], k: int) -> int:
        ans = 0
        g = [[] * n for _ in range(n)]
        for x, y in edges:
            g[x].append(y)
            g[y].append(x)
        
        def dfs(i:int, pa:int) -> int:
            nonlocal ans
            cur = values[i]
            for nxt in g[i]:
                if nxt == pa:
                    continue
                cur += dfs(nxt, i)
            cur %= k
            if cur == 0:
                ans += 1
            return cur
        dfs(0, -1)
        return ans