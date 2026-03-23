class Solution:
    def maxProductPath(self, grid: List[List[int]]) -> int:
        @cache
        def dfs(i: int, j: int) -> Tuple[int, int]:
            x = grid[i][j]
            if i == j == 0:
                return x, x

            res_min, res_max = inf, -inf
            if i > 0:
                mn, mx = dfs(i - 1, j)
                res_min = min(mn * x, mx * x)
                res_max = max(mn * x, mx * x)
            if j > 0:
                mn, mx = dfs(i, j - 1)
                res_min = min(res_min, mn * x, mx * x)
                res_max = max(res_max, mn * x, mx * x)

            return res_min, res_max

        ans = dfs(len(grid) - 1, len(grid[0]) - 1)[1]
        return -1 if ans < 0 else ans % 1_000_000_007