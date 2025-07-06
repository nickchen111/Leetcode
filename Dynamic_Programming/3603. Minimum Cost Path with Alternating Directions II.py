# DP: TC:O(mn) SC:O(mn) -> O(n) Dijkstra: TC:O(mn *logmn) SC:O(mn)
min = lambda a, b: b if b < a else a
class Solution:
    def minCost(self, m: int, n: int, waitCost: List[List[int]]) -> int:
        """
        奇數 step -> 可以走 (往右/下)，代價為 (i+1)*(j+1)
        偶數 step -> 等待，代價為 waitCost[i][j]
        問到達 (m-1, n-1) 的最小 cost
        """
        f = [[inf] * (n + 1) for _ in range(m + 1)]
        f[0][1] = -waitCost[0][0]  # 計算 f[1][1] 的时候抵消掉
        for i, row in enumerate(waitCost):
            for j, c in enumerate(row):
                f[i + 1][j + 1] = min(f[i + 1][j], f[i][j + 1]) + c + (i + 1) * (j + 1)
        return f[m][n] - waitCost[-1][-1]
        '''
        遞歸
        @cache
        def dfs(i:int, j:int) -> int:
            if i < 0 or j < 0:
                return inf
            if i == 0 and j == 0:
                return 1
            return min(dfs(i - 1, j), dfs(i, j - 1)) + waitCost[i][j] + (i + 1) * (j + 1)
        return dfs(m - 1, n - 1) - waitCost[-1][-1]
        '''

        '''
        Dijkstra TC:O(mn *logmn) SC:O(mn)
        minCost = [[[inf] * n for _ in range(m)] for _ in range(2)]  # 0: even, 1: odd step
        pq = [(1, 0, 0, 1)]  # (cost, x, y, step parity)
        dirs = [(0, 1), (1, 0)]  # right, down

        while pq:
            cost, x, y, step = heapq.heappop(pq)
            if x == m - 1 and y == n - 1:
                return cost
            if minCost[step % 2][x][y] <= cost:
                continue
            minCost[step % 2][x][y] = cost

            if step % 2 == 1:  # 奇數步 -> 可以走
                for dx, dy in dirs:
                    nx, ny = x + dx, y + dy
                    if 0 <= nx < m and 0 <= ny < n:
                        nxtCost = cost + (nx + 1) * (ny + 1)
                        if minCost[(step + 1) % 2][nx][ny] > nxtCost:
                            heapq.heappush(pq, (nxtCost, nx, ny, (step + 1) % 2))
            else:  # 偶數步 -> 必須等待
                nxtCost = cost + waitCost[x][y]
                if minCost[(step + 1) % 2][x][y] > nxtCost:
                    heapq.heappush(pq, (nxtCost, x, y, (step + 1) % 2))
        return -1
        '''

        
