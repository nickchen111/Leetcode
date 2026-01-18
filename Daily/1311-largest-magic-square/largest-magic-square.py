class Solution:
    def largestMagicSquare(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        row_sum = [[0] * (n + 1) for _ in range(m)]       # → 前缀和
        col_sum = [[0] * n for _ in range(m + 1)]         # ↓ 前缀和
        diag_sum = [[0] * (n + 1) for _ in range(m + 1)]  # ↘ 前缀和
        anti_sum = [[0] * (n + 1) for _ in range(m + 1)]  # ↙ 前缀和

        for i, row in enumerate(grid):
            for j, x in enumerate(row):
                row_sum[i][j + 1] = row_sum[i][j] + x
                col_sum[i + 1][j] = col_sum[i][j] + x
                diag_sum[i + 1][j + 1] = diag_sum[i][j] + x
                anti_sum[i + 1][j] = anti_sum[i][j + 1] + x

        # is_same_col_sum[i][j] 表示右下角为 (i, j) 的子矩形，每列元素和是否都相等
        is_same_col_sum = [[False] * n for _ in range(m)]

        for k in range(min(m, n), 1, -1):
            for i in range(k, m + 1):
                # 想象有一个 k×k 的窗口在向右滑动
                same_cnt = 1
                for j in range(1, n):
                    if col_sum[i][j] - col_sum[i - k][j] == col_sum[i][j - 1] - col_sum[i - k][j - 1]:
                        same_cnt += 1
                    else:
                        same_cnt = 1
                    # 连续 k 列元素和是否都一样
                    is_same_col_sum[i - 1][j] = same_cnt >= k

            for j in range(k, n + 1):
                # 想象有一个 k×k 的窗口在向下滑动
                sum_row = row_sum[0][j] - row_sum[0][j - k]
                same_cnt = 1
                for i in range(2, m + 1):
                    row_s = row_sum[i - 1][j] - row_sum[i - 1][j - k]
                    if row_s == sum_row:
                        same_cnt += 1
                        if (same_cnt >= k and  # 连续 k 行元素和都一样
                            is_same_col_sum[i - 1][j - 1] and  # 连续 k 列元素和都一样
                            col_sum[i][j - 1] - col_sum[i - k][j - 1] == sum_row and  # 列和 = 行和
                            diag_sum[i][j] - diag_sum[i - k][j - k] == sum_row and  # 主对角线和 = 行和
                            anti_sum[i][j - k] - anti_sum[i - k][j] == sum_row):  # 反对角线和 = 行和
                            return k
                    else:
                        sum_row = row_s
                        same_cnt = 1

        return 1
