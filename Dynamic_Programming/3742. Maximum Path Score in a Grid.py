# TC:O(m * n * k) SC:(n * k)
class Solution:
    def maxPathScore(self, grid: List[List[int]], k: int) -> int:
        m, n = len(grid), len(grid[0])
        # dp[cost][j] = 走到目前列第 j 格，花費 cost 的最大分數
        prev = [[-inf] * (k + 1) for _ in range(n)]

        first_cost = 0
        prev[0][first_cost] = 0

        for j in range(1, n):
            cost_here = 0 if grid[0][j] == 0 else 1
            for c in range(cost_here, k + 1):
                if prev[j - 1][c - cost_here] != -inf:
                    prev[j][c] = prev[j - 1][c - cost_here] + grid[0][j]

        for i in range(1, m):
            cur = [[-inf] * (k + 1) for _ in range(n)]
            for j in range(n):
                cost_here = 0 if grid[i][j] == 0 else 1
                for c in range(cost_here, k + 1):
                    val = -inf
                    if prev[j][c - cost_here] != -inf:
                        val = max(val, prev[j][c - cost_here])
                    if j > 0 and cur[j - 1][c - cost_here] != -inf:
                        val = max(val, cur[j - 1][c - cost_here])
                    if val != -inf:
                        cur[j][c] = val + grid[i][j]
            prev = cur

        ans = max(prev[n - 1])
        return ans if ans != -inf else -1
