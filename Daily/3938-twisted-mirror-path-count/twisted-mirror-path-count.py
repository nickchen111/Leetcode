class Solution:
    def uniquePaths(self, grid: List[List[int]]) -> int:
        MOD = 1_000_000_007
        n = len(grid[0])
        f0 = [0] * (n + 1)
        f1 = [0] * (n + 1)
        f0[1] = f1[1] = 1
        for row in grid:
            for j, x in enumerate(row):
                if x == 0:
                    f0[j + 1] = (f0[j] + f1[j + 1]) % MOD
                    f1[j + 1] = f0[j + 1]
                else:
                    f0[j + 1] = f1[j + 1]
                    f1[j + 1] = f0[j]
        return f0[n]
