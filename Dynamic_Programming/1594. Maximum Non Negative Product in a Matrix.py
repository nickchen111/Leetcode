# 遞歸寫法, 遞推參考cpp
class Solution:
    def maxProductPath(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        MOD = 10**9 + 7

        @cache
        def dfs(i: int, j: int, k:int) -> int:
            if i == m-1 and j == n-1:
                return grid[i][j]
            mx, mn = -inf, inf
            if i + 1 < m:
                down_max, down_min = dfs(i+1, j, 1), dfs(i+1,j, 0)
                if k > 0: mx = max(mx, grid[i][j] * down_max, grid[i][j] * down_min)
                else: mn = min(mn, grid[i][j] * down_max, grid[i][j] * down_min)
            if j + 1 < n:
                right_max, right_min = dfs(i, j+1, 1), dfs(i, j+1, 0)
                if k > 0: mx = max(mx, grid[i][j] * right_max, grid[i][j] * right_min)
                else: mn = min(mn, grid[i][j] * right_max, grid[i][j] * right_min)
            return mx if k > 0 else mn

        ans = max(dfs(0, 0, 0), dfs(0, 0, 1))
        return (ans % MOD) if ans >= 0 else -1

# 回傳兩種狀態的值寫法
class Solution:
    def maxProductPath(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        MOD = 10**9 + 7

        @cache
        def dfs(i: int, j: int) -> Tuple[int, int]:
            if i == m-1 and j == n-1:
                return grid[i][j], grid[i][j]

            mx, mn = -inf, inf
            if i + 1 < m:
                down_max, down_min = dfs(i+1, j)
                mx = max(mx, grid[i][j] * down_max, grid[i][j] * down_min)
                mn = min(mn, grid[i][j] * down_max, grid[i][j] * down_min)
            if j + 1 < n:
                right_max, right_min = dfs(i, j+1)
                mx = max(mx, grid[i][j] * right_max, grid[i][j] * right_min)
                mn = min(mn, grid[i][j] * right_max, grid[i][j] * right_min)

            return mx, mn

        ans = dfs(0, 0)[0]
        return (ans % MOD) if ans >= 0 else -1
