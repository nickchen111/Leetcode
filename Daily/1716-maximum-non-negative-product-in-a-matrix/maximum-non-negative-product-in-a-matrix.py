class Solution:
    def maxProductPath(self, grid: List[List[int]]) -> int:
        MOD = 10 ** 9 + 7
        m,n = len(grid), len(grid[0])
        @cache
        def dfs(i:int, j:int, k:int) -> int:
            if i == m - 1 and j == n - 1:
                return grid[i][j]
            mx, mn = -inf, inf
            x = grid[i][j]
            if i + 1 < m:
                down_mx, down_mn = dfs(i + 1, j, 0), dfs(i + 1, j, 1)
                if k:
                    mx = max(mx, x * down_mx, x * down_mn)
                else:
                    mn = min(mn, x * down_mx, x * down_mn)
            if j + 1 < n:
                right_mx, right_mn = dfs(i, j + 1, 0), dfs(i, j + 1, 1)
                if k:
                    mx = max(mx, x * right_mx, x * right_mn)
                else:
                    mn = min(mn, x * right_mx, x * right_mn)
            return mx if k else mn
        ans = max(dfs(0, 0, 0), dfs(0, 0, 1))
        return (ans % MOD) if ans >= 0 else -1
        

