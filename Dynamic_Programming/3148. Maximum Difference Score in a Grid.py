# 3148. Maximum Difference Score in a Grid


# TC:O(m*n) SC:O(m*n)
class Solution:
    def maxScore(self, grid: List[List[int]]) -> int:
        m = len(grid)
        n = len(grid[0])
        res = -inf
        f = [[inf]*(n+1) for _ in range(m+1)]
        for i, row in enumerate(grid):
            for j, x in enumerate(row):
                mn = min(f[i+1][j], f[i][j+1])
                res = max(res, x - mn)
                f[i+1][j+1] = min(mn, x)
        return res
