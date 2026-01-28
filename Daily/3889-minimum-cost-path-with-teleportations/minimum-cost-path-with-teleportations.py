class Solution:
    def minCost(self, grid: List[List[int]], k: int) -> int:
        m, n = len(grid), len(grid[0])
        mx = max(map(max, grid))
        suf_min_f = [inf] * (mx + 2)
        # 空間優化
        for _ in range(k + 1):
            min_f = [inf] * (mx + 1)

            f = [inf] * (n + 1)
            f[1] = -grid[0][0]
            for i in range(m):
                for j in range(n):
                    f[j + 1] = min(min(f[j], f[j + 1]) + grid[i][j], suf_min_f[grid[i][j]])
                    min_f[grid[i][j]] = min(min_f[grid[i][j]], f[j + 1])
            for i in range(mx, -1, -1):
                suf_min_f[i] = min(suf_min_f[i + 1], min_f[i])
        return f[n]