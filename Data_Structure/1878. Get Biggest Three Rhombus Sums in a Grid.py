# TC:O(m*n* min(m,n)) SC:O(m*n)
class Solution:
    def getBiggestThree(self, grid: List[List[int]]) -> List[int]:
        m, n = len(grid), len(grid[0])
        diag_sum = [[0] * (n + 1) for _ in range(m + 1)] # ↘ 前缀和
        anti_sum = [[0] * (n + 1) for _ in range(m + 1)] # ↙ 前缀和

        for i, row in enumerate(grid):
            for j, v in enumerate(row):
                diag_sum[i + 1][j + 1] = diag_sum[i][j] + v
                anti_sum[i + 1][j] = anti_sum[i][j + 1] + v
        def query_diagonal(x: int, y: int, k: int) -> int:
            return diag_sum[x + k][y + k] - diag_sum[x][y]
        def query_anti_diagonal(x: int, y: int, k: int) -> int:
            return anti_sum[x + k][y - k + 1] - anti_sum[x][y + 1]
        x = y = z = 0
        def update(v:int) -> None:
            nonlocal x, y, z
            if v > x:
                x, y, z = v, x, y
            elif x > v > y:
                y, z = v, y
            elif y > v > z:
                z = v
        for i, row in enumerate(grid):
            for j, v in enumerate(row):
                update(v) # 只有一個
                mx = min(i, j, m - 1 - i, n - 1 - j)
                for k in range(1, mx + 1):
                    a = query_diagonal(i - k, j, k) # 右上的邊
                    b = query_diagonal(i, j - k, k) # 左下的邊
                    c = query_anti_diagonal(i - k + 1, j - 1, k - 1) # 左上的邊
                    d = query_anti_diagonal(i, j + k, k + 1) # 右下的邊
                    update(a + b + c + d)
        ans = [x, y, z]
        while ans[-1] == 0:
            ans.pop()
        return ans

