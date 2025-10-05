class Solution:
    def pacificAtlantic(self, heights: List[List[int]]) -> List[List[int]]:
        m, n = len(heights), len(heights[0])
        P = [[False] * n for _ in range(m)]
        A = [[False] * n for _ in range(m)]
        dirs = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        def dfs(x:int, y:int, v: List[List[int]]) -> None:
            v[x][y] = True
            for dx, dy in dirs:
                nx, ny = x + dx, y + dy
                if 0 <= nx < m and 0 <= ny < n and not v[nx][ny] and heights[x][y] <= heights[nx][ny]:
                    dfs(nx, ny, v)
        for i in range(m):
            dfs(i, 0, P)
            dfs(i, n - 1, A)
        for j in range(n):
            dfs(0, j, P)
            dfs(m - 1, j, A)
        ans = []
        for i in range(m):
            for j in range(n):
                if P[i][j] and A[i][j]:
                    ans.append([i,j])
        return ans