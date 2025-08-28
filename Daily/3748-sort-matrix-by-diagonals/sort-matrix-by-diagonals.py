class Solution:
    def sortMatrix(self, grid: List[List[int]]) -> List[List[int]]:
        n = len(grid)
        for k in range(1, n):
            tmp = sorted([grid[j - k][j] for j in range(k, n)])
            for j in range(k, n):
                grid[j - k][j] = tmp[j - k]
        for k in range(n):
            tmp = sorted([grid[j][j - k] for j in range(k, n)], reverse = True)
            for j in range(k, n):
                grid[j][j - k] = tmp[j - k]
        return grid