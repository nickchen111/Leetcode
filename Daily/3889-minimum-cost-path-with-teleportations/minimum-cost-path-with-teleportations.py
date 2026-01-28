class Solution:
    def minCost(self, grid: List[List[int]], k: int) -> int:
        m, n = len(grid), len(grid[0])
        INF = 10**18

        # dist[x][y][t]
        dist = [[[INF] * (k + 1) for _ in range(n)] for _ in range(m)]
        dist[0][0][0] = 0

        # 所有格子依 grid value 排序（給 teleport 用）
        cells = []
        for i in range(m):
            for j in range(n):
                cells.append((grid[i][j], i, j))
        cells.sort()

        # pointer 指向「目前可被 teleport 的最大 grid 值」
        ptr = [0] * (k + 1)
        used = [[[False] * n for _ in range(m)] for _ in range(k + 1)]

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