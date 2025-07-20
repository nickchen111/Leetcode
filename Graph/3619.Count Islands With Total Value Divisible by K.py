# TC:O(n) SC:O(n)
class Solution:
    def countIslands(self, grid: List[List[int]], k: int) -> int:
        m, n = len(grid), len(grid[0])
        visited = [[False] * n for _ in range(m)]
        dirs = [(0, 1), (1, 0), (-1, 0),(0, -1)]
        def dfs(x:int, y:int) -> int:
            visited[x][y] = True
            ans = grid[x][y]
            for dirx, diry in dirs:
                nx = x + dirx
                ny = y + diry
                if 0 <= nx < m and 0 <= ny < n and not visited[nx][ny] and grid[nx][ny]:
                    ans += dfs(nx, ny)
            return ans
        ans = 0
        for i in range(m):
            for j in range(n):
                if grid[i][j] and not visited[i][j]:
                    cur = dfs(i, j)
                    if cur % k == 0:
                        ans += 1
        return ans
