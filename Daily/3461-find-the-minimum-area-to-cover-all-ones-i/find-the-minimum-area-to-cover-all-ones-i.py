min = lambda x, y : x if x < y else y
max = lambda x, y : x if x > y else y
class Solution:
    def minimumArea(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        min_x = min_y = inf
        max_x = max_y = 0
        for i in range(m):
            for j in range(n):
                if grid[i][j]:
                    min_x = min(min_x, i)
                    min_y = min(min_y, j)
                    max_x = max(max_x, i)
                    max_y = max(max_y, j)
        return (max_x - min_x + 1) * (max_y - min_y + 1)