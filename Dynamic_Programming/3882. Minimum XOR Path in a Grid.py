# TC:O(mnU) SC:O(mnU)
class Solution:
    def minCost(self, grid: list[list[int]]) -> int:
        m, n = len(grid), len(grid[0])
        @cache
        def dfs(i:int, j:int, cur: int) -> int:
            if i == 0 and j == 0:
                return cur
            ans = inf
            if i - 1 >= 0:
                ans = min(ans, dfs(i - 1, j, cur ^ grid[i - 1][j]))
            if j - 1 >= 0:
                ans = min(ans, dfs(i, j - 1, cur ^ grid[i][j - 1]))
            return ans
        ans = dfs(m - 1, n - 1, grid[m-1][n-1])
        dfs.cache_clear()
        return ans
            
