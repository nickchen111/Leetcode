class Solution:
    def constructProductMatrix(self, grid: List[List[int]]) -> List[List[int]]:
        m, n = len(grid), len(grid[0])
        MOD = 12345
        p = [[0] * n for _ in range(m)]
        suf = 1
        for i in range(m - 1, -1, -1):
            for j in range(n - 1, -1, -1):
                p[i][j] = suf
                suf = suf * grid[i][j] % MOD
        pre = 1
        for i, row in enumerate(grid):
            for j, x in enumerate(row):
                p[i][j] = p[i][j] * pre % MOD
                pre = pre * x % MOD
        return p
