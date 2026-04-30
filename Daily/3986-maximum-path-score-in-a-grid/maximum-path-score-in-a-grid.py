class Solution:
    def maxPathScore(self, grid: List[List[int]], k: int) -> int:
        @cache
        def dfs(i:int, j:int, c:int) -> int:
            if c > k:
                return -inf
            if i == 0 and j == 0:
                return grid[i][j]
            x = grid[i][j]
            ans = -inf
            if i - 1 >= 0:
                ans = max(ans, dfs(i - 1, j, c + (1 if x else 0)) + x)
            if j - 1 >= 0:
                ans = max(ans, dfs(i, j - 1, c + (1 if x else 0)) + x)
            return ans
        ans = dfs(len(grid) - 1, len(grid[0]) - 1, 0)
        dfs.cache_clear()
        return ans if ans != -inf else -1