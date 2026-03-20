class Solution:
    def minAbsDiff(self, grid: List[List[int]], k: int) -> List[List[int]]:
        m, n = len(grid), len(grid[0])
        ans = [[0] * (n - k + 1) for _ in range(m - k + 1)]
        for i in range(m - k + 1):
            sub_grid = grid[i:i + k]
            for j in range(n - k + 1):
                tmp = []
                for row in sub_grid:
                    tmp.extend(row[j:j + k])
                tmp.sort()
                ret = inf
                for x, y in pairwise(tmp):
                    if x != y:
                        ret = min(ret, y - x)
                if ret != inf:
                    ans[i][j] = ret
        return ans


