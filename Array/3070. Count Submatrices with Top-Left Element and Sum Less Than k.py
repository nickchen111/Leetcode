# TC:O(m*n) SC:O(n)
class Solution:
    def countSubmatrices(self, grid: List[List[int]], k: int) -> int:
        col_sum = [0] * len(grid[0])
        ans = 0
        for row in grid:
            s = 0
            for j, x in enumerate(row):
                col_sum[j] += x
                s += col_sum[j]
                if s > k:
                    break
                ans += 1
        return ans

  # 2D prefix sum
  class Solution:
    def countSubmatrices(self, grid: List[List[int]], k: int) -> int:
        presum = [[0] * (len(grid[0]) + 1) for _ in range(len(grid) + 1)]
        ans = 0
        for i, row in enumerate(grid):
            for j, x in enumerate(row):
                presum[i + 1][j + 1] = presum[i][j + 1] + presum[i + 1][j] - presum[i][j] + x
                if presum[i + 1][j + 1] <= k:
                    ans += 1
        return ans
