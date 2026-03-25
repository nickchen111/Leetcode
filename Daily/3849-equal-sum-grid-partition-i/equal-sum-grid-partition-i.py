class Solution:
    def canPartitionGrid(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        s = [[0] * (n + 1) for _ in range(m + 1)]
        for i, row in enumerate(grid):
            for j, x in enumerate(row):
                s[i + 1][j + 1] = s[i + 1][j] + s[i][j + 1] - s[i][j] + x

        if s[m][n] % 2:
            return False
        for i in range(m):
            if s[i + 1][n] == s[m][n] - s[i + 1][n]:
                return True
        for j in range(n):
            if s[m][j + 1] == s[m][n] - s[m][j + 1]:
                return True
        return False