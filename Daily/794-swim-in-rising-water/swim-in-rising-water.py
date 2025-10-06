class Solution:
    def swimInWater(self, grid: List[List[int]]) -> int:
        '''
        也就是每一點最少需要多少時間走到 -> dijkstra
        '''
        n = len(grid)
        pq = []
        pq.append((grid[0][0], 0, 0))
        minDist = [[inf] * n for _ in range(n)]
        dirs = [(0, 1), (1, 0), (-1, 0), (0, -1)]
        while pq:
            c, x, y = heappop(pq)
            if minDist[x][y] <= c:
                continue
            if x == n - 1 and y == n - 1:
                return c
            minDist[x][y] = c
            for dx, dy in dirs:
                nx, ny = x + dx, y + dy
                if 0 <= nx < n and 0 <= ny < n:
                    nc = max(c, grid[nx][ny])
                    if minDist[nx][ny] > nc:
                        heappush(pq, (nc, nx, ny))
        return -1

