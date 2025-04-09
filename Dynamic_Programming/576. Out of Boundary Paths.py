# TC:O(m * n * cnt) SC:O(m * n)
class Solution:
    def findPaths(self, m: int, n: int, maxMove: int, startRow: int, startColumn: int) -> int:
        '''
        我的想法是走到某個越界的pos時還剩下 x 次他可以被走到的可能性就會是 某一個界內值位置, 剩下x + 1次
        從test case看來只要一旦出界後就不能走了 所以不存在界內->界外->界內->界外這種可能性
        邊界條件會是 如果當下剩下0次並且我是在起點 那這個會是可能性
        '''
        ans = 0
        MOD = 10 ** 9 + 7
        # 聰明剪枝dfs 如果某個點絕對不可能走到邊界外就不用走了
        @cache
        def dp(i,j,k):
            if i<0 or j<0 or i==m or j==n:
                return 1
            if k<=i and k<=j and i+k<m and j+k<n:
                return 0
            return (dp(i+1,j,k-1)+dp(i-1,j,k-1)+dp(i,j+1,k-1)+dp(i,j-1,k-1))%MOD
        return dp(startRow, startColumn, maxMove)

        dirs = [(0,1), (1,0), (-1,0), (0, -1)]
        '''
        遞推 空間優化過後 去掉cnt 次數
        f = [[0] * n for _ in range(m)]
        f[startRow][startColumn] = 1
        for move in range(maxMove):
            new_dp = [[0] * n for _ in range(m)]
            for i in range(m):
                for j in range(n):
                    if f[i][j] > 0:
                        for di, dj in dirs:
                            ni, nj = i + di, j + dj
                            if ni < 0 or ni >= m or nj < 0 or nj >= n:
                                ans = (ans + f[i][j]) % MOD
                            else:
                                new_dp[ni][nj] = (new_dp[ni][nj] + f[i][j]) % MOD
            f = new_dp
        return ans
        '''
        '''
        # TC = m * n * cnt * 4
        @cache
        def dfs(i:int, j:int, cnt:int) -> int:
            if cnt == 0:
                return 1 if i == startRow and j == startColumn else 0
            # 剪枝
            if abs(i - startRow) + abs(j - startColumn) > cnt:
                return 0
            ret = 0
            # 往上下左右走看看 並且要是沒出界的
            for dx, dy in dirs:
                nx, ny = i + dx, j + dy
                if 0 <= nx < m and 0 <= ny < n:
                    ret = (ret + dfs(nx, ny, cnt - 1)) % MOD
            return ret
        for k in range(1,maxMove+1): # 可以操作的次數
            for j in range(n):
                ans = (ans + dfs(-1, j, k)) % MOD
                ans = (ans + dfs(m, j, k)) % MOD
            for i in range(m):
                ans = (ans + dfs(i, -1, k)) % MOD
                ans = (ans + dfs(i, n, k)) % MOD
        return ans
        '''
            
        
