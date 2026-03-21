class Solution:
    def reverseSubmatrix(self, grid: List[List[int]], x: int, y: int, k: int) -> List[List[int]]:
        m, n = len(grid), len(grid[0])
        # 枚舉k的一半即可 如果是3 那就到 x + k // 2 右開
        for i in range(x, x + k // 2):
            grid[i][y : y + k], grid[x + k - (i - x + 1)][y : y + k] = grid[x + k - (i - x + 1)][y : y + k], grid[i][y : y + k]
        return grid
            