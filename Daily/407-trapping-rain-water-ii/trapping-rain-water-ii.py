class Solution:
    def trapRainWater(self, heights: List[List[int]]) -> int:
        '''
        就是從外圍開始到裡面做bfs
        '''
        m, n = len(heights), len(heights[0])
        pq = []
        for i in range(m):
            heappush(pq, (heights[i][0], i, 0))
            heappush(pq, (heights[i][n - 1], i, n - 1))
        for j in range(1, n):
            heappush(pq, (heights[0][j], 0, j))
            heappush(pq, (heights[m - 1][j], m - 1, j))
        dirs = [(-1, 0), (0, -1), (1, 0), (0, 1)]
        visited = [[False] * n for _ in range(m)]

        level = -inf
        ans = 0
        while pq:
            (h, x, y) = heappop(pq)
            print(h)
            if visited[x][y]: continue
            visited[x][y] = True
            if h > level:
                level = h
            ans += level - h

            for dx, dy in dirs:
                nx, ny = x + dx, y + dy
                if 0 <= nx < m and 0 <= ny < n and not visited[nx][ny]:
                    heappush(pq, (heights[nx][ny], nx, ny))
        return ans
