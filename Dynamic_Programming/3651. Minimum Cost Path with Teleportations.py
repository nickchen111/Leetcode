# TC:O((m * n + U)k) U為數值最大值 SC:O(n + U)
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
        '''
        for _ in range(k + 1):
            min_f = [inf] * (mx + 1)

            f = [[inf] * (n + 1) for _ in range(m + 1)]
            f[0][1] = f[1][0] = -grid[0][0]
            for i in range(m):
                for j in range(n):
                    f[i + 1][j + 1] = min(min(f[i + 1][j], f[i][j + 1]) + grid[i][j], suf_min_f[grid[i][j]])
                    min_f[grid[i][j]] = min(min_f[grid[i][j]], f[i + 1][j + 1])
            for i in range(mx, -1, -1):
                suf_min_f[i] = min(suf_min_f[i + 1], min_f[i])
        return f[m][n]
        '''


# Dijkstra 寫法 TC:O(mnklogmnk) SC:O(mnk)
class Solution:
    def minCost(self, grid: List[List[int]], k: int) -> int:
        m, n = len(grid), len(grid[0])

        dist = [[[inf] * (k + 1) for _ in range(n)] for _ in range(m)]
        dist[0][0][0] = 0

        cells = []
        for i in range(m):
            for j in range(n):
                cells.append((grid[i][j], i, j))
        cells.sort()

        ptr = [0] * (k + 1)

        pq = [(0, 0, 0, 0)]  # cost, x, y, used_teleports

        while pq:
            cost, x, y, t = heapq.heappop(pq)
            if cost > dist[x][y][t]:
                continue

            if x == m - 1 and y == n - 1:
                return cost

            for dx, dy in ((1, 0), (0, 1)):
                nx, ny = x + dx, y + dy
                if nx < m and ny < n:
                    nc = cost + grid[nx][ny]
                    if nc < dist[nx][ny][t]:
                        dist[nx][ny][t] = nc
                        heapq.heappush(pq, (nc, nx, ny, t))

            if t < k:
                while ptr[t] < len(cells) and cells[ptr[t]][0] <= grid[x][y]:
                    _, i, j = cells[ptr[t]]
                    if cost < dist[i][j][t + 1]:
                        dist[i][j][t + 1] = cost
                        heapq.heappush(pq, (cost, i, j, t + 1))
                    ptr[t] += 1
        return -1
