# TC:O(4 ^ n) SC:O(n)
class Solution:
    def specialGrid(self, N: int) -> list[list[int]]:
        a = [[0] * (1 << N) for _ in range(1 << N)]
        val = 0
        def dfs(u:int, d:int, l:int, r:int):
            if d - u == 1:
                nonlocal val
                a[u][l] = val
                val += 1
                return
            m = (d - u) // 2
            dfs(u, u + m, l + m, r)
            dfs(u + m, d, l + m, r)
            dfs(u + m, d, l, l + m)
            dfs(u, u + m, l, l + m)
        dfs(0, (1 << N), 0, (1 << N))
        return a
                
