class Solution:
    def numberOfPaths(self, grid: List[List[int]], k: int) -> int:
        '''
        網格圖DP
        '''
        m, n = len(grid), len(grid[0])
        MOD = 10 ** 9 + 7
        f = [[[0] * (k + 1) for _ in range(n)] for _ in range(m)]
        f[0][0][grid[0][0] % k] = 1
        for i in range(m):
            for j in range(n):
                if i == 0 and j == 0:
                    continue
                x = grid[i][j]
                for r in range(k):
                    if i - 1 >= 0 and f[i - 1][j][r]:
                        f[i][j][(r + x) % k] += f[i - 1][j][r]
                    if j - 1 >= 0 and f[i][j - 1][r]:
                        f[i][j][(r + x) % k] += f[i][j - 1][r]
                    f[i][j][(r + x) % k] %= MOD
        return f[m - 1][n - 1][0]

        '''
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
        '''
