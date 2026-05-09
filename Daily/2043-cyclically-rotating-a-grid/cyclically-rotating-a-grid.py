DIRS = (0, 1), (1, 0), (0, -1), (-1, 0)  # 右下左上

class Solution:
    def rotateGrid(self, grid: List[List[int]], k: int) -> List[List[int]]:
        m0, n0 = len(grid), len(grid[0])

        # 从外到内枚举圈
        for i in range(min(m0, n0) // 2):
            m, n = m0 - i * 2, n0 - i * 2  # 这一圈的行数和列数
            x, y = i, i  # 这一圈的左上角
            a = []
            for dx, dy in DIRS:
                for _ in range(n - 1):
                    a.append(grid[x][y])
                    x += dx
                    y += dy
                m, n = n, m  # 见 54. 螺旋矩阵 我的题解

            shift = k % len(a)
            a = a[shift:] + a[:shift]

            # 注意此时 (x, y) 又回到了左上角
            j = 0
            for dx, dy in DIRS:
                for _ in range(n - 1):
                    grid[x][y] = a[j]
                    j += 1
                    x += dx
                    y += dy
                m, n = n, m

        return grid
