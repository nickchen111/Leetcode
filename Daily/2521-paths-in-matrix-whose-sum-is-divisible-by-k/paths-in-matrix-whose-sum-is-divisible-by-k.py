class Solution:
    def numberOfPaths(self, grid: List[List[int]], k: int) -> int:
        '''
        網格圖DP
        '''
        m, n = len(grid), len(grid[0])
        MOD = 10 ** 9 + 7
        @cache
        def dfs(i:int, j:int, r:int) ->int:
            if i == 0 and j == 0:
                return 1 if (r + grid[i][j]) % k == 0 else 0
            if i < 0 or j < 0:
                return 0
            return (dfs(i - 1, j, (r + grid[i][j]) % k) + dfs(i, j - 1, (r + grid[i][j]) % k)) % MOD
        ans = dfs(m - 1, n - 1, 0) % MOD
        dfs.cache_clear()
        return ans
